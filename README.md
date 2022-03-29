# LCD_Weather_Project
## Report
Full demo link: https://www.youtube.com/watch?v=M_DYicAg1oM
* Complexity 1: https://youtu.be/hL-DuIulUEs
* Complexity 2: https://youtu.be/6WCgEKgCQlw
* Complexity 3: https://www.youtube.com/watch?v=VWSfH3VUZlo

## Project Description
In my room temperature display project, I am utilizing USART to send a button press from one
microcontroller (Transmitter) to another (Receiver) to trigger a temperature measure.
Temperature is measured by LM35, and it is displayed on the LCD screen. By pressing one of
the buttons, the user can view the temperature in Fahrenheit or Celsius. An “Icon” symbol is also
displayed and if the temperature is below 21C, then a snowflake (*) icon is displayed and if the
temperature is above 21C, a ‘+’ symbol is displayed. A user can also view the highest and the
lowest temperatures, both of which are saved to EEPROM, by pressing the second button. Of
course, all the temperatures ever displayed on the LCD have a special character degree symbol in
front of them.

## User Guide
### Rules:
To turn on the temperature display project, connect the board to power through the USB cable.
Then, notice that on the LCD, a temperature is displayed in Celsius, because this is the default
unit. If viewing temperature in Celsius is inconvenient, press the lowest of the two black buttons
and the temperature will become converted to Fahrenheit and displayed. If the temperature is
below 21C, a symbol next to an “Icon” display will be a snowflake, and a plus if above 21C. To
view the highest and lowest temperature, press the first of the two buttons and the maximum and
minimum temperatures will be displayed on the LCD screen. To turn off the board, remove the
USB wire from the power source.

### Controls:
To turn the board on, connect the USB cable to a power source. To control the scale in which the
temperature is, press the lowest of the two buttons, and the temperature will switch between
Celsius and Fahrenheit. The upper button controls the display of data from the EEPROM, which
is the minimum and maximum temperature.

### Special Considerations
For the project to work, the only need is power supply. LM35 nor EEPROM have no special
conditions or setup to be activated.

## Source File Description:
* File lcd_display_temp.c this file includes all the functionality for displaying current
temperature, minimum, and maximum temperature. Switching between Fahrenheit and
Celsius and button control are also included in this file.
  * Outside Sources:
    * https://www.electronicwings.com/avr-atmega/lm35-temperature-sensor-interfacing-with-atmega1632
    * https://www.electronicwings.com/avr-atmega/atmega16-eeprom
    * https://maxembedded.com/2011/06/lcd-interfacing-with-avr/
    * https://www.handsonembedded.com/lcd16x2-hd44780-tutorial-5/  

* File transmit_usart.c This file is responsible for implementing the functionality of the
microcontroller that plays the role of a transmitter in the USART.
  * Outside Sources:
     * https://www.youtube.com/watch?v=dMGRW48Uvxw
     * https://maxembedded.com/2013/09/the-usart-of-the-avr/
     * https://ww1.microchip.com/downloads/en/DeviceDoc/doc8059.pdf

* File receive_usart.c This file contains the code for the receiver microcontroller in the
USART.
  * Outside sources are the same as for the transmit_usart.c
* io.h contains the declarations of the LCD functions as well as other unique functions used
in the lcd_display_temp.c
* transmit_usart.h contains function declarations for the transmit_usart.c
  * Outside sources are the same as for the transmit_usart.c
* receive_usart.h contains function declarations for the receive_usart.c
  * Outside sources are the same as for the transmit_usart.c

## Component Visualization
![ATMEGA 1284](https://dojft4652t1in.cloudfront.net/wp-content/uploads/IC-ATMEGA1284-PU-3.jpg)
![LCD](https://avrgeeks.com/wp-content/uploads/2017/09/Arduino-LCD-Set-Up-and-Programming-Guide-LCD-Pinout.png)
![LM35](https://www.engineersgarage.com/wp-content/uploads/2019/10/lm35-pin-out_orig-1.png)
