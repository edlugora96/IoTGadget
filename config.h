#define GATE D1

const char *ssidAP = "L59a58ba8";
//const char* passwordAP    = "123456789";
const char *passwordAP = "QhY1^GUxaWXb";
String ssiPP = "Hola Mundo";
const char *moduleId = "59a58ba9-cbac-43f6-a32a-d427fc03605e";
char *state;
char command[5];

int apStarted = 0;
// 0 -> Sin conexion - Sin informacion - esta en modo AP
// 1 -> Conectado y disponoble
// 2 -> modulo ocupado
// 3 -> Sin conexion - Con informacion
// 4 -> Configurando Wi-Fi
// 5 -> Configurando en espera Wi-Fi

// 236 -> Gadget desbloqueado
// 237 -> Ip problem

// 0   -> SSID Wifi
// 100 -> Wifi password
// 201 -> Estado
char ssid[100];
char password[100];
const char *dms = "isougmusivia";

IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

String clase1;
String clase2;

unsigned long previousMillis = 0;
unsigned long interval = 30000;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

int unnlockTime = 0;
int reconections = 0;
int apFlag = 0;
int i = 0;
int working = 0;

/*
   const char* ssidAT    = 59a58ba9-cbac-43f6-a32a-d427fc03605e;
   const char* passwordAT = QhY1^GUxaWXb;
   AlaRfECerNeY
*/
