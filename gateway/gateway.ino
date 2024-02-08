#include <ESP32Firebase.h> // you should download library from tools -> manage libraries ->search for library name
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <WiFi.h> 
#include <FirebaseESP32.h>// you should download library

SoftwareSerial ReyaxLoRa(27, 26); //Tx and Rx pins on ESP32

//Firebase URL and WEB API KEY from firebase
#define FIREBASE_HOST "https://haditeam-01-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyBhrjGV4SKOVnuDwgyJEJR7c707BzAtEGU"

//WIFI name and password for esp32 to connect
//You should change it when you use diffrent WIFI
#define WIFI_SSID "HUAWEI-B315-98C7"
#define WIFI_PASSWORD "YETMDE8NY8G"

//Email and password for firebase authuntics
#define USER_EMAIL "hadisupportteam@gmail.com"
#define USER_PASSWORD "Hadi1234"

//Define variables
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;
String msg;
String Sdata;
String Pdata="";

void setup() {

  // set the data rate for the HardwareSerial port
  Serial.begin(9600);
  Serial.println();
  delay(2000);
  
  // set the data rate for the SoftwareSerial port
  ReyaxLoRa.begin(9600);
  delay(100);
  //check LoRa connection
  ReyaxLoRa.print("AT\r\n");
  Serial.print("AT\r\n");
  //conect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //conect with firebase
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = FIREBASE_AUTH;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = FIREBASE_HOST;
  Firebase.begin(&config, &auth);
  Firebase.reconnectNetwork(true);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(fbdo, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(fbdo, "tiny");
  Serial.println("------------------------------------");
  Serial.println("Connected...");
}

void loop() {
  if (Firebase.ready()) {
    if (ReyaxLoRa.available()){
      //read LoRa message 
      msg=ReyaxLoRa.readString();
      //check if it is a message from other LoRa
      if (msg.startsWith("+RCV")) {
        Sdata= msg;
        Serial.println(msg);
    }
  } 
    delay(100);
    //to avoid message repeate
    if (Pdata != Sdata){
      Pdata = Sdata;
      json.set("/message", Pdata);  // Place your Lora message in firebase database
      Firebase.push(fbdo, "/Accidents", json);
    }
  }
}
