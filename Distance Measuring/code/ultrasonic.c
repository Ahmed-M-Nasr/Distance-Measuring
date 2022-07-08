 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the AVR ultrasonic driver
 *
 * Author: Ahmed Nasr
 *
 *******************************************************************************/
#include "common_macros.h"
#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static uint16 time = 0;
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*Initialize the ultrasonic driver as required.*/
void Ultrasonic_init(void){
	/*Initialize the ICU driver as required.*/
	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
	Icu_init(&Icu_Config);
	/*Setup the ICU call back function using the ultrasonic edge processing function */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/*Setup the direction for the trigger pin as output pin through the GPIO driver.*/
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID, PIN_OUTPUT);
	/*initialize the pin with 0 as output*/
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}
/*trigger function to send the trigger signal as in the ultrasonic datasheet*/
void Ultrasonic_Trigger(void){
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}
/*Ultrasonic edge processing function to detect the falling & rising edges using icu driver*/
void Ultrasonic_edgeProcessing(void){

	static uint8 g_edgeCount = 0;

	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */

		Icu_clearTimerValue();

		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{

		/* Store the High time value */
		time = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);


		g_edgeCount=0;
	}
}
/*send the trigger signal then calculate the distance
 * using the stored high value time according the calculation in the data sheet then return the distance*/
uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	return((time*0.017)+2);
}
