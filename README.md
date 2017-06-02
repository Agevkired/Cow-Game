# Cow-Game
A cow wants to eat grass. A farmer wants to protect the cow. You control both the cow and the farmer. Use the cow to eat grass and avoid wolves. Use the farmer to defend the cow by shooting down the wolves.

Game using Gameduino with a standard Arduino. This was implemented on a Duemilanove board.

# Requirements:

* Gameduino library from http://excamera.com/sphinx/gameduino/
* SNES controller library
* An older driver for Atmega. The Gameduino library is incompatable with the newer one.
  
The SNES controller is currently set to pins 5, 6, and 7.
The high-score is reseted when the Arduino is turned off.

# Controls:

The cow uses the left half of the controller and the farmer uses the right half. This can be switched with 'select' in the title screen. The upper icon under score shows which half controls what.

* D-pad: move cow
* L: eat grass (must be near tall grass)
* ABXY: move crosshair
* R: fire gun
* Start: start game
* Select: only in title screen, cow and gun controls swap sides
* Start + Select: only in-game, reset game
