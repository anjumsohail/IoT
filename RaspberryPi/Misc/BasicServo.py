import RPi.GPIO as GPIO
import time

# Set the GPIO mode to BCM
GPIO.setmode(GPIO.BCM)

# Set the GPIO pin for the servo
servo_pin = 18

# Set the PWM frequency (you may need to adjust this value to suit your servo)
pwm_frequency = 50
max_duty =12.5
min_duty =2.5
# Set the angle range supported by your servo (usually 0 to 180 degrees)
angle_range = 180

# Initialize the GPIO pin for PWM control
GPIO.setup(servo_pin, GPIO.OUT)
pwm = GPIO.PWM(servo_pin, pwm_frequency)

# Function to set the angle of the servo
def set_angle(angle):
    duty_cycle = ((angle / angle_range) * (max_duty - min_duty)) + min_duty
    pwm.ChangeDutyCycle(duty_cycle)
    time.sleep(0.3)  # Give the servo some time to move

# Main function
if __name__ == "__main__":
    try:
        # Start PWM
        pwm.start(0)

        # Move the servo to the center position (90 degrees)
        set_angle(90)
        time.sleep(1)

        # Move the servo to the leftmost position (0 degrees)
        set_angle(0)
        time.sleep(1)

        # Move the servo to the rightmost position (180 degrees)
        set_angle(180)
        time.sleep(1)

        # Move the servo back to the center position (90 degrees)
        set_angle(90)
        time.sleep(1)

    except KeyboardInterrupt:
        # If the user presses Ctrl+C, stop PWM and clean up
        pwm.stop()
        GPIO.cleanup()
