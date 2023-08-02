#include <SoftwareSerial.h>
SoftwareSerial SIM900A(2,3); // 2 is Rx while 3 is Tx


void setup()
{
SIM900A.begin(9600); // GSM Module Baud rate – communication speed
Serial.begin(9600); // Baud rate of Serial Monitor in the IDE app
Serial.println ("Text Messege Module Ready  Verified");
delay(1000);
SIM900A.println("AT");
  // Wait for a response from the SIM900 module
  delay(500);
  // Check if the SIM900 module has responded
  if (SIM900A.available()) {
    // Read the response from the SIM900 module
    String response = SIM900A.readString();
    // Check if the response contains "OK"
    if (response.indexOf("OK") != -1) {
      Serial.println("SIM card is properly inserted.");  
    } else {
      Serial.println("SIM card is not inserted or not properly inserted.");
    }
  } else {
    Serial.println("No response from the SIM900 module.");
  }

Serial.println ("Type s to send message or r to receive message");
SIM900A.println("AT+CMGF=1"); //Text Mode initialisation
}


void loop()
{
if (Serial.available()>0)
switch(Serial.read())
{
case 's':
SendMessage();
break;
case 'r':
RecieveMessage();
break;
}


if (SIM900A.available()>0)
Serial.write(SIM900A.read());
}


void SendMessage()
{
Serial.println ("Sending Message please wait….");

delay(1000);
Serial.println ("Set SMS Number");
SIM900A.println("AT+CMGS=\"+923180224024\"\r"); // Receiver’s Mobile Number
delay(1000);
Serial.println ("Set SMS Content");
SIM900A.println("Anjum Here IoT Teacher; Test messege has been sent through Arduino Uno not and Not Mobile Phone ");// Messsage content
delay(100);
Serial.println ("Done");
SIM900A.println((char)26);// delay(1000);
Serial.println ("Message sent succesfully");
}


void RecieveMessage()
{
Serial.println ("Receiving Messeges");
delay (1000);
SIM900A.println("AT+CNMI=2,2,0,0,0"); // Receiving Mode Enabled
delay(1000);

 if (SIM900A.available() > 0) {
    // Read the SMS message
    String sms = SIM900A.readString();

    // Display the received SMS on the serial monitor
    Serial.println("Received SMS:");
    Serial.println(sms);
  }

}
