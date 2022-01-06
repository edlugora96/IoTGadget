//-----------------Función Coneccion STA------------------------
void ConnectWiFi_STA(bool useStaticIP = false)
{
  leer(0).toCharArray(ssid, 100);
  leer(100).toCharArray(password, 100);
  Serial.println("");
  IPAddress local_IP;
  local_IP.fromString(leer(300));
  Serial.println(local_IP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(local_IP, gateway, subnet);
  apStarted = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print('.');
  }
  grabar(201, "1");
  Serial.println("");
  Serial.print("Iniciado STA:\t");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}



//-----------------Función Coneccion AP------------------------
void ConnectWiFi_AP(bool useStaticIP = false)
{
  Serial.println("");
  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP(ssidAP, passwordAP))
  {
    Serial.println(".");
    delay(100);
  }
  //WiFi.softAPConfig(ip, gateway, subnet);
  //InitServer();
  Serial.println("");
  Serial.print("Iniciado AP:\t");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
}



//-----------------Función Coneccion STA_AP------------------------
void ConnectWiFi_STA_AP() {
  if (apStarted == 0) {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(ssidAP, passwordAP);

    Serial.println("Connected!");
    Serial.print("IP address for network ");
    Serial.print(ssidAP);
    Serial.print(" : ");
    Serial.println(WiFi.softAPIP());
    apStarted = 1;
  }

  if (leer(201) == "4" || leer(201) == "6") {
    leer(0).toCharArray(ssid, 100);
    leer(100).toCharArray(password, 100);

    Serial.println(ssid);
    Serial.println(password);
    // Begin WiFi
    WiFi.begin(ssid, password);
  }
}
