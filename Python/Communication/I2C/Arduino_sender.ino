#include <Wire.h>

void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(9600);
}

void loop() 
{
  Wire.beginTransmission(0x08);  // I2C address of the Raspberry Pi slave
  Wire.write("Hello from Arduino!");
  Wire.endTransmission();

  delay(1000);  // Send the message every 1 second
}
