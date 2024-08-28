#include <WiFi.h>
//#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "portentah7";    // your network SSID (name)
char pass[] = "moizch123";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;             // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);
const int lane1Lights[] = {2, 3, 4};
const int lane2Lights[] = {5, 6, 7};
const int lane3Lights[] = {8, 9, 10};
const int lane4Lights[] = {11, 12, 14};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("Access Point Web Server");
  pinMode(LEDB,OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(lane1Lights[i], OUTPUT);
    pinMode(lane2Lights[i], OUTPUT);
    pinMode(lane3Lights[i], OUTPUT);
    pinMode(lane4Lights[i], OUTPUT);
  }

  // by default the local IP address of will be 192.168.3.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));

  if(strlen(pass) < 8){    
    Serial.println("Creating access point failed");
    Serial.println("The Wi-Fi password must be at least 8 characters long");
    // don't continue
    while(true);
  }
    
  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  //Create the Access point
  status = WiFi.beginAP(ssid,pass);
  if(status != WL_AP_LISTENING){
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

  printWiFiStatus();
}

int car_num=0;
void loop() {
  car_num=0;
 // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
  
    while (client.connected()) {            // loop while the client's connected
     
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<html><head>");
            client.print("<style>");
            client.print("* { font-family: sans-serif;}");
            client.print("body { padding: 2em; font-size: 2em; text-align: center;}");            
            client.print("input[type=\"text\"] { padding: 10px; font-size: 1em; width: 4em; }");
            client.print("input[type=\"submit\"] { -webkit-appearance: button; -moz-appearance: button; appearance: button; text-decoration: none; color: initial; padding: 10px; }");
            client.print("</style></head>");
            client.print("<body><h1>Enter The Value For 4th Lane</h1>");
            client.print("<form action=\"/submit\" method=\"GET\">");
            client.print("<input type=\"text\" name=\"value\" maxlength=\"2\" placeholder=\"Enter value\" required>");
            client.print("<br><br>");
            client.print("<input type=\"submit\" value=\"Submit\">");
            client.print("</form>");
            client.print("</body></html>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        delay(10);
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /submit?value=1")) {
          car_num=1;               // GET /Hr turns the Red LED on
        }
        if (currentLine.endsWith("GET /submit?value=2")) {
          car_num=2;                // GET /Lr turns the Red LED off
        }
        if (currentLine.endsWith("GET /submit?value=3")){
          car_num=3;                // GET /Hg turns the Green LED on
        }
        if (currentLine.endsWith("GET /submit?value=4")){
          car_num=4;                // GET /Hg turns the Green LED on
        }
        if (currentLine.endsWith("GET /submit?value=5")){
          car_num=5;                // GET /Hg turns the Green LED on
        }
        if (currentLine.endsWith("GET /submit?value=6")){
          car_num=6;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=7")){
          car_num=7;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=8")){
          car_num=8;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=9")){
          car_num=9;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=10")){
          car_num=10;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=11")){
          car_num=11;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=12")){
          car_num=12;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=13")){
          car_num=13;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=14")){
          car_num=14;                // GET /Hg turns the Green LED on
        } 
        if (currentLine.endsWith("GET /submit?value=15")){
          car_num=15;                // GET /Hg turns the Green LED on
        }
        if (currentLine.endsWith("GET /submit?value=**")){
          digitalWrite(LEDB, LOW);    // GET /Hg turns the Green LED on
        }
        if (currentLine.endsWith("GET /submit?value=..")){
          digitalWrite(LEDB, HIGH);    // GET /Hg turns the Green LED on
        }   
        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
   }
   deactivateTrafficLight("lane 1", "green");
   deactivateTrafficLight("lane 1", "yellow");
   activateTrafficLight("lane 1", "red");
   deactivateTrafficLight("lane 2", "green");
   deactivateTrafficLight("lane 2", "yellow");
   activateTrafficLight("lane 2", "red");
   deactivateTrafficLight("lane 3", "green");
   deactivateTrafficLight("lane 3", "yellow");
   activateTrafficLight("lane 3", "red");
   deactivateTrafficLight("lane 4", "green");
   deactivateTrafficLight("lane 4", "yellow");
   activateTrafficLight("lane 4", "red");

   // Infinite loop for dynamically updating the cars
   lanePriority();
   delay(1000);  // Update every 1 second
   Serial.println("\nUpdating number of cars...\n");
}

void lanePriority() {
  // Simulating Arduino input
  int lane1Car = random(0, 11);
  int lane2Car = random(0, 11);
  int lane3Car = random(0, 11);
  int lane4Car = car_num;

  // Put the values in an array
// Create an array to store lane indices and corresponding car values
  int carValues[] = {lane1Car, lane2Car, lane3Car, lane4Car};
  int laneIndices[] = {1, 2, 3, 4}; // Lane indices

  // Sort carValues and laneIndices in descending order based on carValues
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (carValues[j] > carValues[i]) {
        // Swap carValues
        int tempValue = carValues[i];
        carValues[i] = carValues[j];
        carValues[j] = tempValue;
        // Swap laneIndices
        int tempIndex = laneIndices[i];
        laneIndices[i] = laneIndices[j];
        laneIndices[j] = tempIndex;
      }
    }
  }

  // Process lanes in descending order of car values
  for (int i = 0; i < 4; i++) {
    int carNum = carValues[i];
    String laneName = "lane " + String(laneIndices[i]);
    processLane(carNum, laneName);
  }
}

void processLane(int carNum, String laneName) {
  if (carNum > 0) {
    Serial.println("No of cars in " + laneName + " : " + String(carNum));
    Serial.println("Running " + laneName + " for " + String(carNum) + " seconds...");

    deactivateTrafficLight(laneName, "red");

    activateTrafficLight(laneName, "yellow");
    delay(1000);  // Wait for 3 seconds
    deactivateTrafficLight(laneName, "yellow");

    activateTrafficLight(laneName, "green");
    delay(carNum * 1000);  // Wait for carNum seconds
    deactivateTrafficLight(laneName, "green");
    activateTrafficLight(laneName, "red");

    Serial.println(laneName + " finished.\n");
  }
}

void activateTrafficLight(String laneName, String color) {
  int pin = -1;
  if (laneName == "lane 1") {
    pin = lane1Lights[getColorIndex(color)];
  } else if (laneName == "lane 2") {
    pin = lane2Lights[getColorIndex(color)];
  } else if (laneName == "lane 3") {
    pin = lane3Lights[getColorIndex(color)];
  } else if (laneName == "lane 4") {
    pin = lane4Lights[getColorIndex(color)];
  }

  if (pin != -1) {
    Serial.println("Activating " + color + " light on pin " + String(pin) + " for " + laneName);
    // Code to activate the traffic light on pin
    digitalWrite(pin, HIGH);
  }
}

void deactivateTrafficLight(String laneName, String color) {
  int pin = -1;
  if (laneName == "lane 1") {
    pin = lane1Lights[getColorIndex(color)];
  } else if (laneName == "lane 2") {
    pin = lane2Lights[getColorIndex(color)];
  } else if (laneName == "lane 3") {
    pin = lane3Lights[getColorIndex(color)];
  } else if (laneName == "lane 4") {
    pin = lane4Lights[getColorIndex(color)];
  }

  if (pin != -1) {
    Serial.println("Deactivating " + color + " light on pin " + String(pin) + " for " + laneName);
    // Code to deactivate the traffic light on pin
    digitalWrite(pin, LOW);
  }
}

int getColorIndex(String color) {
  if (color == "red") {
    return 2;
  } else if (color == "yellow") {
    return 1;
  } else if (color == "green") {
    return 0;
  }
  return -1;
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your Wi-Fi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
