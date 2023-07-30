from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
import Adafruit_DHT
import RPi.GPIO as GPIO

# Set the GPIO pin mode to BCM
GPIO.setmode(GPIO.BCM)

# Set to True to define Relay as Normally Open (NO)
RELAY_NO = True
# Set the number of relays
NUM_RELAYS = 3
# Assign each GPIO to a relay
relayGPIOs = [4, 14, 12]

# DHT11 sensor configuration
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 2

# Function to get the relay state
def relay_state(num_relay):
    #print("relayGPIO "+str(relayGPIOs[num_relay - 1]))
    GPIO.setup(relayGPIOs[num_relay - 1], GPIO.IN)
    if RELAY_NO:
        #print("Num Relay -1"+str(num_relay-1))
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
def index(request):
    #return HttpResponse("Hello, world. You're at the polls index.")
    #relay_states = [relay_state(i) for i in range(1, NUM_RELAYS + 1)]
    
    relays = []
    for i in range(len(relayGPIOs)):
        pin = relayGPIOs[i]
        state = relay_state(i)
        relay = {"pin": pin, "state": state}
        relays.append(relay)
    
    context = {
       'relays': relays,
       }
    return render(request, 'index.html', context)

# View for updating relay state
def update(request):
    print(request)
    relay_num = int(request.GET.get("relay"))
    state = int(request.GET.get("state"))
    toggle_relay(relay_num, state)
    return HttpResponse("OK")

# View for temperature data
def temperature(request):
    humidity, temperature = Adafruit_DHT.read_retry(DHT_SENSOR, DHT_PIN)
    print(humidity)
    print(temperature)
    return HttpResponse(str(temperature)+","+str(humidity))
