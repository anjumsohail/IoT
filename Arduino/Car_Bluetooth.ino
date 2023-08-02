int LeftFront = 2;
int Leftback = 3;
int RightFront = 4;
int Rightback = 8;  // Change to a different available pin
int speed = 10;

#include <SoftwareSerial.h>
SoftwareSerial bt(6, 7);

void setup() {
  bt.begin(9600);     /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
  pinMode(LeftFront, OUTPUT);
  pinMode(Leftback, OUTPUT);
  pinMode(RightFront, OUTPUT);
  pinMode(Rightback, OUTPUT);
  pinMode(speed, OUTPUT);
  digitalWrite(speed, HIGH);
}

void loop() {
  if (bt.available()) /* If data is available on the serial port */
  {
    char command = bt.read(); /* Read the command character */
    Serial.println(command);
    processCommand(command); /* Process the received command */
  }
}

void processCommand(char command) {
  switch (command) {
    case 'F':  // Move forward
      moveForward();
      break;
    case 'B':  // Move backward
      moveBackward();
      break;
    case 'L':  // Move left
      moveLeft();
      break;
    case 'R':  // Move right
      moveRight();
      break;
    case 'S':  // Stop
      stopCar();
      break;
    case 'I':  // Position 45 degrees
      setPosition(45);
      break;
    case 'G':  // Position 135 degrees
      setPosition(135);
      break;
    case 'H':  // Position 225 degrees
      setPosition(225);
      break;
    case 'J':  // Position 315 degrees
      setPosition(315);
      break;
    default:
      // Invalid command
      break;
  }
}

void moveForward() {
  digitalWrite(LeftFront, HIGH);
  digitalWrite(Leftback, LOW);
  digitalWrite(RightFront, HIGH);
  digitalWrite(Rightback, LOW);
}

void moveBackward() {
  digitalWrite(LeftFront, LOW);
  digitalWrite(Leftback, HIGH);
  digitalWrite(RightFront, LOW);
  digitalWrite(Rightback, HIGH);
}

void moveLeft() {
  digitalWrite(LeftFront, LOW);
  digitalWrite(Leftback, HIGH);
  digitalWrite(RightFront, HIGH);
  digitalWrite(Rightback, LOW);
}

void moveRight() {
  digitalWrite(LeftFront, HIGH);
  digitalWrite(Leftback, LOW);
  digitalWrite(RightFront, LOW);
  digitalWrite(Rightback, HIGH);
}

void stopCar() {
  digitalWrite(LeftFront, LOW);
  digitalWrite(Leftback, LOW);
  digitalWrite(RightFront, LOW);
  digitalWrite(Rightback, LOW);
}

void setPosition(int position) {
  // Calculate the corresponding motor control values based on the desired position
  if (position == 45) {
    digitalWrite(LeftFront, HIGH);
    digitalWrite(Leftback, LOW);
    digitalWrite(RightFront, LOW);
    digitalWrite(Rightback, LOW);
  } else if (position == 135) {
    digitalWrite(LeftFront, LOW);
    digitalWrite(Leftback, LOW);
    digitalWrite(RightFront, HIGH);
    digitalWrite(Rightback, LOW);
  } else if (position == 225) {
    digitalWrite(LeftFront, LOW);
    digitalWrite(Leftback, LOW);
    digitalWrite(RightFront, LOW);
    digitalWrite(Rightback, HIGH);
  } else if (position == 315) {
    digitalWrite(LeftFront, LOW);
    digitalWrite(Leftback, HIGH);
    digitalWrite(RightFront, LOW);
    digitalWrite(Rightback, LOW);
  }
}
