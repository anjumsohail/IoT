// Import required libraries
#include "ESP8266WiFi.h"
#include "ESPAsyncWebServer.h"

#include <DHT_U.h>
// Set to true to define Relay as Normally Open (NO)
#define RELAY_NO    true
// Set number of relays
#define NUM_RELAYS  3
// Assign each GPIO to a relay
int relayGPIOs[NUM_RELAYS] = { 4, 14, 12 };
#define DHTPIN 2        // GPIO5 (D4)
#define DHTTYPE DHT11   // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
// Other variables
float temperature = 0.0;
float humidity = 0.0;
// Replace with your network credentials
const char* ssid = "ESP";
const char* password = "";
const char* PARAM_INPUT_1 = "relay";
const char* PARAM_INPUT_2 = "state";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
  <script>
    function updateTemperature() {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.DONE) {
          if (xhr.status === 200) {
            var temperatureElement = document.getElementById("temperature");
            temperatureElement.innerHTML = xhr.responseText;
          }
        }
      };
      xhr.open("GET", "/temperature", true);
      xhr.send();
    }

    setInterval(updateTemperature, 2000); // Update temperature every 2 seconds
  </script>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
  <p>Temperature: <span id="temperature">%TEMP_PLACEHOLDER%</span> &deg;C</p>
  <p>Humidity: %HUMIDITY_PLACEHOLDER% %</p>
  <script>
    function toggleCheckbox(element) {
      var xhr = new XMLHttpRequest();
      if (element.checked) {
        xhr.open("GET", "/update?relay=" + element.id + "&state=0", true);
      } else {
        xhr.open("GET", "/update?relay=" + element.id + "&state=1", true);
      }
      xhr.send();
    }
  </script>
</body>
</html>
)rawliteral";
String relayState(int numRelay) {
  if (RELAY_NO) {
    if (digitalRead(relayGPIOs[numRelay - 1])) {
      return "";
    } else {
      return "checked";
    }
  } else {
    if (digitalRead(relayGPIOs[numRelay - 1])) {
      return "checked";
    } else {
      return "";
    }
  }
  return "";
}

String processor(const String& var) {
  if (var == "BUTTONPLACEHOLDER") {
    String buttons = "";
    for (int i = 1; i <= NUM_RELAYS; i++) {
      String relayStateValue = relayState(i);
      buttons += "<h4>Relay #" + String(i) + " - GPIO " + relayGPIOs[i - 1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" " + relayStateValue + "><span class=\"slider\"></span></label>";
    }
    return buttons;
  }
  if (var == "TEMP_PLACEHOLDER") {
    return String(temperature);
  }
  if (var == "HUMIDITY_PLACEHOLDER") {
    return String(humidity);
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
    // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  // Set all relays to off when the program starts - if set to Normally Open (NO), the relay is off when you set the relay to HIGH
  for (int i = 1; i <= NUM_RELAYS; i++) {
    pinMode(relayGPIOs[i - 1], OUTPUT);
    if (RELAY_NO) {
      digitalWrite(relayGPIOs[i - 1], HIGH);
    } else {
      digitalWrite(relayGPIOs[i - 1], LOW);
    }
  }
  // Start ESP8266 in AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("Access Point Mode Activated");
  Serial.print("SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  // Send a GET request to <ESP_IP>/update?relay=<inputMessage>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
    String inputMessage;
    String inputParam;
    String inputMessage2;
    String inputParam2;
    // GET input1 value on <ESP_IP>/update?relay=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1) & request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam2 = PARAM_INPUT_2;
      if (RELAY_NO) {
        Serial.print("NO ");
        digitalWrite(relayGPIOs[inputMessage.toInt() - 1], !inputMessage2.toInt());
      } else {
        Serial.print("NC ");
        digitalWrite(relayGPIOs[inputMessage.toInt() - 1], inputMessage2.toInt());
      }
    } else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage + inputMessage2);
    request->send(200, "text/plain", "OK");
  });
  // Route for temperature data
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest* request) {
    String tempData = String(temperature);
    request->send(200, "text/plain", tempData);
  });
  // Start server
  server.begin();
}
void loop() {
     // ...
  delay(2000); // Wait for 2 seconds before reading again
delay(delayMS);

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    temperature=event.temperature;
    }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    humidity=event.relative_humidity;
    
  }
    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.println(F("°C"));
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.println(F("%"));




}
