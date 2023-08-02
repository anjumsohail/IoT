import serial

# Replace '/dev/ttyS0' with the appropriate serial port of your Raspberry Pi
ser = serial.Serial('COM9', 9600)

try:
    while True:
        # Read data from the serial port
        data = ser.readline().decode('utf-8').strip()
        print(f"Received: {data}")
except KeyboardInterrupt:
    ser.close()
    print("Serial port closed.")
