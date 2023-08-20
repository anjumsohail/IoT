//This code is slave and it send and receive the data
// use sudo i2cdetect -y 1 
#include <Wire.h>
#define SDA_PIN D2       //Declare SCL Pin on NodeMCU 
#define SCL_PIN D1         //Declare SDA Pin on NodeMCU
#define ADDRESS 5

void setup() {
 Wire.begin(SCL_PIN, SDA_PIN,ADDRESS); //start I2C communication on address 8
 Wire.onReceive(receiveEvent);   //register receive event
 Wire.onRequest(requestEvent);   //register request event
 Serial.begin(9600);             //start serial for debug
}

void loop() {
 delay(1000);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      //receive byte as a character
    Serial.print(c);           // print the character 
  }
 Serial.println();             // to newline
}

// function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("HELLO_PICO");  //send string on request
}
