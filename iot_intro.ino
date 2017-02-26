/****Includes****/
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the &onfiguration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ESP8266mDNS.h>          //Allow custom URL

typedef enum color_e {RED, GREEN, BLUE, YELLOW, OFF} color_t;

/*****Initialization*****/
ESP8266WebServer server(80);
const char *ssid = "iot_intro";
void handleRoot(); // implemented below

/****Manage LEDs****/
void handleLEDs() {
    if ( server.hasArg("toggle") ) {
        String str = server.arg(0);
        LEDtoggle(str[0]);
    } else {
        Serial.println("Bad URL.");
        server.send(404, "text/plain", "Bad URL.");
        return;
    }
    server.send(200, "text/plain", ""); // empty response as ACK to GET request.
}

/****Setups****/

//gets called when WiFiManager enters configuration mode
void configModeCallback(WiFiManager *myWiFiManager) {
    LEDfeedback(RED); // waiting for connection
}

void setupWifi() {
    //WiFiManager
    WiFiManager wifiManager;

    //reset saved settings -- Flush flash
    //wifiManager.resetSettings();

    //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(configModeCallback);

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect(ssid);

    // might seem redundant but it's not printed the 1st time:
    Serial.println("local ip");
    Serial.println(WiFi.localIP());
}

void setupServer() {
    server.on("/", handleRoot);
    server.on("/set", handleLEDs);
    server.begin();
    Serial.println("HTTP server started");
}

void setupMDNS() {
    // Add service to MDNS-SD to access the ESP with the URL http://<ssid>.local
    if (MDNS.begin(ssid)) {
        Serial.print("MDNS responder started as http://");
        Serial.print(ssid);
        Serial.println(".local");
    }
    MDNS.addService("http", "tcp", 8080);
}

void setup() {
    pinMode(D8, OUTPUT); // Red
    pinMode(D6, OUTPUT); // Green
    pinMode(D7, OUTPUT); // Blue
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, LOW); // = ON (inverted logic)

    Serial.begin(115200);

    Serial.println("Starting LEDs.");
    LEDfeedback(YELLOW); // state feedback

    Serial.println("Starting WiFi.");
    setupWifi();
    setupServer();
    setupMDNS();

    Serial.println("Setup OK.");
    LEDfeedback(GREEN); // state feedback
}

/****Loop****/
void loop() {
    server.handleClient();
}

/****LEDs****/
void LEDtoggle(char color) {
    switch (color) {
        case 'r' :
            digitalWrite(D8, !digitalRead(D8));
            break;
        case 'g' :
            digitalWrite(D6, !digitalRead(D6));
            break;
        case 'b' :
            digitalWrite(D7, !digitalRead(D7));
            break;
        default:
            Serial.print("LEDtoggle() switch failed!");
    }
}

void LEDfeedback(color_t color) {
    bool R, G, B;

    switch (color) {
        case RED :
            R=1; G=0; B=0;
            break;
        case GREEN :
            R=0; G=1; B=0;
            break;
        case BLUE :
            R=0; G=0; B=1;
            break;
        case YELLOW :
            R=1; G=1; B=0;
            break;
        case OFF :
            R=0; G=0; B=0;
            break;
        default:
            Serial.print("LEDfeedback() switch failed!");
    }
    digitalWrite(D8, R);
    digitalWrite(D6, G);
    digitalWrite(D7, B);
}


/*****WebPage*****/
// Warning: only use simple quotes in the html (no double)
String handleRootHTML = "\
<!doctype html>\
<html>\
<head> <title> IoT into </title> </head>\
<body>\
<form method='get' action='/set'>\
  <br><br> <button type='submit' name='toggle' formtarget='_blank' value='r'>toggle RED  </button>\
  <br><br> <button type='submit' name='toggle' formtarget='_blank' value='g'>toggle GREEN</button>\
  <br><br> <button type='submit' name='toggle' formtarget='_blank' value='b'>toggle BLUE </button>\
</form>\
</body>\
</html>\
";

void handleRoot() {
    server.send(200, "text/html", handleRootHTML);
}
