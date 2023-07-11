// Inclusion de librerias
#include <HTTPClient.h>              // Para trabajar con peticiones HTTP
#include <WiFi.h>                   // Para conectarse a una red Wifi
#include <ArduinoJson.h>                    // Para trabajar con objetos json
//________________________________________________________________________________________________________________________________________________
// Sustituir por los datos de vuestro WiFi
const char* ssid = "nombre WIFI";
const char* password = "clave WIFI";
// Sustituir por la url del servidor web
String url = "http://webservices/api/registry";
//________________________________________________________________________________________________________________________________________________
// Declaracion de objetos
HTTPClient http;                            // Este objeto proporciona los métodos para crear y enviar la solicitud HTTP
WiFiClient client;
//________________________________________________________________________________________________________________________________________________
// Declaracion de variables globales
int var1, var2;                             // Variables de tipo entero
float var3, var4;                           // Variables de tipo flotante
//________________________________________________________________________________________________________________________________________________
void setup() {
  // Iniciar comunicacion serial *La velocidad del BAUDIO es la misma del arduino
  Serial.begin(9600);
  // Conexion con la red Wifi
  ConectarWifi();
}

void loop() {
  // Verificar conexion Wifi. Si se desconecto entonces se vuelve a conectar
  if (WiFi.status() != WL_CONNECTED) {
    ConectarWifi();
  }
  // Verificar si llego un dato por comunicacion Serial desde el Arduino
  if (Serial.available()) {
    Procesar_Serial();    // Procesar datos
    Web_Enviar();         // Enviar datos al servidor we
  }
}

// Funcion: Conectar ESP8266 a red Wifi
void ConectarWifi() {
  //Serial.println("Conectando a red Wifi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }
  WiFi.setAutoReconnect(true);
  //Serial.println("Conectado a la red Wifi");
}

// Funcion: Procesar datos recibidor por serial desde el Arduino
void Procesar_Serial() {
  StaticJsonDocument <256> doc;
  deserializeJson(doc, Serial);
  // Leer variables
  var1 = doc ["var1"];
  var2 = doc ["var2"];
  var3 = doc ["var3"];
  var4 = doc ["var4"];
}

// Funcion: Enviar datos al servidor web
void Web_Enviar() {
  if (http.begin(client, url)) {  // Iniciar conexión con servidor web
    // Enviar datos por peticion POST
    String datos = "{\"var1\":";
    datos = datos + var1 + ",\"var2\":";
    datos = datos + var2 + ",\"var3\":";
    datos = datos + var3+ ",\"var4\":";
    datos = datos + var4 + "}";

    int lDatos = datos.length();

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "*/*");
    http.addHeader("Content-Length", String(lDatos));

    int httpCode = http.POST(datos);
    http.setTimeout(500);   // Tiempo de espera
    String payload = http.getString();
    http.end();
  }
}