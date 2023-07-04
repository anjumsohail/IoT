#define BLYNK_TEMPLATE_ID "Your Template ID"
#define BLYNK_TEMPLATE_NAME "Your Template Name"
#define BLYNK_AUTH_TOKEN "Your Auth Token"
char ssid[] = "Wokwi-GUEST"; //nama hotspot yang digunakan
char pass[] = ""; //password hotspot yang digunakan
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial // Defines the object that is used for printing
//#define BLYNK_DEBUG        // Optional, this enables more detailed prints




#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


BlynkTimer timer;
int previousButtonState = HIGH;
int counter = 0;
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if (value==1)
  {digitalWrite(26,HIGH);}
  else
  {digitalWrite(26,LOW);}
  Blynk.virtualWrite(V1, value);
    Serial.println(value);
}
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}
void setup()
{
   pinMode(26,OUTPUT);
 pinMode(27, INPUT_PULLUP);
  // Debug console
  Serial.begin(9600);
  delay(500);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); //memulai Blynk
 timer.setInterval(1000L, myTimerEvent);
}


BLYNK_CONNECTED()
{
  Serial.print("Blynk Connected");


}
void loop()
{


  Blynk.run();
 timer.run();
int switchState = digitalRead(27); // Assuming switch is connected to D3
  if (switchState != previousButtonState)
  {
    if (switchState==LOW) {
    counter++;
    Blynk.virtualWrite(V3, counter); // Send information to virtual pin V1
    }
  }


previousButtonState = switchState;}




#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Your Template ID"
#define BLYNK_TEMPLATE_NAME "Your Template Name"
#define BLYNK_AUTH_TOKEN "Your Auth Token"


#define BLYNK_DEVICE_NAME "Anjum"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h> //Library untuk DHT


char auth[] = BLYNK_AUTH_TOKEN ; //Auth Token


char ssid[] = "Wokwi-GUEST"; //nama hotspot yang digunakan
char pass[] = ""; //password hotspot yang digunakan


const int DHT_PIN = 15;


int value0, value1, value2, value3, value6;


byte LED_R = 26;
byte LED_Y = 27;
byte LED_G = 14;
byte LED_B = 12;


DHTesp dht;


BlynkTimer timer;


//function untuk pengiriman sensor
void sendSensor()
{
 TempAndHumidity  data = dht.getTempAndHumidity();


//menampilkan temperature pada Serial monitor
Serial.print("% Temperature: ");
Serial.print(data.temperature);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(data.humidity);
Serial.println("% ");


Blynk.virtualWrite(V4, data.temperature); //mengirimkan data temperatur ke Virtual pin VO di Blynk Cloud
Blynk.virtualWrite(V5, data.humidity); //mengirimkan data kelemaban ke Virtual pin V1 di Blynk Cloud
}


BLYNK_WRITE(V0)
{
  value0 = param.asInt();
  digitalWrite(LED_R, value0);
  Blynk.virtualWrite(V7, value0);
  cekAllLed();
}


BLYNK_WRITE(V1)
{
  value1 = param.asInt();
  digitalWrite(LED_Y, value1);
  Blynk.virtualWrite(V8, value1);
  cekAllLed();
}


BLYNK_WRITE(V2)
{
  value2 = param.asInt();
  digitalWrite(LED_G, value2);
  Blynk.virtualWrite(V9, value2);
  cekAllLed();
}


BLYNK_WRITE(V3)
{
  value3 = param.asInt();
  digitalWrite(LED_B, value3);
  Blynk.virtualWrite(V10, value3);
  cekAllLed();
}


BLYNK_WRITE(V6)
{
  value6 = param.asInt();


  digitalWrite(LED_R, value6);
  Blynk.virtualWrite(V7, value6);
  Blynk.virtualWrite(V0, value6);
 
  digitalWrite(LED_Y, value6);
  Blynk.virtualWrite(V8, value6);
  Blynk.virtualWrite(V1, value6);


  digitalWrite(LED_G, value6);
  Blynk.virtualWrite(V9, value6);
  Blynk.virtualWrite(V2, value6);


  digitalWrite(LED_B, value6);
  Blynk.virtualWrite(V10, value6);
  Blynk.virtualWrite(V3, value6);
}


void cekAllLed(){
  if(value0 == 1 && value1 == 1 && value2 == 1 && value3 == 1){
    Blynk.virtualWrite(V6, 1);
  }
  else{
    Blynk.virtualWrite(V6, 0);
  }
  // if(value0 == 0 && value1 == 0 && value2 == 0 && value3 == 0){
  //   Blynk.virtualWrite(V6, 0);
  // }
}


void setup()
{
// Debug console
Serial.begin(115200); //serial monitor menggunakan bautrate 9600
dht.setup(DHT_PIN, DHTesp::DHT22);
pinMode(LED_R, OUTPUT);
pinMode(LED_Y, OUTPUT);
pinMode(LED_G, OUTPUT);
pinMode(LED_B, OUTPUT);
Blynk.begin(auth, ssid, pass); //memulai Blynk
timer.setInterval(1000, sendSensor); //Mengaktifkan timer untuk pengiriman data 1000ms
}


void loop()
{


Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}
