#sudo apt update
#sudo apt install python3-pip i2c-tools
#pip3 install adafruit-circuitpython-lcd

#Connect the SDA pin of the LCD to the SDA pin of the Raspberry Pi (usually GPIO 2).
#Connect the SCL pin of the LCD to the SCL pin of the Raspberry Pi (usually GPIO 3).
#Connect the VCC pin of the LCD to the 5V pin of the Raspberry Pi.
#Connect the GND pin of the LCD to the GND pin of the Raspberry Pi.

import board
import busio
import adafruit_character_lcd.character_lcd_i2c as character_lcd

# Define I2C bus
i2c = busio.I2C(board.SCL, board.SDA)

# Set up the LCD
lcd_columns = 16
lcd_rows = 2
lcd = character_lcd.Character_LCD_I2C(i2c, lcd_columns, lcd_rows)

# Clear the LCD screen
lcd.clear()

# Display a message
lcd.message = "Hello, LCD!\nWelcome to RPi!"

# Wait for a few seconds
time.sleep(5)

# Clear the LCD screen
lcd.clear()

