#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "WORKSHOP1";
const char* password = "PENSJOSS";
const char* mqttServer = "192.168.137.1";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
int lampu =0;


void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  delay(2000);
  pinMode(A0,INPUT);
  pinMode(D5,OUTPUT);  
  //client.publish("/sensor/potensio", "Hello from ESP8266");
  //client.subscribe("esp/test");
 client.subscribe("/aktuator/lampu");
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  lampu = (int)payload[0]-48;
  //Serial.println(lampu);
    if(lampu ==0){
      digitalWrite(D5,LOW);
    }else{
      digitalWrite(D5,HIGH);
    }
  
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
  int potensio = analogRead(A0);
  String stringPotensio = String(potensio);
  
  client.publish("/sensor/potensio", (char*) stringPotensio.c_str());
  delay(200);

  
}
