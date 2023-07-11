// Inclusion de librerias
#include <SoftwareSerial.h>                 // Para trabajar con un puerto serial extra de ser NECESARIO
//________________________________________________________________________________________________________________________________________________

// Declaracion de variables globales
int var1, var2;                             // Variables de tipo entero
float var3, var4;                           // Variables de tipo flotante
unsigned long millis_tiempo;
//________________________________________________________________________________________________________________________________________________
void setup() {
  // Iniciar comunicacion serial
  Serial.begin(9600);
  delay(1000);
  Serial.println("Iniciado correctamente..");
}
void loop() {
  // Enviar datos al ESP32 por puerto serial cada 2 segundos
  if (millis() > millis_tiempo) {
    millis_tiempo = millis() + 2000ul;
    // Obtener datos aleatorios
    var1 = random(0, 100);                        // Obtener un dato enteo
    var2 = random(0, 50);                         // Obtener un dato entero
    var3 = random(0, 1000); var3 = var3 / 10.0;   // Obtener un dato flotante
    var4 = random(0, 500);  var4 = var4 / 10.0;   // Obtener un dato flotante
    Serial_Enviar();
  }
}
// Funcion: Enviar datos por puerto serie
void Serial_Enviar() {
  String datos = "{\"var1\":";
  datos = datos + var1 + ",\"var2\":";
  datos = datos + var2 + ",\"var3\":";
  datos = datos + var3 + ",\"var4\":";
  datos = datos + var4 + "}"; 
  Serial.print(datos);
  // Mostrar en consola los datos que se enviaron
  Serial.println("Datos enviados: Var1=" + String(var1) + ", Var2=" + String(var2) + ", Var3=" + String(var3) + ", Var4=" + String(var4));
}
