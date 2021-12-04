/*#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Timer/Timer.h>
#include <WebServer.h>
#include <MQTT.h>
#include <webpage.h>

Timer timerA;

OneWire sensorTemp1(4);                //Se establece el pin 4  como bus OneWire

DallasTemperature sensors(&sensorTemp1); //Se declara una variable u objeto para nuestro sensor


//-----------------------------------------------
  WebServer server(80);
  const char* ssid = "cotemax_eca";
  const char* password = "cote566d";
  
//-----------------------------------------------

void setup() {
Serial.begin(115200);
sensors.begin();   //Se inicia el sensor
timerA.reset();
}

void loop() {
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  if(timerA.elapsed() > 500){
    Serial.print("Temperatura= ");
    Serial.print(temp);
    Serial.println(" C°");
  }
  timerA.reset();

}*/




/*El ejemplo envia la varible de Temperatura a ThingSpeak utilizando la placa ESP32*/ 
/****************************************
*Definir libreris, instancias y constantes
*para la conexion WIFI
****************************************/
#include <WiFi.h>
  const char* ssid = "cotemax_eca";
  const char* password = "cote566d";
  WiFiClient client = 80;

/****************************************
*Definir librería, instancias y constantes
*para la conexión a ThingSpeak
****************************************/
#include "ThingSpeak.h"
unsigned long Channel_ID = 1586772; //Ingrese su numero de canal de ThingSpeak
const char * WriteAPIKey = "9BQFH1WROKEYARWW"; //Ingrese su clave de API de escritura de canal

/****************************************
*Definir librería, instancias y constantes
*para del sensor DS18B20
****************************************/
#include <OneWire.h> 
#include <DallasTemperature.h>
OneWire ourWire(4); //Se establece el pin 4 del ESP32 para la lectura del sensor
DallasTemperature DS18B20(&ourWire); //Se declara una variable u objeto para el sensor

/****************************************
*Funciones principales
****************************************/

void setup()
{
Serial.begin(115200); //Iniciar el monitor serie
Serial.println("Iniciando conexión Wifi"); //Imprimir mensaje de conexión a la red Wifi
WiFi.begin(ssid, password); //Se inicia la conexión al Wifi
//Minetras se conecta imprimirá ...

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  //Ya que se estableció la conexión al Wifi se imprime conexión establecida
  Serial.println("Conexion establecida");
  ThingSpeak.begin(client); //Iniciar el servidor de ThingSpeak
  DS18B20.begin(); //Se inicia el sensor DS18B20
  }
}

//Función para leer el sensor y asignar los campos a ThingSpeak
void leer_sensor_DS18B20(){
DS18B20.requestTemperatures(); //Se envía el comando para leer la temperatura
float tem= DS18B20.getTempCByIndex(0); //Se obtiene la temperatura en ºC
Serial.print("Temperatura= ");
Serial.print(tem);
Serial.println(" °C");
//Signar en ThingSpeak al campo 1 la lectura de temperatura
ThingSpeak.setField(1, tem); 
}

void loop(){
leer_sensor_DS18B20(); //Función para lectura del sensor
//Transmitir los datos al sevidor ThingSpeak
ThingSpeak.writeFields(Channel_ID, WriteAPIKey);
Serial.println("Datos enviados a ThingSpeak");

}

