#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <String.h>
#define motor1 16
#define motor2 5
#define motor3 4
#define motor4 0

WiFiClient client;
WiFiServer server(80);

char* ssid = "rudrakshbotx";
char* password = "BotXDriftKing";

void forward();
void backward();
void right();
void left();
void stop();
void rightturn();
void leftturn();

void setup() {
  Serial.begin(9600); 
  delay(500);

  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);

  WiFi.softAP(ssid, password); 

  Serial.println("NodeMCU is connected");    
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  client = server.available();

  if (client){
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    
    if (request == "GET /?dir=forward HTTP/1.1")  {
      forward();
      Serial.println("FORWARD");
    } 
    else if (request == "GET /?dir=backward HTTP/1.1") {
      backward();
      Serial.println("BACK");
    } 
    else if (request == "GET /?dir=stop HTTP/1.1") {
      stop();
      Serial.println("STOP");
    } 
    else if (request == "GET /?dir=right HTTP/1.1") {
      right();
      Serial.println("RIGHT");
    } 
    else if (request == "GET /?dir=left HTTP/1.1") {
      left();
      Serial.println("LEFT");
    }
    else if (request == "GET /?dir=L HTTP/1.1") {
      Serial.println("ROTATE LEFT");
      leftturn();
    }
    else if (request == "GET /?dir=R HTTP/1.1") {
      Serial.println("ROTATE RIGHT");
      rightturn();
    }
  }
}

void forward() {
  digitalWrite(motor2, LOW);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor4, LOW);
  digitalWrite(motor3, HIGH);
}
void backward() {
  digitalWrite(motor2, HIGH);
  digitalWrite(motor1, LOW);
  digitalWrite(motor4, HIGH);
  digitalWrite(motor3, LOW);
}
void right() { 
  digitalWrite(motor2, LOW);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor4, LOW);
  digitalWrite(motor3, LOW);
}
void left() {
  digitalWrite(motor2, LOW);
  digitalWrite(motor1, LOW);
  digitalWrite(motor4, LOW);
  digitalWrite(motor3, HIGH);
}
void stop() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}
void rightturn() {
  digitalWrite(motor2, LOW);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor4, HIGH);
  digitalWrite(motor3, LOW);
}
void leftturn() {
  digitalWrite(motor2, HIGH);
  digitalWrite(motor1, LOW);
  digitalWrite(motor4, LOW);
  digitalWrite(motor3, HIGH);
}
