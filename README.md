# Cow-Game
A cow wants to eat grass. A farmer wants to protect the cow. You are both the cow and the farmer. Use the cow to eat grass and avoid wolves. Use the farmer to defend the cow by shooting down the wolves.

Game using Gameduino with a standard Arduino. This was implemented on a Duemilanove board.

# Requirements:

* Arduino IDE
* Gameduino library from http://excamera.com/sphinx/gameduino/
* SNESpad controller library
* An older driver for Atmega. The Gameduino library is incompatable with the newer one.
  
The SNES controller is currently set to pins 5, 6, and 7(strobe, clock, data).
The high-score is reseted when the Arduino is turned off.
Necessary drivers and libraries are in this repository. Drop the libraries into the "library" folder. The driver is Windows only.

# Controls:

The cow uses the left half of the controller and the farmer uses the right half. This can be switched with 'select' in the title screen. The upper icon under score shows which half controls what.

* D-pad: move cow
* L: eat grass (must be near tall grass)
* ABXY: move crosshair
* R: fire gun
* Start: start game, pause game
* Select: swap cow and gun controls (d-pad+L = gun, abxy+R = cow), indicated below score, title screen only
* Start + Select: only in-game, reset game

# Resources:

* Gameduino poster: https://drive.google.com/open?id=1tJNmtkq-SvkcLh3P9yD57E0uEu3egMDu
* Background and sprite encoding tool: https://drive.google.com/open?id=18G-xYFF1IhWlKaPzAGVqMoo_PwC7Eu1q
