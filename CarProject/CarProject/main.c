/*
 * CARPROJECT.c
 *
 * Created: 2/17/2020 10:14:40 AM
 * Author : Mohamed Ramadan
 */ 
/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "Timer.h"
#include "DIO.h"
#include "util/delay.h"
#include "PWM.h"
#include "motor.h"
#include "ICU.h"
#include "Us.h"
#include "car_sm.h"
#include "Steering.h"


int main(void)
{
	
/*********************************** Car Application ***********************************/
//Initialize the Car state machine with speed 30%
Car_SM_Init();

//Super main loop
while(1)
{
	/****Trigger ultrasonic module and change the car 
	state according to ultrasonic distance****/
	
	Car_SM_Update();
	
}

	return 0;
}

