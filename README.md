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

