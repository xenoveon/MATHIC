# MATHIC
HOW TO EDIT CODE

TAKE NOTE: TWO ARDUINO UNOs WILL BE USED (ONE WILL BE MASTER & THE OTHER WILL BE SLAVE)

MASTER: Runs the puzzle/game logic, reads joystick/buttons, chooses question sets, checks answers, and tells the slave what to display.

SLAVE: Receives commands from the master (like start, stop, reset, update timer), and updates the timer digits on the 7-segment display.

STEP 1: Download Arduino IDE via web browser

STEP 2: Download these libraries from the library manager ( left side panel of the Arduino IDE )
          
          -> LiquidCrystal I2C by Frank de Brabander
        
          -> Keypad by Mark Stanley, Alexander Brevig
          
STEP 3: Install MATHIC_CODE_MASTER.ino and MATHIC_CODE_SLAVE.ino and open via Arduino IDE

STEP 4: Connect the Arduino UNO board to your computer using a Firewire (Type B USB Cable)

STEP 5: Modify to your liking

STEP 6: Upload
