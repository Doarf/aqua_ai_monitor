const express = require('express');
const http    = require('http');
const app     = express();
const server  = http.createServer(app);

const PORT   = 3000;
let clients  = [];

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/public/index.html');
});

app.post('/stream', (req, res) => {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setTimeout(0);
  req.setTimeout(0);

  let buffer = Buffer.alloc(0);

  req.on('data', chunk => {
    // Accumule les chunks
    buffer = Buffer.concat([buffer, chunk]);

    // Cherche les marqueurs JPEG (début 0xFFD8, fin 0xFFD9)
    let start = -1;
    for (let i = 0; i < buffer.length - 1; i++) {
      if (buffer[i] === 0xFF && buffer[i+1] === 0xD8) {
        start = i;
      }
      if (start !== -1 && buffer[i] === 0xFF && buffer[i+1] === 0xD9) {
        const frame = buffer.slice(start, i + 2);
        buffer = buffer.slice(i + 2);

        // Envoie la frame complète à tous les clients
        clients.forEach(client => {
          try {
            client.write('--frame\r\nContent-Type: image/jpeg\r\n\r\n');
            client.write(frame);
            client.write('\r\n');
          } catch(e) {}
        });

        start = -1;
        i = 0;
      }
    }
  });

  req.on('end',   () => res.sendStatus(200));
  req.on('error', () => res.sendStatus(500));
});

app.get('/video', (req, res) => {
  res.setHeader('Content-Type', 'multipart/x-mixed-replace; boundary=frame');
  res.setHeader('Cache-Control', 'no-cache');
  res.setHeader('Connection', 'keep-alive');
  res.setTimeout(0);

  clients.push(res);
  console.log(`[+] Client connecté (${clients.length})`);

  req.on('close', () => {
    clients = clients.filter(c => c !== res);
    console.log(`[-] Client déconnecté (${clients.length})`);
  });
});

server.listen(PORT, '0.0.0.0', () => {
  console.log(`\n=== ESP32-CAM Stream Server ===`);
  console.log(`Site web : http://localhost:${PORT}`);
});