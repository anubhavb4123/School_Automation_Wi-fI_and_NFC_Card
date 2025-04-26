#include <ESP8266WiFi.h> 
// Define GPIO pins for the lights (adjust if necessary 
for your ESP8266 board) 
const int light1 = D1; // GPIO5 
const int light2 = D2; // GPIO4 
const int light3 = D3; // GPIO0 
const int light4 = D4; // GPIO2 
// Set up the Access Point credentials 
const char* ssid = "#Epic Global School_Control"; 
const char* password = "22446688"; // Minimum 8 
characters 
// Create an instance of the WiFi server on port 80 
WiFiServer server(80); 
// HTML content for the control page 
const char webpage[] PROGMEM = R"rawliteral( 
<!DOCTYPE html> 
<html> 
<head> 
    <title>ESP8266 Light Control</title> 
    <meta name="viewport" content="width=device
width, initial-scale=1"> 
    <style> 
        button { 
            font-size: 24px; 
            margin: 10px; 
            padding: 20px; 
            color: DodgerBlue; 
        } 
        h1 { 
            color: Tomato; 
        } 
        h2 { 
            color: orange; 
        } 
</style> 
</head> 
<body> 
<h1>#Epic Global School {Controls}:</h1> 
<button onclick="location.href='/on1'">Corridor 
Light ON</button> 
<button onclick="location.href='/off1'">Corridor 
Light OFF</button><br> 
<button onclick="location.href='/on2'">Class Room 
Light ON</button> 
<button onclick="location.href='/off2'">Class Room 
Light OFF</button><br> 
<button onclick="location.href='/on3'">Water Pump 
ON</button> 
<button onclick="location.href='/off3'">Water Pump 
OFF</button><br> 
<button onclick="location.href='/on4'">Decorative 
Lights ON</button> 
<button onclick="location.href='/off4'">Decorative 
Lights OFF</button> 
<h1>Project Team Member Name:</h1> 
    <h2 style="color:blue;">1: Parul Bajpai { Team Leader 
}</h2> 
    <h2 style="color:blue;">2: Naman Pratap Singh { 
Team Leader }</h2> 
    <h2 style="color:blue;"> 3: Akshay Bajpai { Team 
Leader , Key Contributor } </h2> 
    <h2 style="color:blue;">4: Aishwarya Mishra { Team 
Leader }</h2> 
    <h2 style="color:blue;">5: Vaibhavi Singh { Team 
Leader }</h2>  
<h2 
style="color:red;">...........................................................
 .....END.......................................................</h2> 
</body> 
</html> 
)rawliteral"; 
void setup() { 
Serial.begin(115200); 
// Initialize GPIO pins as OUTPUT 
pinMode(light1, OUTPUT); 
pinMode(light2, OUTPUT); 
pinMode(light3, OUTPUT); 
pinMode(light4, OUTPUT); 
// Turn off all lights initially 
digitalWrite(light1, LOW); 
digitalWrite(light2, LOW); 
digitalWrite(light3, LOW); 
digitalWrite(light4, LOW); 
// Start the Access Point 
WiFi.softAP(ssid, password); 
Serial.println("Access Point started!"); 
Serial.print("IP Address: "); 
Serial.println(WiFi.softAPIP()); 
// Start the server 
server.begin(); 
} 
void loop() { 
// Check if a client is connected 
WiFiClient client = server.available(); 
if (!client) { 
return; 
} 
// Wait for the client to send a request 
String request = client.readStringUntil('\r'); 
Serial.println(request); 
client.flush(); 
// Handle the requests to control lights 
if (request.indexOf("/on1") != -1) { 
digitalWrite(light1, HIGH); 
} else if (request.indexOf("/off1") != -1) { 
digitalWrite(light1, LOW); 
} 
if (request.indexOf("/on2") != -1) { 
digitalWrite(light2, HIGH); 
} else if (request.indexOf("/off2") != -1) { 
digitalWrite(light2, LOW); 
} 
if (request.indexOf("/on3") != -1) { 
digitalWrite(light3, HIGH); 
} else if (request.indexOf("/off3") != -1) { 
digitalWrite(light3, LOW); 
} 
if (request.indexOf("/on4") != -1) { 
digitalWrite(light4, HIGH); 
} else if (request.indexOf("/off4") != -1) { 
digitalWrite(light4, LOW); 
} 
// Send the response 
client.print("HTTP/1.1 200 OK\r\nContent-Type: 
text/html\r\n\r\n"); 
client.print(webpage); 
// Close the connection 
client.stop(); 
}