#include <ESP8266WiFi.h>       //wifi library for node mcu
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <String.h>
#define motor1 16              //motor connected to GPIO5. Basically pin number
#define motor2 5
#define motor3 4
#define motor4 0

//WiFi

WiFiClient client;            //wificlient defining 
WiFiServer server(80);        //port to 80

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
  //In the line Serial.begin(9600) u have to pass the baud rate which should be the same as in the rightmost top corner of the serial monitor written as 115200 baud. If u want to check whether it is connected or not, u may remove the usb cable and after uploading the code and then reconnect it then check in the serial monitor.
  Serial.begin(9600); 
  delay(500); 

  // Set motor pin as output
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);

  //turning on access point
  WiFi.softAP(ssid, password); 

  //output for checking wifi and finding ip
  Serial.println("NodeMCU is connected");    
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  //starts server for client requests
  server.begin();
}

void loop() {
  //client reads any device connected to network
  client = server.available();

  //if client is connected
  if (client){
    //read request and string management
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    
    //motor commands
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
