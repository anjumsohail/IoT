#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

const char* ssid = "ZONG MBB-E5573-475C"; //Enter SSID
const char* password = ""; //Enter Password
const char* websockets_server_host = "wss://socketsbay.com/wss/v2/1/demo/"; //Enter server adress

using namespace websockets;
WebsocketsClient client;
void setup() {
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }
    // Check if connected to wifi
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }
    Serial.println("Connected to Wifi, Connecting to server.");
    // try to connect to Websockets server
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
    bool connected = client.connect(websockets_server_host);
       
      //  client.setClientECCert(const X509List *cert, const PrivateKey *sk)
      //  client.setClientRSACert(const X509List *cert, const PrivateKey *sk)
      // client.connectSecure(const WSInterfaceString host, const int port, const WSInterfaceString path)

    if(connected) {
        Serial.println("Connecetd!");
        client.send("Hello Server From ESP8266");
    } else {
        Serial.println("Not Connected!");
        
    }
    
    // run callback when messages are received
    client.onMessage([&](WebsocketsMessage message) {
        Serial.print("Got Message: ");
        Serial.println(message.data());
    });
}

void loop() {
    // let the websockets client check for incoming messages
    if(client.available()) {
        client.poll();
    }
    if (Serial.available()) {
      String teststr = Serial.readString();  //read until timeout
      client.send(teststr);
    }
    delay(500);
}
