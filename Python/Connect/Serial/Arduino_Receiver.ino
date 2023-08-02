void setup() {
  Serial.begin(9600); // Set the baud rate to match the Raspberry Pi
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.println(c);
  }
}
