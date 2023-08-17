#include <Wire.h>
# Arduino Pins A4 (SDA), A5 (SCL)
# RaspberryPi Pins SDA: GPIO2 (BCM pin 2)  SCL: GPIO3 (BCM pin 3)

void setup() {
  Wire.begin(0x08); // I2C address of the Arduino slave
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
}
