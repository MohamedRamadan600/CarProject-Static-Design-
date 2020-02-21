/*
 * File		: car_sm.h
 * Created	: 19/2/2020 7:30:37 AM
 * Author	: Mohamed Ramadan
 */

/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/

#include "Us.h"
#include "car_sm.h"
#include "util/delay.h"

#define  FreeWay          0
#define  TakeLeft         1
#define  AvoidAccident    2

#define Dangeredge       20
#define Safeedge         35
#define ZeroInitial      0

#define InitialSpeed		  35
#define freewayspeed		  40
#define VoidAccidentspeed     40
#define TakeLeftspeed         40


/*************************************************************/
/*                     FUNCTIONS Implementation              */
/*************************************************************/

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 30%",
 * -------------- And initiate steering and ultrasonic functions
*/
uint8_t Car_SM_Init(void){
	
	uint8_t Err_Status = ZeroInitial;
	/*Assign No Error for the Err_Status variable*/
	Err_Status = E_OK;
	
	/*Ultrasonic Initialization*/
	Us_Init();
	/*Initialize the module PWM and Motor*/
	Steering_Init();
	/*Control the car to move forward with speed 30%*/
	Steering_SteerCar(CAR_FORWARD,InitialSpeed);
	
	return Err_Status;
}

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/
uint8_t Car_SM_Update(void){
	 /***Variable storing the geeting distance by ultrasonic***/
	 uint16_t Car_Distance = ZeroInitial;
	 /***Variable storing the state of the car if it find obstacle or not***/
	 uint16_t Car_state =ZeroInitial;
	 /***Pointer to pass it with function "Get_Distance" to get the distance ***/
	 uint16_t *Get_Distance = NULL;
	 /***variable of Error status of the function ***/
	 uint8_t Err_Status = ZeroInitial;
	 /***Error status is not exist***/
	 Err_Status = E_OK;
	  
	 /***Trigger the Ultrasonic module by dending Trigger signal***/ 
	 Us_Trigger();
	 /***getting the distance measured by ultrasonic***/
	 Us_GetDistance(Get_Distance);
	
	/***storing get distance value at the car_Distance ***/
	Car_Distance = *Get_Distance;
	
	/*** Check boundary cases of car movement and Action used ***/
	if (Car_Distance>=Dangeredge && Car_Distance<=Safeedge)
	{
		/***Rotate the car left***/
		Car_state =TakeLeft;
	} 
	/***Distance less than 25 cm***/
	else if(Car_Distance<Dangeredge)
	{
		/***Step Backward to avoid obstacle then move forward again***/
		Car_state =AvoidAccident;
	/***Distance more than 25 cm***/
	}else if(Car_Distance>Safeedge)
	{
		/***Go away the road is safe***/
		Car_state =FreeWay;
	}
	
	switch (Car_state)
	{
	case FreeWay:
		/***Move Car to forward the way is safe***/
		Steering_SteerCar(CAR_FORWARD,freewayspeed);
		_delay_ms(10);
		break;
	case AvoidAccident:
		/***Move Car to Backward to avoid an accident***/
		Steering_SteerCar(CAR_BACKWARD,VoidAccidentspeed);
		_delay_ms(35);
		/***Move Car to forward again and detect again the distance***/
		Steering_SteerCar(CAR_FORWARD,VoidAccidentspeed);
		_delay_ms(10);
		break;
	case TakeLeft:
		/***Rotate the car to the left Direction***/
		Steering_SteerCar(CAR_LEFT,TakeLeftspeed);
		_delay_ms(5);
		break;
	}

	return Err_Status;
}