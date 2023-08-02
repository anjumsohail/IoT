import RPi.GPIO as GPIO
import time

# Set GPIO pins for the LED and push button
LED_PIN = 18
BUTTON_PIN = 17

def setup():
    # Set GPIO mode and setup pins
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(LED_PIN, GPIO.OUT)
    GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def toggle_led():
    # Toggle the state of the LED
    GPIO.output(LED_PIN, not GPIO.input(LED_PIN))

def check_button():
    # Check if the button is pressed
    return not GPIO.input(BUTTON_PIN)

def cleanup():
    # Clean up GPIO settings
    GPIO.cleanup()

if __name__ == "__main__":
    try:
        setup()
        button_state = False

        while True:
            # Toggle the LED state every second
            toggle_led()

            # Check the push button state
            current_button_state = check_button()

            if current_button_state != button_state:
                button_state = current_button_state
                if button_state:
                    print("Button Pressed")
                else:
                    print("Button Released")

            time.sleep(1)

    except KeyboardInterrupt:
        # If Ctrl+C is pressed, exit cleanly
        print("Exiting...")
    finally:
        cleanup()
