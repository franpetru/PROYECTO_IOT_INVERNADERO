#include <Arduino.h>
#include <WiFi.h> //<WiFi101.h>
#include <MQTT.h>

const char ssid[] = "Casa";
const char pass[] = "playa2018";
// ingresar datos de la red wifi usuario y nombre de red

WiFiClient net;
MQTTClient client;
int riego = 0; // riego
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;


void messageReceived(String &topic, String &payload) 
{
  Serial.println("incoming: " + topic + " - " + payload);
  // set temperatura 
  
 // if (topic=="Temperatura") {
 //     ledcWrite(ledChannel, payload.toInt());
 // }  
  if (topic=="Ventilacion") 
  {
    if (payload=="true") digitalWrite(26, HIGH);
    if (payload=="false") digitalWrite(26, LOW);
  }
  
}


void connect()
{
    Serial.print("checking wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.print("\nconnecting...");
    while (!client.connect("arduino"))
    { //, "public", "public")) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\nconnected!");
    client.publish("Temperatura");      // para usar en el modulo temperatura
    client.onMessage(messageReceived);  // lllama la funcion del mensage que recibe del node red .
    client.subscribe("Ventilacion");    //para usar en el modulo de ventilacion 


}

int Message_Publish()
{

    int t1 = map(analogRead(34), 0, 4095, 0, 90); // ver como lee el sensor el pin MAUROOOO jajaja
    return (t1);
}



void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(34, INPUT);  // temp
    pinMode(26, OUTPUT); // ventilacion

    WiFi.begin(ssid, pass); // se conecta a la red

    // MQTT brokers usually use port 8883 for secure connections.
    client.begin("192.168.1.109", 1883, net); // pasa la ip de la maquina para el node red y el puerto

    connect(); // llama la funcion conectar al wifi
   
}

void loop()
{

    client.loop(); // Si o si tiene que estar en el loop

    if (!client.connected())
    {
        connect();
    }

    if ((millis() - lastTime) > timerDelay)
    {
        lastTime = millis();
        client.publish("Temperatura", String(Message_Publish()));
    }

    
}