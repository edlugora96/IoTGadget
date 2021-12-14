AsyncWebServer server(80);
/*#include "pags.hpp"*/


void control(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  request->send(200, "application/json", "{\"data\":\"Success\", \"error\":\"\"}");

}

void feedRequest(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String bodyContent = GetBodyContent(data, len);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) {
    request->send(500, "application/json", "{\"data\":\"\", \"error\":\"Internal error\"}");
    return;
  }

  String string_data = doc["data"];
  if (leer(201) == "0") {
    grabar(0, doc["data"]["ssid"]);
    grabar(100, doc["data"]["pass"]);

    Serial.println("SSID grabado en la EPROM");
    grabar(201, "3");
    Serial.println("EPROM: state = 3");
  }

  request->send(200, "application/json", "{\"data\":\"Success\", \"error\":\"\"}");
  delay(5000);
  ESP.reset();
  return;
}

void resetRequest(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String bodyContent = GetBodyContent(data, len);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) {
    request->send(500, "application/json", "{\"data\":\"\", \"error\":\"Internal error\"}");
    return;
  }


  String string_data = doc["data"];
  if (doc["data"]["password"] == moduleId) {
    request->send(200, "application/json", "{\"data\":\"Success\", \"error\":\"\"}");
    resetESP();
    return;
  }
}




void actionRequest(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  String bodyContent = GetBodyContent(data, len);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) {
    request->send(500, "application/json", "{\"data\":\"\", \"error\":\"Internal error\"}");
    return;
  }
  Serial.print(String(doc["data"]));
  if (leer(201) == "1") {
    grabar(202, doc["data"]);
    request->send(200, "application/json", "{\"data\":\"Success\", \"error\":\"\"}");
  } else {
    request->send(200, "application/json", "{\"data\":\"Busy\", \"error\":\"\"}");
  }




}

void InitServer()
{
  server.on("/", control);
  server.on("/action", HTTP_POST, [](AsyncWebServerRequest * request) {}, NULL, actionRequest);
  server.on("/feed", HTTP_POST, [](AsyncWebServerRequest * request) {}, NULL, feedRequest);
  server.on("/reset", HTTP_POST, [](AsyncWebServerRequest * request) {}, NULL, resetRequest);

  /*if (!MDNS.begin(dms)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
    }
    Serial.println("mDNS responder started");
    Serial.println(dms);*/

  // Iniciar servidor
  server.begin();
  Serial.println("TCP server started");

  // Add service to MDNS-SD
  //MDNS.addService("http", "tcp", 80);
}
