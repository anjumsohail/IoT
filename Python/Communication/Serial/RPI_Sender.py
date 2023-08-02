import serial
import time

# Replace '/dev/ttyS0' with the appropriate serial port of your Raspberry Pi
ser = serial.Serial('COM9', 9600)

try:
    while True:
        ser.write(b'Hello from Raspberry Pi!\n')
        time.sleep(1)
except KeyboardInterrupt:
    ser.close()
    print("Serial communication terminated.")
