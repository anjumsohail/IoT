#include <Wire.h>

# Arduino Pins A4 (SDA), A5 (SCL)
# RaspberryPi Pins SDA: GPIO2 (BCM pin 2)  SCL: GPIO3 (BCM pin 3)

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
