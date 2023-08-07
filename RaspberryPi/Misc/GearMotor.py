import RPi.GPIO as GPIO
import time

# Set the GPIO mode to BCM
GPIO.setmode(GPIO.BCM)

# Define GPIO pins for motor control
IN1 = 17
IN2 = 18
IN3 = 22
IN4 = 23
ENA = 19

# Set GPIO pins as OUTPUT
GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)
GPIO.setup(IN3, GPIO.OUT)
GPIO.setup(IN4, GPIO.OUT)
GPIO.setup(ENA, GPIO.OUT)

# Create PWM object for speed control
pwm = GPIO.PWM(ENA, 100)  # 100 Hz frequency, you can adjust it as needed

# Function to control motor direction and speed for left side
def set_left_motor_direction_and_speed(direction, speed):
    GPIO.output(IN1, direction)
    GPIO.output(IN2, not direction)
    pwm.start(speed)

# Function to control motor direction and speed for right side
def set_right_motor_direction_and_speed(direction, speed):
    GPIO.output(IN3, direction)
    GPIO.output(IN4, not direction)
    pwm.start(speed)

# Function to make the car move forward
def move_forward(speed):
    set_left_motor_direction_and_speed(True, speed)
    set_right_motor_direction_and_speed(True, speed)

# Function to make the car move backward
def move_backward(speed):
    set_left_motor_direction_and_speed(False, speed)
    set_right_motor_direction_and_speed(False, speed)

# Function to stop the car
def stop_car():
    set_left_motor_direction_and_speed(False, 0)
    set_right_motor_direction_and_speed(False, 0)

# Main function
if __name__ == "__main__":
    try:
        # Set the motor speed (0 to 100, where 100 is full speed)
        motor_speed = 50

        # Move the car forward for 5 seconds
        move_forward(motor_speed)
        time.sleep(5)

        # Move the car backward for 5 seconds
        move_backward(motor_speed)
        time.sleep(5)

        # Stop the car
        stop_car()
        time.sleep(1)

        # Cleanup
        pwm.stop()
        GPIO.cleanup()

    except KeyboardInterrupt:
        # If the user presses Ctrl+C, stop the car and clean up
        stop_car()
        pwm.stop()
        GPIO.cleanup()
