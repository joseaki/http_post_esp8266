#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
ESP8266WebServer server(80);
 
const char* ssid = "Dell";
const char* password = "Antonioo";
 
void setup() {
    pinMode(2, OUTPUT);
    analogWrite(2,1023);
    
    Serial.begin(115200);
    WiFi.begin(ssid, password);  //Connect to the WiFi network
    IPAddress ip(192,168,137,200);   
    IPAddress gateway(192,168,137,1);   
    IPAddress subnet(255,255,255,0);   
    WiFi.config(ip, gateway, subnet);
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
        delay(500);
        Serial.println("Waiting to connect...");
    }
 
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP
 
    server.on("/body", handleBody); //Associate the handler function to the path
 
    server.begin(); //Start the server
    Serial.println("Server listening");
 
}
 
void loop() {
    server.handleClient(); //Handling of incoming requests
}
 
void handleBody() { //Handler for the body path
  if (server.hasArg("v_right")== false){ //Check if body received
        server.send(200, "text/plain", "Body not received");
        return;
  }
  
  String pwm_str_right = server.arg("v_right");
  int pwm_value_right=pwm_str_right.toInt();
  String pwm_str_left = server.arg("v_left");
  int pwm_value_left=pwm_str_left.toInt();
  
  analogWrite(2,pwm_value_right);
  analogWrite(0,pwm_value_left);
  /*
  if(server.arg("plain")=="centro"){
    analogWrite(2, 512);
  }else{
    analogWrite(2,1023);
  }*/
  
  String message = "right speed:\n";
         message += server.arg("v_right");
         message += "\n";
         message += "left speed:\n";
         message += server.arg("v_left");

  server.send(200, "text/plain", message);
  Serial.println(message);
}

