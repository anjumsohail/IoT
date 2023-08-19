#include <SPI.h>

void setup() {
  SPI.begin();
  Serial.begin(9600);
}

void loop() {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // 1 MHz clock, MSB first, SPI Mode 0
  digitalWrite(SS, LOW); // Select the slave device

  byte dataToSend = 42;
  byte receivedData = SPI.transfer(dataToSend); // Send and receive data simultaneously

  digitalWrite(SS, HIGH); // Deselect the slave device
  SPI.endTransaction();

  Serial.print("Sent: ");
  Serial.print(dataToSend);
  Serial.print(", Received: ");
  Serial.println(receivedData);

  delay(1000);
}
