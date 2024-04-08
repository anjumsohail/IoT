//======================================================================//

#include <SPI.h>
#include <LoRa.h>

//======================================================================//

#define PIN_LORA_COPI   13
#define PIN_LORA_CIPO   12
#define PIN_LORA_SCK    14
#define PIN_LORA_CS     15
#define PIN_LORA_RST    5
#define PIN_LORA_DIO0   4

#define LORA_FREQUENCY  433E6

//======================================================================//

int counter = 0;

//======================================================================//

void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1500);
  Serial.println ("LoRa Sender");

  LoRa.setPins (PIN_LORA_CS, PIN_LORA_RST, PIN_LORA_DIO0);
  LoRa.setSPIFrequency (20000000);
  LoRa.setTxPower (20);

  if (!LoRa.begin (LORA_FREQUENCY)) {
    Serial.println ("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.print ("LoRa initialized with frequency ");
    Serial.println (LORA_FREQUENCY);
  }
}

//======================================================================//

void loop() {
  Serial.print ("Sending packet: ");
  Serial.println (counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print ("Hello LoRa ");
  LoRa.print (counter);
  LoRa.endPacket();

  counter++;

  delay (3000);
}

//======================================================================//

