AsyncWebServer server(80);
/*#include "pags.hpp"*/

void control(AsyncWebServerRequest *request)
{
  Serial.println("Llego informacion");

  if (leerChar(201) == '5')
  {
    grabarChar(201, '1');
  }

  AsyncResponseStream *response = request->beginResponseStream("application/json");
  if (WiFi.status() == WL_CONNECTED && leerChar(201) != '0')
  {
    Serial.println(WiFi.localIP());
    String ip_lcl = IpAddress2String(WiFi.localIP());
    grabar(300, ip_lcl);
    request->send(200, "application/json", "{\"code\":200,\"data\":\"" + ip_lcl + "\", \"wifi\":\"" + leer(0) + "\",  \"error\":\"\"}");
  }
  else
  {
    request->send(200, "application/json", "{\"code\":200,\"data\":\"" + leer(300) + "\", \"wifi\":\"" + leer(0) + "\",  \"error\":\"\"}");
  }
}

void feedRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String bodyContent = GetBodyContent(data, len);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error)
  {
    request->send(200, "application/json", "{\"code\":500,\"data\":\"\", \"error\":\"Internal error\"}");
    return;
  }

  String string_data = doc["feed"];
  //if (leer(201) == "0") {
  grabar(0, doc["feed"]["ssid"]);
  grabar(100, doc["feed"]["pass"]);
  grabar(300, "0");

  grabarChar(201, '4');
  //}
  WiFi.disconnect();
  ConnectWiFi_STA_AP();

  request->send(200, "application/json", "{\"code\":200,\"data\":\"Success\", \"error\":\"\"}");
  //delay(5000);
  //ESP.reset();
  return;
}

void resetRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String bodyContent = GetBodyContent(data, len);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error)
  {
    request->send(200, "application/json", "{\"code\":500,\"data\":\"\", \"error\":\"Internal error\"}");
    return;
  }

  String string_data = doc["data"];
  if (doc["data"] == moduleId)
  {
    request->send(200, "application/json", "{\"code\":200,\"data\":\"Success\", \"error\":\"\"}");
    resetESP();
    return;
  }
}

void unlockRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String bodyContent = GetBodyContent(data, len);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error)
  {
    request->send(200, "application/json", "{\"code\":500,\"data\":\"\", \"error\":\"Internal error\"}");
    return;
  }

  String string_data = doc["data"];
  if (doc["data"] == moduleId)
  {
    grabarChar(236, 'O');
    request->send(200, "application/json", "{\"code\":200,\"data\":\"Success\", \"error\":\"\"}");
    //ESP.reset();
    return;
  }
}

void actionRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{

  AsyncResponseStream *response = request->beginResponseStream("application/json");

  String bodyContent = GetBodyContent(data, len);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error)
  {
    request->send(200, "application/json", "{\"code\":500,\"data\":\"\", \"error\":\"Internal error\"}");
    return;
  }
  if (leer(201) != "2")
  {
    char resp = doc["data"];
    String respInStr = doc["data"];
    grabarChar(202, respInStr[0]);
  }
  if (leerChar(201) == '2')
  {
    request->send(200, "application/json", "{\"code\":400,\"data\":\"Busy\", \"error\":\"\"}");
  }
  else
  {
    request->send(200, "application/json", "{\"code\":200,\"data\":\"Success\", \"error\":\"\"}");
  }
}

void InitServer()
{
  server.on("/", control);
  server.on(
      "/action", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, actionRequest);
  server.on(
      "/feed", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, feedRequest);
  server.on(
      "/reset", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, resetRequest);
  server.on(
      "/unlock", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, unlockRequest);

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
  //Serial.println("TCP server started");

  // Add service to MDNS-SD
  //MDNS.addService("http", "tcp", 80);
}

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println();
  Serial.println("Connected to Wi-Fi sucessfully.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  IPAddress local_IP_test;
  local_IP_test.fromString(leer(300));
  if (leer(300) != "0")
  {
    if (WiFi.localIP().toString() != local_IP_test.toString())
    {
      Serial.print("Que shit pasa con la ip?");
      grabarChar(237, 'O');
    }

    if (WiFi.localIP().toString() == local_IP_test.toString())
    {
      Serial.print("Estan bien las Ip");
      grabarChar(237, 'F');
    }
  }

  if (leerChar(201) != '4' && leerChar(201) != '6')
  {
    grabarChar(201, '1');
  }
  else if (leerChar(201) == '4' && leerChar(201) != '6')
  {
    grabarChar(201, '5');
  }

  if (leerChar(201) == '0' || leerChar(201) == '5')
  {
    Serial.println("Ip Guardada");
    String ip_lcl = IpAddress2String(WiFi.localIP());
    grabar(300, ip_lcl);
  }
  if (reconections > 5)
  {
    ESP.reset();
  }
  reconections = 0;
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println();
  if (leerChar(201) != '4')
  {
    grabarChar(201, '3');
  }
  /*if (leer(201) == "6") {
    ESP.reset();
    }
    else {
    ConnectWiFi_STA_AP();
    }*/
  reconections++;
  //grabar(300, "0");
  Serial.println("Disconnected from Wi-Fi, trying to connect...");
  WiFi.disconnect();
  //WiFi.begin(ssid, password);
}
