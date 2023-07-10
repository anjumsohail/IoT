#!/usr/bin/env python3
from pyfirmata import Arduino, INPUT, OUTPUT,util
import time
import serial.tools.list_ports

def find_arduino_port():
    print("Hello")
    ports = serial.tools.list_ports.comports()
    arduino_port = None
    for port in ports:
        print(port.description)
        if 'USB-SERIAL CH340' in port.description:
            arduino_port = port.device
            break
    return arduino_port

# Example usage
port = find_arduino_port()
board = None  # Initialize the board object

if __name__ == '__main__':
    if port is not None:
        print(f"Arduino Uno found on port: {port}")
        board = Arduino(port)
        time.sleep(2)  # Wait for the board to initialize
    else:
        print("Arduino Uno not found.")
        exit()
    
    print("Communication successfully started")
    
    # Set the pin modes
    board.digital[13].mode = OUTPUT
    board.digital[3].mode = OUTPUT

    pin = board.get_pin('d:{}:i'.format(2))
    board.analog[0].mode = INPUT
    #pin.mode = INPUT
    pin.enable_reporting()
    board.analog[0].enable_reporting()
       
    it = util.Iterator(board)  
    it.start()  
    #creating an instance of pyfirmata.util.Iterator and calling
    # its start() method. This enables continuous background 
    # monitoring of the digital input pin.
    
    # Blink the built-in LED
    while True:
        board.digital[13].write(1)  # Turn LED on
        board.digital[3].write(1)  # Turn LED on
        analog_value = board.analog[0].read()
        #digital_value = board.digital[2].read()
        digital_value = pin.read()
        print("Analog Input (A0):", analog_value)
        print("Digital Input (Pin 2):", digital_value)
        board.pass_time(1)  # Delay for 1 second
        board.digital[13].write(0)  # Turn LED off
        board.digital[3].write(0)  # Turn LED on
        board.pass_time(1)  # Delay for 1 second

    # Close the connection
    board.exit()
