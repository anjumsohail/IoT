#include <Wire.h>

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
