#include "streamer.h"

Streamer::Streamer() {}

bool Streamer::_connect() {
  if (_client.connected()) return true;
  Serial.println("[STREAM] Connexion au serveur...");
  if (!_client.connect(SERVER_HOST, SERVER_PORT)) {
    Serial.println("[STREAM] Échec connexion !");
    return false;
  }
  _client.printf(
    "POST %s HTTP/1.1\r\n"
    "Host: %s:%d\r\n"
    "Content-Type: application/octet-stream\r\n"
    "Transfer-Encoding: chunked\r\n"
    "Connection: keep-alive\r\n\r\n",
    SERVER_PATH, SERVER_HOST, SERVER_PORT
  );
  Serial.println("[STREAM] Connecté ✓");
  return true;
}

bool Streamer::send(camera_fb_t* fb) {
  if (!_connect()) return false;
  _client.printf("%x\r\n", fb->len);
  _client.write(fb->buf, fb->len);
  _client.print("\r\n");
  return true;
}