from flask import Flask, render_template, request
import Adafruit_DHT
import RPi.GPIO as GPIO

# Set the GPIO pin mode to BCM
GPIO.setmode(GPIO.BCM)

# Set to True to define Relay as Normally Open (NO)
RELAY_NO = True
# Set the number of relays
NUM_RELAYS = 3
# Assign each GPIO to a relay
relayGPIOs = [16, 20, 21]

# DHT11 sensor configuration
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 4

# Create Flask app
app = Flask(__name__)

# Function to get the relay state
def relay_state(num_relay):
    if RELAY_NO:
        if GPIO.input(relayGPIOs[num_relay - 1]):
            return ""
        else:
            return "checked"
    else:
        if GPIO.input(relayGPIOs[num_relay - 1]):
            return "checked"
        else:
            return ""

# Function to toggle the relay state
def toggle_relay(relay_num, state):
    if RELAY_NO:
        GPIO.output(relayGPIOs[relay_num - 1], not state)
    else:
        GPIO.output(relayGPIOs[relay_num - 1], state)

# View for the index page
@app.route("/")
def index():
    return render_template("index.html", num_relays=NUM_RELAYS, relay_state=relay_state, relayGPIOs=relayGPIOs)

# Route for updating relay state
@app.route("/update", methods=["GET"])
def update():
    relay_num = int(request.args.get("relay"))
    state = int(request.args.get("state"))
    toggle_relay(relay_num, state)
    return "OK"

# Route for temperature data
@app.route("/temperature")
def temperature():
    humidity, temperature = Adafruit_DHT.read_retry(DHT_SENSOR, DHT_PIN)
    print(humidity,temperature);
    return f"{humidity},{temperature}"

if __name__ == "__main__":
    # Setup GPIO pins
    for gpio_pin in relayGPIOs:
        GPIO.setup(gpio_pin, GPIO.OUT)
        if RELAY_NO:
            GPIO.output(gpio_pin, GPIO.HIGH)
        else:
            GPIO.output(gpio_pin, GPIO.LOW)

    app.run(host="0.0.0.0", port=8080)
