import smbus
import time

bus = smbus.SMBus(1)  # Use I2C bus 1 on Raspberry Pi

# Arduino I2C address
address = 0x08

try:
    while True:
        message = "Hello from Raspberry Pi!"
        data = [ord(char) for char in message]
        bus.write_i2c_block_data(address, 0, data)

        time.sleep(1)
except KeyboardInterrupt:
    print("I2C communication terminated.")
