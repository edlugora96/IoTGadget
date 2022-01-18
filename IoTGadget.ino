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

/*
  #define MP D0
  #define BL D1
  #define MJ D2
  #define HP D3
  #define HJ D4
  #define CS D5
  #define LZ D6

*/

void setup(void)
{

  EEPROM.begin(512);
  Serial.begin(115200);

  pinMode(MP, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(MJ, OUTPUT);
  pinMode(HP, OUTPUT);
  pinMode(HJ, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(LZ, OUTPUT);

  digitalWrite(MP, LOW);
  digitalWrite(BL, LOW);
  digitalWrite(MJ, LOW);
  digitalWrite(HP, LOW);
  digitalWrite(HJ, LOW);
  digitalWrite(CS, LOW);
  digitalWrite(LZ, LOW);

  if (leer(201) == NULL)
  {
    grabarChar(201, '0');
  }

  //resetESP();

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  if (leerChar(211) == 'O')
  {
    digitalWrite(LZ, HIGH);
  }

  if (leerChar(212) == 'O' || leerChar(217) == 'O')
  {
    digitalWrite(MP, HIGH);
  }

  if (leerChar(213) == 'O' || leerChar(214) == 'O' || leerChar(216) == 'O')
  {
    digitalWrite(MJ, HIGH);
  }

  if (leerChar(215) == 'O')
  {
    digitalWrite(BL, HIGH);
  }

  if (leerChar(213) == 'O')
  {
    digitalWrite(HP, HIGH);
  }
  if (leerChar(214) == 'O')
  {
    digitalWrite(HJ, HIGH);
  }
  if (leerChar(216) == 'O')
  {
    digitalWrite(CS, HIGH);
  }

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
  i = 0;
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

  if (leerChar(299) == 'O')
  {

    grabarChar(299, 'F');
    if (leerChar(202) == 'E')
    {
      Serial.println("Encender luces");
      if (leerChar(211) == 'O')
      {
        grabarChar(211, 'F');
      }
      else
      {
        grabarChar(211, 'O');
      }
    }
    if (leerChar(202) == 'F')
    {
      Serial.println("Filtrado Manual");
      if (leerChar(212) == 'O')
      {
        grabarChar(212, 'F');
      }
      else
      {
        grabarChar(212, 'O');
      }
    }
    if (leerChar(202) == 'P')
    {
      Serial.println("Hidromasaje piscina");
      if (leerChar(213) == 'O')
      {
        grabarChar(213, 'F');
      }
      else
      {
        grabarChar(213, 'O');
      }
    }
    if (leerChar(202) == 'J')
    {
      Serial.println("Hidromasaje jacuzzi");
      if (leerChar(214) == 'O')
      {
        grabarChar(214, 'F');
      }
      else
      {
        grabarChar(214, 'O');
      }
    }
    if (leerChar(202) == 'B')
    {
      Serial.println("Blower");
      if (leerChar(215) == 'O')
      {
        grabarChar(215, 'F');
      }
      else
      {
        grabarChar(215, 'O');
      }
    }
    if (leerChar(202) == 'C')
    {
      Serial.println("Cascada");
      if (leerChar(216) == 'O')
      {
        grabarChar(216, 'F');
      }
      else
      {
        grabarChar(216, 'O');
      }
    }
    if (leerChar(202) == 'A')
    {
      Serial.println("Filtrado Automatico");
      if (leerChar(217) == 'O')
      {
        grabarChar(217, 'F');
      }
      else
      {
        grabarChar(217, 'O');
      }
    }
  }

  if (leerChar(211) == 'O')
  {
    digitalWrite(LZ, HIGH);
  }
  else
  {
    digitalWrite(LZ, LOW);
  }

  if (leerChar(212) == 'O' || leerChar(217) == 'O')
  {
    digitalWrite(MP, HIGH);
  }
  else
  {
    digitalWrite(MP, LOW);
  }

  if (leerChar(213) == 'O' || leerChar(214) == 'O' || leerChar(216) == 'O')
  {
    digitalWrite(MJ, HIGH);
  }
  else
  {
    digitalWrite(MJ, LOW);
  }

  if (leerChar(215) == 'O')
  {
    digitalWrite(BL, HIGH);
  }
  else
  {
    digitalWrite(BL, LOW);
  }

  if (leerChar(213) == 'O')
  {
    digitalWrite(HP, HIGH);
  }
  else
  {
    digitalWrite(HP, LOW);
  }

  if (leerChar(214) == 'O')
  {
    digitalWrite(HJ, HIGH);
  }
  else
  {
    digitalWrite(HJ, LOW);
  }

  if (leerChar(216) == 'O')
  {
    digitalWrite(CS, HIGH);
  }
  else
  {
    digitalWrite(CS, LOW);
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
  unsigned long unix_epoch = timeClient.getEpochTime(); // Get Unix epoch time from the NTP server

  second_ = second(unix_epoch);
  if (last_second != second_)
  {

    minute_ = minute(unix_epoch);
    hour_ = hour(unix_epoch);
    day_ = day(unix_epoch);
    month_ = month(unix_epoch);
    year_ = year(unix_epoch);

    Time[12] = second_ % 10 + 48;
    Time[11] = second_ / 10 + 48;
    Time[9] = minute_ % 10 + 48;
    Time[8] = minute_ / 10 + 48;
    Time[6] = hour_ % 10 + 48;
    Time[5] = hour_ / 10 + 48;

    Date[5] = day_ / 10 + 48;
    Date[6] = day_ % 10 + 48;
    Date[8] = month_ / 10 + 48;
    Date[9] = month_ % 10 + 48;
    Date[13] = (year_ / 10) % 10 + 48;
    Date[14] = year_ % 10 % 10 + 48;

    // Send time and date to serial monitor
    //Serial.println(Time);
    //Serial.println(Date);
    if (hour_ >= startTimeFilter && hour_ <= endTimeFilter)
    {
      grabarChar(217, 'O');
    }

    if (hour_ < startTimeFilter || hour_ > endTimeFilter && leerChar(212) != 'O')
    {
      grabarChar(217, 'F');
    }

    last_second = second_;
  }

  delay(1000);
}
