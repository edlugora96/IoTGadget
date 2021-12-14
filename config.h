#define GATE D1

const char* ssidAP    = "L59a58ba8";
const char* passwordAP    = "123456789";
/*const char* passwordAP = "QhY1^GUxaWXb";*/
String ssiPP = "Hola Mundo";
const char* moduleId = "59a58ba9-cbac-43f6-a32a-d427fc03605e";
char* state;
char command[5];
// 0 -> Sin conexion - Sin informacion - esta en modo AP
// 1 -> Conectado y disponoble
// 2 -> modulo ocupado
// 3 -> Sin conexion - Con informacion

char ssid[100];
char password[100];
const char* dms = "isougmusivia";

IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


String clase1;
String clase2;

unsigned long previousMillis = 0;
unsigned long interval = 30000;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;


/*
   const char* ssidAT    = 59a58ba9-cbac-43f6-a32a-d427fc03605e;
   const char* passwordAT = QhY1^GUxaWXb;
   AlaRfECerNeY
*/
