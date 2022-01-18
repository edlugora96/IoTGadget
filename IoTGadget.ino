//#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "config.h" // Sustituir con datos de vuestra red
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
  //Serial.println(leerChar(201));

  if (leerChar(201) == NULL)
  {
    grabarChar(201, '0');
  }
  //resetESP();
  //grabarChar(201, '3');
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  Serial.println(WiFi.softAPIP());
  if (leerChar(201) == '0' || leerChar(201) == '3' || leerChar(201) == '4' || leerChar(201) == '6')
  {
    ConnectWiFi_STA_AP();
  }
  else
  {
    ConnectWiFi_STA();
  }

  InitServer();
}
void loop()
{
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
        if (apStarted == 1) {
          ESP.reset();
        }
        ConnectWiFi_STA();
      }
    }
  }

  if (leerChar(202) == 'C')
  {
   
    if (i == 0)
    {
      
      grabarChar(202, 'C');
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i >= 3)
    {
      i = 0;
      grabarChar(202, 'q');
      grabarChar(201, '1');
    }
    else
    {
      i++;
    }
  }
  if (leerChar(202) == 'P')
  {
    Serial.println(i);
    if (i == 0)
    {
      Serial.println("Start");
      grabarChar(202, 'P');
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 6)
    {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i >= 9)
    {
      i = 0;
      Serial.println("End Start");
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      grabarChar(202, 'q');
      grabarChar(201, '1');
    }
    else
    {
      i++;
    }
  }
  if (leerChar(202) == 'M')
  {
    if (i == 0)
    {
      working = 1;
      grabarChar(202, 'M');
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i == 6)
    {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i >= 13)
    {
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      i = 0;
      grabarChar(202, 'q');
      grabarChar(201, '1');
    }
    else
    {
      i++;
    }
  }
  if (leerChar(202) == 'A')
  {
    if (i == 0)
    {
      grabarChar(202, 'A');
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
    }

    if (i >= 40)
    {
      i = 0;
      digitalWrite(GATE, HIGH);
      delay(100);
      digitalWrite(GATE, LOW);
      grabarChar(202, 'q');
      grabarChar(201, '1');
    }
    else
    {
      i++;
    }
  }

  delay(1000);
}
