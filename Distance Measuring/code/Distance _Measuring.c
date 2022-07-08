 /******************************************************************************
 *
 * Module: Application
 *
 * File Name: Mini_Project4.c
 *
 * Description: Source file for the Application
 *
 * Author: Ahmed Nasr
 *
 *******************************************************************************/
#include "lcd.h"
#include "icu.h"
#include <avr/io.h> /* To use the SREG register */
#include<util/delay.h>
int main(void){
	/*Value initalized by 0 to store the distance read*/
	uint32 distance = 0;
	/*Global interrupt Enable*/
	SREG |= (1<<7);
	/*Initialize Ultrasonic driver & ICU driver*/
	Ultrasonic_init();
	/*Initialize LCD driver*/
	LCD_init();
	/*Display "Distance=    cm" once the value is space changes according to the distance reading*/
	LCD_displayString("Distance=    cm");
	while(1){
		/*read and calculate the distance using the ultrasonic driver and save it in a varible*/
		distance= Ultrasonic_readDistance();
		/*Move the lcd cursor just after the '=' sign */
		LCD_moveCursor(0,10);
		/*Display the value stored in the distance variable on the lcd*/
		LCD_intgerToString(distance);
		/*check if the distance is less than 100 insert a space after the value to make sure
		 * no old value displayed in the unused space*/
		if(distance<100)
				LCD_displayCharacter(' ');
	}
}
