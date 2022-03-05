//#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include <WiFiUdp.h>

#include <NTPClient.h> // Include NTPClient library
#include <TimeLib.h>   // Include Arduino time library

#include "config.h" // Sustituir con datos de vuestra red
#include "ESP8266_Utils.hpp"
#include "Net_Connections.hpp"
#include "Server.hpp"


void setup(void)
{

  EEPROM.begin(512);
  Serial.begin(115200);

  pinMode(MA, OUTPUT);
  pinMode(MR, OUTPUT);
  pinMode(B, OUTPUT);

  digitalWrite(MA, LOW);
  digitalWrite(MR, LOW);
  digitalWrite(B, LOW);

  if (leer(201) == NULL)
  {
    grabarChar(201, '0');
  }

  //resetESP();

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);


  if (leerChar(201) == '0' || leerChar(201) == '3' || leerChar(201) == '4' || leerChar(201) == '6')
  {
    ConnectWiFi_STA_AP();
  }
  else
  {
    ConnectWiFi_STA();
  }
  unnlockTime = 0;
  reconections = 0;
  apFlag = 0;
  timePass = 0;
  working = 0;
  timeClient.begin();
  InitServer();
}

void loop()
{
  // 211 -> (E) Encender luces  / EL
  // 212 -> (F) Filtrado / FL
  // 213 -> (P) Hidromasaje piscina / HP
  // 214 -> (J) Hidromasaje jacuzzi / HJ
  // 215 -> (B) Blower / BL
  // 216 -> (C) Cascada / CS
  // 217 -> (A) Filtrado Automatica / FA
  // Serial.println(leerChar(211));

  if (leerChar(202) == '1')
  {
    grabarChar(201, '2');
    if (apFlag == 0) {
      timePass = 0;
      digitalWrite(MR, LOW);
      digitalWrite(B, LOW);
      digitalWrite(MA, LOW);
      apFlag = 1;
    }
    digitalWrite(MA, HIGH);
    delay(10000);
    digitalWrite(MA, LOW);
    delay(3000);
    digitalWrite(MR, HIGH);
    delay(10000);
    digitalWrite(MR, LOW);
    digitalWrite(B, LOW);
    digitalWrite(MA, LOW);
    delay(3000);
    if (timePass == 16 * 60 && apFlag == 1) {
      grabarChar(201, '1');
      grabarChar(202, '0');
      digitalWrite(MA, LOW);
      digitalWrite(B, LOW);
      digitalWrite(MR, LOW);
      timePass = 0;
      apFlag = 0;
    } else {
      timePass++;
    }
  }

  if (leerChar(202) == '2')
  {
    grabarChar(201, '2');
    digitalWrite(MA, LOW);
    if (working == 0) {
      timePass = 0;
      digitalWrite(B, HIGH);
      delay(10000);
      working = 1;
    }
    digitalWrite(MA, HIGH);
    if (timePass == 10 * 60 && working == 1) {
      grabarChar(201, '1');
      grabarChar(202, '0');
      digitalWrite(MA, LOW);
      digitalWrite(B, LOW);
      digitalWrite(MR, LOW);
      working = 0;
      timePass = 0;
    } else {
      timePass++;
    }
  }



  if (leerChar(236) == 'O')
  {
    ConnectWiFi_STA_AP();
    if (unnlockTime > 60)
    {
      grabarChar(236, 'F');
      unnlockTime = 0;
      ESP.reset();
    }
    unnlockTime++;
  }

  if (leerChar(236) != 'O')
  {
    if (leerChar(201) == '1' || leerChar(201) == '3')
    {
      if (reconections > 5 || leerChar(237) == 'O')
      {
        ConnectWiFi_STA_AP();
      }
      else
      {
        if (apStarted == 1)
        {
          ESP.reset();
        }
        ConnectWiFi_STA();
      }
    }
  }
  timeClient.update();
  delay(1000);
}
