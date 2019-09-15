Play Space Invaders and T-Rex Run on an Arduino Uno!

# Rules
## Space Invaders
The purpose of this game is to kill all invaders by shooting them, before they can move past you or kill you in turn. You will control a cannon through a potentiometer and a button; the potentiometer controls where you cannon points, while the button fires the cannon. You must shoot the invaders a number of times depending on their strengths.
* Strength 1: red
* Strength 2: orange
* Strength 3: yellow
* Strength 4: green
* Strength 5: blue
* Strength 6: purple
* Strength 7: white

You start out with 3 lives, and lose a life each time an invader reaches the bottom of the screen.

## T-Rex Run
You control a T-Rex dinosaur, and you must dodge all cacti and birds by either jumping or ducking. You start out with three lives, and lose a life each time you are hit. The game ends when you reach 0. 

# Materials
These are the materials that you will need:
* 1 Arduino Uno
* 1 Adafruit 16x32 RGB Matrix Panel
* 1 breadboard
* 1 potentiometer
* 1 button
* 1 Piezo speaker
* 1 flat ribbon cable
* 1 USB cable
* 1 5V power converter
* wires
* 3 1K resistors

# Setup

This is a simplified set of instructions on how to set up the Arduino Uno. For more information, please email sriman.chilam@gmail.com.

1. Insert all GND wires on Arduino to the Ground Bus on the breadboard.

2. Insert all wires to pins accordingly.

    * 2 -> R1
    * 3 -> G1
    * 4 -> B1
    * 5 -> R2
    * 6 -> G2
    * 7 -> B2
    * 8 -> CLK
    * 9 -> OE
    * A0 -> A
    * A1 -> B
    * A2 -> C
    * A3 -> LAT

