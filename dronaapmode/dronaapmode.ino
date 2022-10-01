// Load Wi-Fi library
#include <WiFi.h>
#include <HardwareSerial.h>

HardwareSerial SerialPort(2);

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String forwardState = "off";
String reverseState = "off";
String yawleftState = "off";
String yawrightState = "off";
String ascendState = "off";
String descendState = "off";
String stableState = "on";


void setup() {
  SerialPort.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            


            //Code for the buttons
            if (header.indexOf("GET /forward/on") >= 0)
            {
              forwardState = "on";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "off";
              SerialPort.print('c');
              
            }
            else if(header.indexOf("GET /forward/off") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "on"; 
              SerialPort.print('f'); 
            }
            else if(header.indexOf("GET /reverse/on") >= 0)
            { 
              forwardState = "off";
              reverseState = "on";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "off";
              SerialPort.print('d');  
            }
            else if(header.indexOf("GET /reverse/off") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "on";
              SerialPort.print('f');  
            }
            else if(header.indexOf("GET /yawleft/on") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "on";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "off";
              SerialPort.print('a');  
            }
            else if(header.indexOf("GET /yawleft/off") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "on"; 
              SerialPort.print('f'); 
            }
            else if(header.indexOf("GET /yawright/on") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "on";
              ascendState = "off";
              descendState = "off";
              stableState = "off";
              SerialPort.print('b');  
            }
            else if(header.indexOf("GET /yawright/off") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "on";
              SerialPort.print('f');  
            }
            else if(header.indexOf("GET /ascend/on") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "on";
              descendState = "off";
              stableState = "off";
              SerialPort.print('g');  
            }
            else if(header.indexOf("GET /ascend/off") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "on"; 
              SerialPort.print('f'); 
            }
            else if(header.indexOf("GET /descend/on") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "on";
              stableState = "off";
              SerialPort.print('e');  
            }
            else if(header.indexOf("GET /descend/off") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "on";
              SerialPort.print('f');  
            }
            else if(header.indexOf("GET /stable/on") >= 0)
            {
              forwardState = "off";
              reverseState = "off";
              yawleftState = "off";
              yawrightState = "off";
              ascendState = "off";
              descendState = "off";
              stableState = "on";
              SerialPort.print('f');  
            }
                        
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Drona Control</h1>");
            


            // Display current state, and ON/OFF buttons for forward  
            client.println("<p>Forward - State " + forwardState + "</p>");
            // If the forwardState is off, it displays the ON button       
            if (forwardState=="off") {
              client.println("<p><a href=\"/forward/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/forward/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for reverse  
            client.println("<p>Reverse - State " + reverseState + "</p>");
            // If the forwardState is off, it displays the ON button       
            if (reverseState=="off") {
              client.println("<p><a href=\"/reverse/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/reverse/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for yawleft  
            client.println("<p>Yaw left - State " + yawleftState + "</p>");
            // If the yawleftState is off, it displays the ON button       
            if (yawleftState=="off") {
              client.println("<p><a href=\"/yawleft/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/yawleft/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            // Display current state, and ON/OFF buttons for yawright  
            client.println("<p>Yaw right - State " + yawrightState + "</p>");
            // If the yawrightState is off, it displays the ON button       
            if (yawrightState=="off") {
              client.println("<p><a href=\"/yawright/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/yawright/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for ascend  
            client.println("<p>Ascend - State " + ascendState + "</p>");
            // If the ascendState is off, it displays the ON button       
            if (ascendState=="off") {
              client.println("<p><a href=\"/ascend/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/ascend/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
           
            // Display current state, and ON/OFF buttons for descend  
            client.println("<p>Descend - State " + descendState + "</p>");
            // If the descendState is off, it displays the ON button       
            if (descendState=="off") {
              client.println("<p><a href=\"/descend/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/descend/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for stable  
            client.println("<p>Stable - State " + stableState + "</p>");
            // If the stableState is off, it displays the ON button       
            if (stableState=="off") {
              client.println("<p><a href=\"/stable/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/stable/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
