//#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "ESP8266_Utils.hpp"
#include "Server.hpp"
#include "Net_Connections.hpp"


void setup(void)
{

  clase1 = "OFF";
  clase2 = "OFF";

  EEPROM.begin(512);
  Serial.begin(115200);

  pinMode(GATE, OUTPUT);
  digitalWrite(GATE, LOW);

  Serial.println(" ");
  Serial.println(" ");
  Serial.println(leer(201));


  if (leer(201) == NULL) {
    grabar(201, "0");
  }

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  if (leer(201) != "0") {
    ConnectWiFi_STA();
  } else {
    ConnectWiFi_AP();
  }

  InitServer();
}

int i = 0;
void loop()
{
  if (leer(201) != "0") {
    if (WiFi.status() != WL_CONNECTED) {
      ConnectWiFi_STA();
    }
  }
  if (leer(202) == "C") {

    if (i == 0) {
      grabar(201, "2");
      grabar(202, "C");
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 3) {
      i = 0;
      grabar(202, "q");
      grabar(201, "1");
    } else {
      i++;
    }

  }
  if (leer(202) == "P") {
    if (i == 0) {
      grabar(201, "2");
      grabar(202, "P");
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 6) {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 9) {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      i = 0;
      grabar(202, "q");
      grabar(201, "1");
    } else {
      i++;
    }
  }
  if (leer(202) == "M") {
    if (i == 0) {
      grabar(201, "2");
      grabar(202, "M");
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 6) {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 13) {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      i = 0;
      grabar(202, "q");
      grabar(201, "1");
    } else {
      i++;
    }
  }
  if (leer(202) == "A") {
    if (i == 0) {
      grabar(201, "2");
      grabar(202, "A");
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 40) {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      i = 0;
      grabar(202, "q");
      grabar(201, "1");
    } else {
      i++;
    }
  }

  delay(1000);
}
