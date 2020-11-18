# cooptimer
/* TIME CONTROLLER PROGRAM - cooptimer

Created by Simon Nyrup Madsen 2014-2020 - simon.nyrup@gmail.com

This program is designes to control relays on the basis of timers and manual inputs on a keypad.

Its features includes:
 * Timekeeping and setting timers
 * Calculation of todays sunset and sunrise for automatic timekeeping
 * Control of 8 relays
 * Keypad and display for manual control.

In this version, the program is designed to manage a chicken coop with automatic lights as well as doors and nests operated by lineary actuators.

Hardware set-up:
 *  Arduino Uno/Mega (Disable code for the board, that is not relevant to you)
 *  Clock-mocule DS3231 (Insert rechargeable battery LIR2032. Connect to SCL and SDA on Arduino and supplied from 3.3 V outlet and GND on Arduino)
 *  Relay-module (Connect to GND on arduino on pin side - but with seperate GND and power supply to VCC-JD)
 *  LCD Keypad Shield
 *  Temperature sensor S18B20 (Currently disabled in code)
 *  Lineary actuators
*/
