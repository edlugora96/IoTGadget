void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println();
  Serial.println("Connected to Wi-Fi sucessfully.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  InitServer();
  grabar(201, "1");
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println();
  grabar(201, "3");
  Serial.println("Disconnected from Wi-Fi, trying to connect...");
  WiFi.disconnect();
  WiFi.begin(ssid, password);
}

//-----------------Función Coneccion STA------------------------
void ConnectWiFi_STA(bool useStaticIP = false)
{
  leer(0).toCharArray(ssid, 100);
  leer(100).toCharArray(password, 100);
  Serial.println("");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
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

  Serial.println("");
  Serial.print("Iniciado AP:\t");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
}



//-----------------Función Coneccion STA_AP------------------------
void ConnectWifi_STA_AP() {

  // Begin Access Point
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssidAP, passwordAP);

  leer(0).toCharArray(ssid, 100);
  leer(100).toCharArray(password, 100);

  // Begin WiFi
  WiFi.begin(ssid, password);

  //WiFi.softAPConfig(ip, gateway, subnet);
  // Connecting to WiFi...
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println();
  /*while (WiFi.status() != WL_CONNECTED)
    {
    delay(100);
    Serial.print(".");
    }

    // Connected to WiFi
    Serial.println();

    Serial.print("IP address for network ");
    Serial.print(ssid);
    Serial.print(" : ");
    Serial.println(WiFi.localIP());*/
  Serial.println("Connected!");
  Serial.print("IP address for network ");
  Serial.print(ssidAP);
  Serial.print(" : ");
  Serial.print(WiFi.softAPIP());

}
