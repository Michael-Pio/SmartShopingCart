#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <Cart.h>

const char* ssid = "PioAndroid";
const char* password = "12345678"; 

int pin = D0;

Cart shoppingCart = Cart();

// Initialize WebSocket server on port 81
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected. IP Address: ");
  Serial.println(WiFi.localIP());



  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // Process WebSocket events with priority
  webSocket.loop();
  // MDNS.update();  // Update mDNS service This shit really fucks up
  // shoppingCart.loop();
}

// Handle WebSocket events
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_DISCONNECTED) {
    Serial.printf("WebSocket [%u] disconnected!\n", num);
  } else if (type == WStype_CONNECTED) {
      Serial.printf("WebSocket [%u] connected from %s\n", num, webSocket.remoteIP(num).toString().c_str());
  }


  if (type == WStype_TEXT) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload, length);

    if (!error) {
      // Parse and act on JSON command
      const char* direction = doc["direction"];
      int speed = doc["speed"];

      // Handle directions
      if (strcmp(direction, "STP") == 0) {
        Serial.println("STOP");
      } else if (strcmp(direction, "FWD") == 0) {
        Serial.println("FORWARD");
      } else if (strcmp(direction, "BWD") == 0) {
        Serial.println("BACKWARD");
      } else if (strcmp(direction, "RGT") == 0) {
        Serial.println("RIGHT");
      } else if (strcmp(direction, "LFT") == 0) {
        Serial.println("LEFT");
      }
      shoppingCart.Move(direction,speed);


      // Print speed for debugging
      Serial.print("Speed: ");
      Serial.println(speed);
    }
  }
}
