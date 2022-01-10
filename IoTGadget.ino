//#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "ESP8266_Utils.hpp"
#include "Net_Connections.hpp"
#include "Server.hpp"

void setup(void)
{

  clase1 = "OFF";
  clase2 = "OFF";

  EEPROM.begin(512);
  Serial.begin(115200);

  pinMode(GATE, OUTPUT);
  digitalWrite(GATE, LOW);

  //Serial.println(" ");
  //Serial.println(" ");
  //Serial.println(leer(201));


  if (leer(201) == NULL) {
    grabar(201, "0");
  }
  //resetESP();
  //grabar(201, "3");
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  Serial.println(WiFi.softAPIP());
  if (leer(201) == "0" || leer(201) == "3" || leer(201) == "4" || leer(201) == "6") {
    ConnectWiFi_STA_AP();
  } else {
    ConnectWiFi_STA();
  }

  InitServer();

}
int unnlockTime = 0;
int reconections = 0;
int apFlag = 0;
int i = 0;
int working = 0;
void loop()
{
  if (leer(201) == "1") {
    if (WiFi.status() != WL_CONNECTED) {
      ConnectWiFi_STA();
    }
  }
  if (leer(201) == "3") {
    if (WiFi.status() != WL_CONNECTED) {
      if (reconections > 5) {
        ConnectWiFi_STA_AP();
      } else {
        ConnectWiFi_STA();
      }

      reconections++;
    } else {
      reconections = 0;
    }
  } else {
    reconections = 0;
  }

  if (leer(201) == "5") {
    if (unnlockTime > 18) {
      grabar(201, "1");
      unnlockTime = 0;
      //ESP.reset();
    }
    unnlockTime++;
  }

  if (leer(201) == "6") {
    if (unnlockTime > 300 ) {
      //grabar(201, "1");
      apFlag = 0;
      //WiFi.disconnect();
      //ConnectWiFi_STA();
      ESP.reset();
    }
    if (apFlag == 0) {
      ConnectWiFi_STA_AP();
      apFlag = 1;
    }
    unnlockTime++;
  }

  Serial.println(leer(202));
  if (leer(202) == "C") {
    
    if (i == 0) {
      Serial.println("Start");
      grabar(202, "C");
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 3) {
      i = 0;
      Serial.println("End Start");
      grabar(202, "q");
      grabar(201, "1");
    } else {
      i++;
    }

  }
  if (leer(202) == "P") {
    if (i == 0) {
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
      i = 0;
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      grabar(202, "q");
      grabar(201, "1");
    } else {
      i++;
    }
  }
  if (leer(202) == "M") {
    if (i == 0) {
      working = 1;
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
      grabar(202, "A");
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 40) {
      i = 0;
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      grabar(202, "q");
      grabar(201, "1");
    } else {
      i++;
    }
  }

  delay(1000);
}
