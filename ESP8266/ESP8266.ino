#include <WiFi.h>
#include <WebServer.h>
/*Put your SSID & Password*/
const char* ssid = "drona";  // Enter SSID here
const char* password = "auvdrona";  //Enter Password here

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);
boolean right_status=LOW;
 boolean left_status = LOW;
boolean  up_status = LOW;
boolean  down_status = LOW;
 boolean paus_status = LOW;

void setup() {
  Serial.begin(9600);
  
  //Serial.println("Connecting to ");
  //Serial.println(ssid);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  server.on("/", handle_OnConnect);
  server.on("/up", up);
  server.on("/down", down);
  server.on("/right", right);
  server.on("/left", left);
  server.on("/paus", paus);
  server.onNotFound(handle_NotFound);

  server.begin();
  //Serial.println("HTTP server started");
}
void loop() {
  digitalWrite(SS, HIGH);
  server.handleClient();
  if(right_status)
  {Serial.println("a");}
  else if(left_status)
  {Serial.println("b");}
  else if(up_status)
  {Serial.println("c");}
  else if(down_status)
  {Serial.println("d");}
  else if(paus_status)
  {Serial.println("e");}
}

void handle_OnConnect() {
  right_status = LOW;
  left_status = LOW;
  up_status = LOW;
  down_status = LOW;
  paus_status = LOW;
  //Serial.println("No motion");
  server.send(200, "text/html", SendHTML(up_status,down_status,left_status,right_status,paus_status)); 
}

void up() {
  right_status = LOW;
  left_status = LOW;
  up_status = HIGH;
  down_status = LOW;
  paus_status = LOW;
  //Serial.println("Up: ON");
  server.send(200, "text/html", SendHTML(up_status,down_status,left_status,right_status,paus_status)); 
}

void down() {
  right_status = LOW;
  left_status = LOW;
  up_status = LOW;
  down_status = HIGH;
  paus_status = LOW;
  //Serial.println("Down: ON");
  server.send(200, "text/html", SendHTML(up_status,down_status,left_status,right_status,paus_status)); 
}

void right() {
  right_status = HIGH;
  left_status = LOW;
  up_status = LOW;
  down_status = LOW;
  paus_status = LOW;
  //Serial.println("Right Status: ON");
  server.send(200, "text/html", SendHTML(up_status,down_status,left_status,right_status,paus_status)); 
}

void left() {
  right_status = LOW;
  left_status = HIGH;
  up_status = LOW;
  down_status = LOW;
  paus_status = LOW;
  //Serial.println("Reft : ON");
  server.send(200, "text/html", SendHTML(up_status,down_status,left_status,right_status,paus_status)); 
}
void paus() {
  right_status = LOW;
  left_status = LOW;
  up_status = LOW;
  down_status = LOW;
  paus_status = HIGH;
  //Serial.println("Stalling : ON");
  server.send(200, "text/html", SendHTML(up_status,down_status,left_status,right_status,paus_status)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t up_status,uint8_t down_status,uint8_t left_status,uint8_t right_status,uint8_t paus_status){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button { border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }\n";
  ptr +=".button-upOFF {background-color: #4CAF50;}\n";
  ptr +=".button-downOFF {background-color: #4CAF50;}\n";
  ptr +=".button-rightOFF {background-color: #4CAF50;}\n";
  ptr +=".button-leftOFF {background-color: #4CAF50;}\n";
  ptr +=".button-pausOFF {background-color: #4CAF50;}\n";
  ptr +=".button-upON {background-color: #008CBA;}\n";
  ptr +=".button-downON {background-color: #008CBA;}\n";
  ptr +=".button-rightON {background-color: #008CBA;}\n";
  ptr +=".button-leftON {background-color: #008CBA;}\n";
  ptr +=".button-pausON {background-color: #008CBA;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
    ptr +="<h3>Using Station(STA) Mode</h3>\n";
  
   if(up_status)
  {ptr +="<p>Moving up</p><a class=\"button button-upON\" href=\"/up\">ON</a>\n";}
  else
  {ptr +="<p>up</p><a class=\"button button-upOFF\" href=\"/up\">OFF</a>\n";}

  if(down_status)
  {ptr +="<p>Moving down</p><a class=\"button button-downON\" href=\"/down\">ON</a>\n";}
  else
  {ptr +="<p>down</p><a class=\"button button-downOFF\" href=\"/down\">OFF</a>\n";}

  if(left_status)
  {ptr +="<p>Moving left</p><a class=\"button button-leftON\" href=\"/left\">ON</a>\n";}
  else
  {ptr +="<p>left</p><a class=\"button button-leftOFF\" href=\"/left\">OFF</a>\n";}

  if(right_status)
  {ptr +="<p>Moving right</p><a class=\"button button-rightON\" href=\"/right\">ON</a>\n";}
  else
  {ptr +="<p>right</p><a class=\"button button-rightOFF\" href=\"/right\">OFF</a>\n";}

  if(paus_status)
  {ptr +="<p>pausd</p><a class=\"button button-pausON\" href=\"/paus\">ON</a>\n";}
  else
  {ptr +="<p>paus</p><a class=\"button button-pausOFF\" href=\"/paus\">OFF</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
