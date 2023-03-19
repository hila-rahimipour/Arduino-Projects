# Arduino-Projects

3 blinking lights with button-
  3 lights connected and 1 button. when the button is pressed, the lights blink.
  
color and laser sensor-
  2 photoresistors connected, 1 relay and one RGB sensor.
  When the photoresistors recieve laser, they active a relay that opens an electronic lock.
  after that, RGB sensor tries to find a spesific color
  
color sensor-
  RGB sensor is connected and prints the RGB values of colors it senses
  
laser photoresistor-
  2 photoresistors are connected. When both with value under 30, both of them sense a laser
  
unknown resistor-
  One known resistor is connected and another unknown resistor. The program finds the value of the unknown resistor
  
  
ohmMeterRelay-
  The program calculates the resistance of an unknown resistor. It displays the resistance value on a LCD screen. 
  Once the resistance is in the correct range, a relay will be activated in order to make an electromagnet work and the LCD screen will show "Open the door!"


laserColor-
  The program calculates the value of 2 photoresistors to find laser light. Once the 2 photoresistors sense the laser light, a code will be displayed on a LCD screen, 
  a red light will light up and a RGB sensor will start working. Once the RGB color recieve the correct color, the LCD screen will display "Congradulations!" and music
  will be played
