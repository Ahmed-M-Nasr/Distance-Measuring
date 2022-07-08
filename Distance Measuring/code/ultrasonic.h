 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the AVR ultrasonic driver
 *
 * Author: Ahmed Nasr
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Initialize the ultrasonic driver as required.*/
void Ultrasonic_init(void);
/*trigger function to send the trigger signal as in the ultrasonic datasheet*/
void Ultrasonic_Trigger(void);
/*send the trigger signal then calculate the distance
 * using the stored high value time according the calculation in the data sheet then return the distance*/
uint16 Ultrasonic_readDistance(void);
/*Ultrasonic edge processing function to detect the falling & rising edges using icu driver*/
void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_H_ */
