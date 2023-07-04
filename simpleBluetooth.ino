#include<SoftwareSerial.h>
/* Create object named bt of the class SoftwareSerial */
SoftwareSerial bt(2,3); /* (Rx,Tx) */
boolean chk=false;
void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
}
void loop() {
      if (bt.available()) /* If data is available on serial port */
    {
     Serial.write(bt.read()); /* Print character received on to the serial monitor */
     delay(100);
     //bt.println("I Got that");
     
    }


if (Serial.available())
{
       bt.write(Serial.read()); /* Print character received on to the serial monitor */
       //Serial.write(Serial.read());
       //bt.println(Serial.read());
}
}
