#pip install gpiozero
from gpiozero import LED, Button
from time import sleep

# Initialize an LED on GPIO pin 17
led = LED(17)

# Initialize a Button on GPIO pin 18
button = Button(18)

# Blink the LED
while True:
    led.toggle()
    sleep(1)

# Detect button press
def on_button_pressed():
    print("Button Pressed")

def on_button_released():
    print("Button Released")

button.when_pressed = on_button_pressed
button.when_released = on_button_released
