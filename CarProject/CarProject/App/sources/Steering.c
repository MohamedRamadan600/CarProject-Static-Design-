#include "Steering.h"

//ICU structures
Icu_cfg_s Icu_cfg_INT2;


/************************************************************************/
/*		      STEERING FUNCTIONS' Implementation		        */
/************************************************************************/


/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

uint8_t Steering_Init(void){
	uint8_t Err_Status = 0;
	Err_Status =E_OK;
	
	//Initialize Motor
	Motor_Init(MOTOR_1);
	Motor_Init(MOTOR_2);
	
	Motor_Start(MOTOR_1,0);
	Motor_Start(MOTOR_2,0);
	return Err_Status;
}


/**
 * Input: 
 * 	car Direction: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function controls the command and the speed of the car.
 * 							
 */
uint8_t Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed){
	uint8_t Err_Status = 0;
	Err_Status = E_OK;
	
	switch (Steering_CarCmd)
	{
	case CAR_STOP:
		Motor_Stop(MOTOR_1);
		Motor_Stop(MOTOR_2);
		break;
	case CAR_FORWARD:
		Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		Motor_Direction(MOTOR_2,MOTOR_FORWARD);
		Motor_SpeedUpdate(MOTOR_1_2,speed);
		break;
	case CAR_BACKWARD:
		Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
	    Motor_SpeedUpdate(MOTOR_1_2,speed);
		break;
		
	case CAR_RIGHT:
		Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		Motor_SpeedUpdate(MOTOR_2,speed);
		break;
	case CAR_LEFT:
		Motor_Direction(MOTOR_1,MOTOR_FORWARD);
		Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
		Motor_SpeedUpdate(MOTOR_2,speed);
		break;
	default:
		Err_Status = E_NOK;			
	}
	
	
	return Err_Status;
}