#define MA D0
#define MR D1
#define B D2

const char *ssidAP = "awZ2ApBt4";
const char *passwordAP = "DGnh!BD6^MOo";
const char *moduleId = "1D2D756A785CAFA80A821CA1AD021E9B";

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

// 202 -> Accion selecionada

char ssid[100];
char password[100];

IPAddress ip(192, 168, 250, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

unsigned long previousMillis = 0;
unsigned long interval = 30000;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

int unnlockTime = 0;
int reconections = 0;
int apFlag = 0;
int timePass = 0;
int i = 0;
int working = 0;
int automatic = 0;
/*
   const char* ssidAT    = 59a58ba9-cbac-43f6-a32a-d427fc03605e;
   const char* passwordAT = QhY1^GUxaWXb;
   AlaRfECerNeY
*/

int startTimeFilter = 3;
int filterPeriod = 6;
int endTimeFilter = startTimeFilter + filterPeriod;

WiFiUDP ntpUDP;

// 'time.nist.gov' is used (default server) with +1 hour offset (3600 seconds) 60 seconds (60000 milliseconds) update interval
NTPClient timeClient(ntpUDP, "time.nist.gov", -1 * 3600 * 4, 60000);

char Time[] = "TIME:00:00:00";
char Date[] = "DATE:00/00/2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;
