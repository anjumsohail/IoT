#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "<<YourWifi>>";
const char* password = "";
const char* city = "Karachi";
const char* countryCode = "pk";
const char* apiKey = "<<getYourApiKey>>";
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    // Construct the API URL
    String url = "http://api.openweathermap.org/data/2.5/weather?q=";
    url += city;
    url += ",";
    url += countryCode;
    url += "&APPID=";
    url += apiKey;

    // Make the API request
    http.begin(client, url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      String payload = http.getString();
      // Parse JSON response
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      float temperatureKelvin = doc["main"]["temp"];
      float temperatureCelsius = temperatureKelvin - 273.15;
      float humidity = doc["main"]["humidity"];
      Serial.print("Temperature: ");
      Serial.print(temperatureCelsius);
      Serial.print("°C\tHumidity: ");
      Serial.print(humidity);
      Serial.println("%");
    } else {
      Serial.print("Error - HTTP response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(5000); // Wait for 15 seconds before making the next API request
}
