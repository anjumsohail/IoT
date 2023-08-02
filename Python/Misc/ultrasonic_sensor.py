#python ultrasonic_sensor.py
import RPi.GPIO as GPIO
import time

# Set GPIO pins for the sensor
TRIG_PIN = 23
ECHO_PIN = 24

def setup():
    # Set GPIO mode and setup pins
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(TRIG_PIN, GPIO.OUT)
    GPIO.setup(ECHO_PIN, GPIO.IN)

def get_distance():
    # Send a short pulse to trigger the ultrasonic sensor
    GPIO.output(TRIG_PIN, GPIO.HIGH)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, GPIO.LOW)

    # Measure the time it takes for the echo to return
    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()
    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()

    # Calculate distance using the speed of sound (343 meters per second)
    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 17150

    # Round the distance to 2 decimal places
    distance = round(distance, 2)

    return distance

def cleanup():
    # Clean up GPIO settings
    GPIO.cleanup()

if __name__ == "__main__":
    try:
        setup()
        while True:
            distance = get_distance()
            print(f"Distance: {distance} cm")
            time.sleep(1)

    except KeyboardInterrupt:
        # If Ctrl+C is pressed, exit cleanly
        print("Exiting...")
    finally:
        cleanup()
