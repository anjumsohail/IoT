# Arduino Pins A4 (SDA), A5 (SCL)
# RaspberryPi Pins SDA: GPIO2 (BCM pin 2)  SCL: GPIO3 (BCM pin 3)

import smbus
import time

bus = smbus.SMBus(1)  # Use I2C bus 1 on Raspberry Pi

# Raspberry Pi I2C address
address = 0x08

try:
    while True:
        data = bus.read_i2c_block_data(address, 0, 32)  # Read up to 32 bytes
        message = "".join(chr(byte) for byte in data if byte != 0)
        print(f"Received: {message}")
        time.sleep(1)
except KeyboardInterrupt:
    print("I2C communication terminated.")
