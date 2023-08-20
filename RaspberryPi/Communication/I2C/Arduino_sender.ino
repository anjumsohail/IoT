#include <Wire.h>

// Arduino Pins A4 (SDA), A5 (SCL)
// NodeMCU Pins D1(GPIO5) SCL , D2(GPIO4) SDA
// The Wire.h Library curretly supports NodeMCU only as Master
// RaspberryPi Pins SDA: GPIO2 (Board pin 3)  SCL: GPIO3 (Board pin 5)
int a=0;
void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);
}

void loop() 
{
  a=a+1;
  String message = "Hello from Arduino! " + String(a);
  Wire.beginTransmission(0x08);  // I2C address of the Raspberry Pi slave
  Wire.write(message.c_str());  // Convert String to const char* using c_str()
  Wire.endTransmission();
  delay(1000);  // Send the message every 1 second
}
