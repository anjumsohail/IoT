import spidev

spi = spidev.SpiDev()
spi.open(0, 0)  # (bus, device)
spi.mode = 0

try:
    while True:
        received_data = spi.xfer2([0])  # Send dummy data to initiate SPI transaction
        received_value = received_data[0]
        print("Received:", received_value)

except KeyboardInterrupt:
    spi.close()
