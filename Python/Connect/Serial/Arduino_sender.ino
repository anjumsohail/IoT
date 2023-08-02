void setup() {
  Serial.begin(9600); // Set the baud rate to match the Raspberry Pi
}

void loop() {
  Serial.println("Hello from Arduino!");
  delay(1000); // Send the message every 1 second
}
