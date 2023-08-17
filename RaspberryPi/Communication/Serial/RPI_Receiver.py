import serial

# Replace '/dev/ttyS0' for UART0 with the appropriate serial port of your Raspberry Pi
# GPIO14 (TXD) - Pin 8    GPIO15 (RXD) - Pin 10
# device file for SPI could be like /dev/spidevX,Y : where X represents the bus number and Y represents the chip select (CS) number: i.e /dev/spidev0.0
# Device File for I2C could be like /dev/i2c-X:  where X is the bus number, so it could be /dev/i2c-1
ser = serial.Serial('/dev/ttyS0', 9600)

try:
    while True:
        # Read data from the serial port
        data = ser.readline().decode('utf-8').strip()
        print(f"Received: {data}")
except KeyboardInterrupt:
    ser.close()
    print("Serial port closed.")
