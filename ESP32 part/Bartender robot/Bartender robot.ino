#include <MyQueue.h>
#include <Pomp.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "*********";
const char* password =  "********";

AsyncWebServer server(80);
AsyncWebSocket wss("/ws");

char message[100]={};

MyQueue queue;
Pomp pomp(2, 5, 21, 22); //пины подключения помпы и клапанов

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {

  if (type == WS_EVT_CONNECT) {

    Serial.println("Websocket client connection received");
    client->text("Connection");

  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("Client disconnected");
  }
  else if (type == WS_EVT_DATA) {

    Serial.println("Data received: ");
    strncpy(message, (char*) data, len);
    queue.push_back(message);
    Serial.println(message);
    Serial.println(len);
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  wss.onEvent(onWsEvent);
  server.addHandler(&wss);

  server.begin();
}

void loop() {
  if (queue.GetSize() != 0) {
    if (!pomp.operation(queue[0])) queue.pop_front();
    else pomp.Timer(3000, 5000);//настройки таймера для конкретного напитка
  }
}
