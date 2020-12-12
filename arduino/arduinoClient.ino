#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "WORKSHOP1";
const char* password = "PENSJOSS";
const char* mqttServer = "x2.hcm-lab.id";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
int lampu =0;
float hasilfuzTemp[3], hasilfuzCahaya[3];
float valSedikit[5] = {0 , 0 , 0 , 0 , 0};
float valSedang[2] = {0 , 0 };
float valPenuh[2] = {0 , 0 };
float valCog[256];
float arSedikit[256];
float arSedang[256];
float arPenuh[256];
float tersedikit;
float tersedang ;
float terpenuh ;
int modeLampu = 0;
float finalVal;
String classification;

float finalClassification(){
  for (int i = 0; i <=90; i++){
    arSedikit[i] = valCog[i];
  }
  for (int i = 91; i <=255; i++){
    arSedikit[i] = 0;
  }

  for (int i =0 ; i <=47; i++){
    arSedikit[i] = 0;
  } 
  for (int i =48 ; i <=213; i++){
    arSedang[i] = valCog[i];
  }
  for (int i =214 ; i <=255; i++){
    arSedang[i] = 0;
  }

  for (int i = 0; i <=170; i++){
    arPenuh[i] = 0;
  }
  for (int i = 171; i <=255; i++){
    arPenuh[i] = valCog[i];
  }

  if(arSedikit[(int)finalVal] >= arSedang[(int)finalVal] && arSedikit[(int)finalVal] >= arPenuh[(int)finalVal]){
    classification = "Sedikit";
  }else if(arSedang[(int)finalVal] >= arSedikit[(int)finalVal] && arSedang[(int)finalVal] >= arPenuh[(int)finalVal]){
    classification = "Sedang";
  }else if(arPenuh[(int)finalVal] >= arSedang[(int)finalVal] && arPenuh[(int)finalVal] >= arSedikit[(int)finalVal]){
    classification = "Penuh";
  }
}

float tempFuzzifikasi(int suhu){
  float hasilfuz[3];
  //dingin
  if (suhu <= 35){
    hasilfuz[0] = 1.0;
  }else if (suhu >= 36 && suhu <= 55){
    hasilfuz[0] = (float)(55 - suhu)/ (float)20;
  }else{
    hasilfuz[0] = 0;
  }

  //hangat
  if (suhu >= 35 && suhu <= 55){
    hasilfuz[1] = (float)(suhu - 35)/(float)20;
  }else if (suhu >= 56 && suhu <= 75){
    hasilfuz[1] = (float)(75 - suhu)/(float)20;
  }
  else{
    hasilfuz[1] = 0;
  }

  //panas
  if (suhu >= 55 && suhu <= 75){
    hasilfuz[2] = (float)(suhu - 55)/(float)20;
  }else if (suhu >= 76 ){
    hasilfuz[2] = 1.0 ;
  }else{
    hasilfuz[2] = 0;
  }

  for (int i = 0; i < 3; i++)
  {
    hasilfuzTemp[i] = hasilfuz[i];
//    Serial.println(hasilfuzTemp[i]);
  }
  
}

float cahayaFuzzifikasi(int lux ){
  float hasilfuz[3];
  //gelap
  if (lux <= 25){
    hasilfuz[0] = 1.0;
  }else if (lux >= 26 && lux <= 50){
    hasilfuz[0] = (float)(50 - lux)/(float)25;
  }

  //remang
  if (lux >= 25 && lux <= 50){
    hasilfuz[1] = (float)(lux - 25)/(float)25;
  }else if (lux >= 51 && lux <= 75){
    hasilfuz[1] = (float)(75 - lux)/(float)25;
  }

  //terang
  if (lux >= 50 && lux <= 75){
    hasilfuz[2] = (float)(lux - 50)/(float)25;
  }else if (lux >= 76 ){
    hasilfuz[2] = 1.0 ;
  }

  for (int i = 0; i < 3; i++)
  {
    hasilfuzCahaya[i] = hasilfuz[i];
//    Serial.println(hasilfuzCahaya[i]);
  }
  
}


float ruleTable(){
  //sedikit
  if(hasilfuzTemp[1] <= hasilfuzCahaya[1]){
    valSedikit[0] = hasilfuzTemp[1];
  }else{
    valSedikit[0] = hasilfuzCahaya[1];
  }
  
  if(hasilfuzTemp[1] <= hasilfuzCahaya[2]){
    valSedikit[1] = hasilfuzTemp[1];
  }else{
    valSedikit[1] = hasilfuzCahaya[2];
  }

  if(hasilfuzTemp[2] <= hasilfuzCahaya[0]){
    valSedikit[2] = hasilfuzTemp[2];
  }else{
    valSedikit[2] = hasilfuzCahaya[0];
  }

  if(hasilfuzTemp[2] <= hasilfuzCahaya[1]){
    valSedikit[3] = hasilfuzTemp[2];
  }else{
    valSedikit[3] = hasilfuzCahaya[1];
  }

  if(hasilfuzTemp[2] <= hasilfuzCahaya[1]){
    valSedikit[3] = hasilfuzTemp[2];
  }else{
    valSedikit[3] = hasilfuzCahaya[1];
  }

  //sedang
  if(hasilfuzTemp[1] <= hasilfuzCahaya[0]){
    valSedang[0] = hasilfuzTemp[1];
  }else{
    valSedang[0] = hasilfuzCahaya[0];
  }

  if(hasilfuzTemp[0] <= hasilfuzCahaya[2]){
    valSedang[1] = hasilfuzTemp[0];
  }else{
    valSedang[1] = hasilfuzCahaya[2];
  }

  //PENUH

  if(hasilfuzTemp[0] <= hasilfuzCahaya[0]){
    valPenuh[0] = hasilfuzTemp[0];
  }else{
    valPenuh[0] = hasilfuzCahaya[0];
  }

  
  if(hasilfuzTemp[0] <= hasilfuzCahaya[1]){
    valPenuh[1] = hasilfuzTemp[0];
  }else{
    valPenuh[1] = hasilfuzCahaya[1];
  }

}

float maxRuleTable(){
   tersedikit = valSedikit[0];
   tersedang = valSedang[0];
   terpenuh = valPenuh[0];
  
  for (int i = 0; i < 5; i++)
  {
    if (valSedikit[i] >= tersedikit ){
        tersedikit = valSedikit[i];
    }
  }

  for (int i = 0; i < 2; i++)
  {
    if (valSedang[i] >= tersedang ){
        tersedang = valSedang[i];
    }
  }

  for (int i = 0; i < 2; i++)
  {
    if (valPenuh[i] >= terpenuh ){
        terpenuh = valPenuh[i];
    }
  }

}


float centerOfGrafity(){
  float atas, bawah, pembanding;
  
  for (int i = 0; i <= 47; i++)
  {
    valCog[i] = tersedikit;
  }

  for (int i = 48; i <= 90; i++)
  {
    pembanding = (float)(90-i)/42;
    if (pembanding >= tersedikit){
      valCog[i] = tersedikit;
    }else if(pembanding < tersedikit){
      valCog[i]= pembanding;
    }
    
    pembanding = (float)(i-48)/42;
    if (pembanding >= tersedang){
      if (valCog[i] > tersedang){
        valCog[i] = valCog[i];
      }else{
        valCog[i] = tersedang;
      }
    }else if(pembanding < tersedang){
      if (valCog[i] > pembanding){
        valCog[i] = valCog[i];
      }else{
        valCog[i] = pembanding;
      }
    }
  }
  
  for (int i = 91; i <= 170; i++)
  {
    valCog[i] = tersedang;
  }

  for (int i = 171; i <= 213; i++)
  {
    pembanding = (float)(213-i)/42;
    if (pembanding >= tersedang){
      valCog[i] = tersedang;
    }else if(pembanding < tersedang){
      valCog[i]= pembanding;
    }
    
    pembanding = (float)(i-171)/42;
    if (pembanding >= terpenuh){
      if (valCog[i] > terpenuh){
        valCog[i] = valCog[i];
      }else{
        valCog[i] = terpenuh;
      }
    }else if(pembanding < terpenuh){
      if (valCog[i] > pembanding){
        valCog[i] = valCog[i];
      }else{
        valCog[i] = pembanding;
      }
    }
  }

  for (int i =214; i <= 255; i++)
  {
    valCog[i] = terpenuh;
  }


  for (int i = 0; i < 256; i++)
  {
    atas += (float)i * (float)valCog[i];
    bawah += (float)valCog[i];
  }

  float hasilAkhir = (float)atas/(float)bawah;
  if (modeLampu == 0){
      int outLed = hasilAkhir * 1024/ 255;
      analogWrite(D5,outLed);
  }
  finalVal = hasilAkhir;

  return hasilAkhir;
}


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
  pinMode(D8,OUTPUT);  
  //client.publish("/sensor/potensio", "Hello from ESP8266");
  //client.subscribe("esp/test");
 client.subscribe("/aktuator/lampu");
 client.subscribe("mode");
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  if(strcmp(topic, "/aktuator/lampu")==0){
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
  }else if(strcmp(topic, "mode")==0){
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    modeLampu = (int)payload[0]-48;
    //Serial.println(lampu);    
    Serial.println();
    Serial.println("-----------------------");
  }
 
 
}
 
void loop() {
  client.loop();
  digitalWrite(D8,LOW);
  int potensioTemp = analogRead(A0);
  potensioTemp = potensioTemp * 100 / 1024;
  
  digitalWrite(D8,HIGH);
  int potensioCah = analogRead(A0);
  potensioCah = potensioCah * 100 / 1024;


  
  tempFuzzifikasi(potensioTemp);
  cahayaFuzzifikasi(potensioCah);
  ruleTable();
  maxRuleTable();
//  Serial.println(centerOfGrafity());
 
  // int potensio = analogRead(A0);
  String stringTemperature = String(potensioTemp);
  String stringCahaya = String(potensioCah);
  String stringFuzzyVal = String(centerOfGrafity());
  finalClassification();
  
  client.publish("/sensor/temp", (char*) stringTemperature.c_str());
  client.publish("/sensor/cahaya", (char*) stringCahaya.c_str());
  client.publish("/aktuator/fuzzylamp", (char*) stringFuzzyVal.c_str());
  client.publish("/aktuator/class", (char*) classification.c_str());
  delay(200);
}
