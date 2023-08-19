import spidev
import time

spi = spidev.SpiDev()
spi.open(0, 0)  # (bus, device)

def send_receive_spi_data(data):
    received_data = spi.xfer2([data])[0]
    return received_data

try:
    while True:
        data_to_send = 84  # Data to send to Arduino
        received_data = send_receive_spi_data(data_to_send)
        print("Sent:", data_to_send, "Received:", received_data)
        time.sleep(1)

except KeyboardInterrupt:
    spi.close()
