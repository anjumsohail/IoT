# pip install Adafruit_DHT
# to Run : python3 dht11_sensor.py

import Adafruit_DHT
import time

# Set the GPIO pin where the DHT11 sensor is connected,GPIO 4 (BCM numbering) as the data pin.
DHT_PIN = 4
# DHT sensor type (DHT11)
DHT_TYPE = Adafruit_DHT.DHT11

def read_dht_sensor():
    # Attempt to get a sensor reading
    humidity, temperature = Adafruit_DHT.read_retry(DHT_TYPE, DHT_PIN)

    # Return values as None if reading fails
    if humidity is None or temperature is None:
        return None, None

    # Round the values to 2 decimal places
    humidity = round(humidity, 2)
    temperature = round(temperature, 2)

    return humidity, temperature

if __name__ == "__main__":
    try:
        while True:
            # Read data from DHT11 sensor
            humidity, temperature = read_dht_sensor()

            if humidity is not None and temperature is not None:
                # Print the data to the console
                print(f"Temperature: {temperature} °C, Humidity: {humidity} %")

            # Wait for one second before the next reading
            time.sleep(1)

    except KeyboardInterrupt:
        # If Ctrl+C is pressed, exit cleanly
        print("Exiting...")

