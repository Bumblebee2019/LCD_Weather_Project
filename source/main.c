//Name: Daria
/*Sources I used:
	* https://www.electronicwings.com/avr-atmega/lm35-temperature-sensor-interfacing-with-atmega1632	//for LM35 and AVR interfacing and ADC initialization
	* https://www.electronicwings.com/avr-atmega/atmega16-eeprom										//for EEPROM and atmega interfacing
	* https://maxembedded.com/2011/06/lcd-interfacing-with-avr/											//for displaying variables of type 'int' on the LCD screen
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "io.h"
#include <string.h>
#include <avr/eeprom.h>
#include "LCD.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))
          
/*-------------------------------------------------------------------------*/

#define DATA_BUS PORTC		// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTD	// port connected to pins 4 and 6 of LCD disp.
#define RS 6			// pin number of uC connected to pin 4 of LCD disp.
#define E 7			// pin number of uC connected to pin 6 of LCD disp.


void LCD_ClearScreen(void) {
   LCD_WriteCommand(0x01);
}

void LCD_init(void) {

    //wait for 100 ms.
	delay_ms(100);
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x0f);
	LCD_WriteCommand(0x01);
	delay_ms(10);						 
}

void LCD_WriteCommand (unsigned char Command) {
   CLR_BIT(CONTROL_BUS,RS);
   DATA_BUS = Command;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
   SET_BIT(CONTROL_BUS,RS);
   DATA_BUS = Data;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(1);
}

void LCD_DisplayString( unsigned char column, char* string) {
   LCD_ClearScreen();
   unsigned char c = column;
   while(*string) {
      LCD_Cursor(c++);
      LCD_WriteData(*string++);
   }
}

void LCD_Cursor(unsigned char column) {
   if ( column < 17 ) { // 16x1 LCD: column < 9
						// 16x2 LCD: column < 17
      LCD_WriteCommand(0x80 + column - 1);
   } else {
      LCD_WriteCommand(0xB8 + column - 9);	// 16x1 LCD: column - 1
											// 16x2 LCD: column - 9
   }
}

void delay_ms(int miliSec) //for 8 Mhz crystal

{
    int i,j;
    for(i=0;i<miliSec;i++)
    for(j=0;j<775;j++)
  {
   asm("nop");
  }
}
//--------------------------------------------CODE FOR LM35----------------------------------------------//
void ADC_init(){										
	DDRA = 0x00;	        /* Make ADC port as input */
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;           /* Vref: Avcc, ADC channel: 0 */
}

int ADC_read(char data)							
{
	ADMUX = 0x40 | (data & 0x07);   /* set input channel to read */
	ADCSRA |= (1<<ADSC);               /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}
//-------------------------------------------------------------------------------------------------------//
int main(void) {
	DDRC = 0xFF;	PORTC = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;

	LCD_init();
	ADC_init();

	char buffer[15]; 
	int celsius; 
	int counter = 0;
	int current_temp = 0;
	int min_temp = 0;
	int max_temp = 0;

	//First measurement is outside the while(1) because we want to initially set min = max = current
	celsius = (ADC_read(0)*4.88);
    celsius = (celsius/10.00);
	current_temp = celsius;
	min_temp = current_temp;
	max_temp = current_temp;
	
	while(1) {
		celsius = (ADC_read(0)*4.88);
    	celsius = (celsius/10.00);
		current_temp = celsius;
		//If curr_temp > max_temp, then write the new max to EEPROM
		if(current_temp > max_temp) {
			float new_max = (float) current_temp;
			eeprom_write_float ((float*) 0, new_max);
		}
		if(current_temp < min_temp) {
			float new_min = (float) current_temp;
			eeprom_write_float ((float*) 20, new_min);
		}

		if(counter < 3) {
    		sprintf(buffer, "Temperature: %d", celsius);  //%d means type int; %f means type double
  	 		LCD_DisplayString(1, buffer);
 			delay_ms(1000);
			memset(buffer,0,15);
			LCD_DisplayString(1, buffer);
		}
		else if (counter < 7) {
			if (celsius < 21) {
				 sprintf(buffer, "Icon: %c", '*');  //%c means single character
     	         LCD_DisplayString(1, buffer);
            	 delay_ms(1000);
            	 memset(buffer,0,15);
            	 LCD_DisplayString(1, buffer);
			}
			else if (celsius > 21) {
				 sprintf(buffer, "Icon: %c", '+');  //%c means single character
            	 LCD_DisplayString(1, buffer);
            	 delay_ms(1000);
            	 memset(buffer,0,15);
            	 LCD_DisplayString(1, buffer);
			}
	
		}
		++counter;
		if (counter>7) {
			counter = 0;
		}
		
	}
}

































