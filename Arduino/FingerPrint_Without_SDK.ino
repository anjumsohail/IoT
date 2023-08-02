#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

// Commands
#define CMD_GET_IMAGE       0x01
#define CMD_IMAGE2TZ        0x02
#define CMD_MATCH           0x03
#define CMD_REG_MODEL       0x05
#define CMD_STORE           0x06
#define CMD_DELETE          0x0C
#define CMD_EMPTY           0x0D
#define CMD_READ_SYS_PARAM  0x0F

// Responses
#define RESP_OK             0x00
#define RESP_NO_FINGER      0x02
#define RESP_MISMATCH       0x08
#define RESP_FAIL           0x0F

void setup() {
  Serial.begin(9600);
  mySerial.begin(57600);
  delay(1000);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
      case 'R':
        registerFingerprint();
        break;
      case 'M':
        matchFingerprint();
        break;
    }
  }
}

void registerFingerprint() {
  Serial.println("Place your finger on the sensor...");
  if (sendCommand(CMD_GET_IMAGE) != RESP_OK) {
    Serial.println("Failed to get fingerprint image.");
    return;
  }

  if (sendCommand(CMD_IMAGE2TZ, 1) != RESP_OK) {
    Serial.println("Failed to convert image to template.");
    return;
  }

  Serial.println("Remove your finger.");
  delay(2000);

  Serial.println("Place the same finger again...");
  if (sendCommand(CMD_GET_IMAGE) != RESP_OK) {
    Serial.println("Failed to get fingerprint image.");
    return;
  }

  if (sendCommand(CMD_IMAGE2TZ, 2) != RESP_OK) {
    Serial.println("Failed to convert image to template.");
    return;
  }

  if (sendCommand(CMD_REG_MODEL) == RESP_OK) {
    Serial.println("Fingerprint registered successfully.");
  } else {
    Serial.println("Failed to register fingerprint.");
  }
}

void matchFingerprint() {
  Serial.println("Place your finger on the sensor...");
  if (sendCommand(CMD_GET_IMAGE) != RESP_OK) {
    Serial.println("Failed to get fingerprint image.");
    return;
  }

  if (sendCommand(CMD_IMAGE2TZ, 1) != RESP_OK) {
    Serial.println("Failed to convert image to template.");
    return;
  }

  Serial.println("Remove your finger.");
  delay(2000);

  Serial.println("Place the finger to match...");
  if (sendCommand(CMD_GET_IMAGE) != RESP_OK) {
    Serial.println("Failed to get fingerprint image.");
    return;
  }

  if (sendCommand(CMD_IMAGE2TZ, 2) != RESP_OK) {
    Serial.println("Failed to convert image to template.");
    return;
  }

  if (sendCommand(CMD_MATCH) == RESP_OK) {
    Serial.println("Fingerprint matched!");
  } else {
    Serial.println("Fingerprint did not match.");
  }
}

byte sendCommand(byte command, byte param1 = 0, byte param2 = 0, byte param3 = 0, byte param4 = 0) {
  //byte packet[] = { 0xEF, 0x01, param1, param2, param3, param4, command, param1 ^ param2 ^ param3 ^ param4 ^ command, 0xFF, 0xFF, 0xFF, 0xFF };
  byte packet[] = {
  0xEF,                          // Header byte 1
  0x01,                          // Header byte 2
  param1, param2, param3, param4, // Parameters for the command
  command,                       // Command byte
  param1 ^ param2 ^ param3 ^ param4 ^ command,  // Checksum byte using XOR (^) operator 
  0xFF, 0xFF, 0xFF, 0xFF          // Tail bytes
};

/*
Header bytes: The header bytes 0xEF and 0x01 indicate the start of the packet and are used to identify the beginning of the command.

Parameters: The param1, param2, param3, and param4 variables represent the parameters specific to the command being sent. These parameters can vary depending on the command you are executing. They are included in the packet to provide additional information or data required by the command.

Command byte: The command variable represents the specific command you want to send to the fingerprint sensor. It specifies the operation you want to perform, such as enrollment, verification, or matching.

Checksum byte: The checksum byte is calculated by performing an XOR operation (^) on param1, param2, param3, param4, and command. The checksum is used to verify the integrity of the packet during transmission. It ensures that the received packet is not corrupted.
XOR is a bitwise operation that compares corresponding bits of two operands and returns a new value where each bit is the result of the XOR operation on the corresponding bits of the operands.

Tail bytes: The tail bytes 0xFF are used to mark the end of the packet.

By constructing the packet in this format, you create a sequence of bytes that can be sent to the fingerprint sensor to execute a specific command with the required parameters.
*/


  mySerial.write(packet, sizeof(packet));  // Send Packet via Serial port

  byte response[12];  //  array of type byte with a length of 12 elements to store the response received from the fingerprint sensor.
  int timeout = 1000;
  int idx = 0;

  while (!mySerial.available() && timeout > 0) {
    delay(1);
    timeout--;
  }

  if (timeout == 0) {
    Serial.println("Timeout");
    return RESP_FAIL;
  }

  while (mySerial.available() && idx < sizeof(response)) {
    response[idx] = mySerial.read();			// Reading Response from Buffer and saving to the Array
    idx++;
  }

  if (idx != sizeof(response)) // Verifies that the response received from the fingerprint sensor matches the expected size.
  {
    Serial.println("Invalid response");
    return RESP_FAIL;
  }

  if (response[0] != 0xEF || response[1] != 0x01) {
    Serial.println("Invalid packet header");
    return RESP_FAIL;
  }

  if (response[9] != 0x00 || response[10] != 0x00 || response[11] != 0x00 || response[12] != 0x00) {
    Serial.println("Invalid packet tail");
    return RESP_FAIL;
  }

  return response[7];
}
