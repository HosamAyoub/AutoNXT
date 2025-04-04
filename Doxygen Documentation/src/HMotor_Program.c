/**
 * @file	HMOTOR_Program.c
 * @author 	Seif Eldeen Ashraf
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The MOTOR Interface C file that has the functions body which is responsible for Controlling the motor
 */

#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/GPIO/MGPIO_Interface.h"
#include "../include/MCAL/TIMER/MTIMER_Interface.h"
#include "../include/HAL/MOTOR/HMotor_Interface.h"
#include "../include/HAL/MOTOR/HMotor_Config.h"

/**
 * @fn 		void HMotor_VoidCarInit(void)
 * @brief   This function is responsible of Initializing the motor
 * @param 	none
 * @return 	none
 * @details This function initialize the motor:
 * -# Switching the pins which controls the motor to Output mode
 * -#Initializing the Timer's Channels with PWM
 */
void HMotor_VoidCarInit(void)
{
	/* define Motor driver pins as GPIO_OUTPUT */
	MGPIO_voidSetPinMode(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_OUTPUT);
	MGPIO_voidSetPinMode(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_OUTPUT);
	MGPIO_voidSetPinMode(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_OUTPUT);
	MGPIO_voidSetPinMode(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_OUTPUT);

	/* Define Pins GPIO_OUTPUT mode */
	MGPIO_voidSetPinOutputMode(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_PUSH_PULL,GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputMode(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_PUSH_PULL,GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputMode(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_PUSH_PULL,GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputMode(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MTIMER_voidSetPWMOption(TIMER_PWM, CHANNEL1, PRELOAD_VALUE, NO_DUTYCYCLE, 15);
	MTIMER_voidSetPWMOption(TIMER_PWM, CHANNEL2, PRELOAD_VALUE, NO_DUTYCYCLE, 15);
//	MTimer_voidPWMConfig(TIMER_PWM1,PRELOAD_VALUE,NO_DUTYCYCLE);
//	MTimer_voidPWMConfig(TIMER_PWM2,PRELOAD_VALUE,NO_DUTYCYCLE);


}

/**
 * @fn 		void HMotor_VoidCarForword(void)
 * @brief   This function is responsible of Moving The Motor Forward
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarForword(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);

}

/**
 * @fn 		void HMotor_VoidCarBackword(void)
 * @brief   This function is responsible of Moving The Motor Backward
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarBackword(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_RESET);
    MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_SET);

}


/**
 * @fn 		void HMotor_VoidCarRight(void)
 * @brief   This function is responsible of Moving The Motor Right
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarRight(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);
}

/**
 * @fn 		void HMotor_VoidCarLeft(void)
 * @brief   This function is responsible of Moving The Motor Left
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarLeft(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);
}

/**
 * @fn 		void HMotor_VoidCarStop(void)
 * @brief   This function is responsible of Stopping the motor
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarStop(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);
}

/**
 * @fn 		void HMotor_VoidCarSpeed(u16)
 * @brief   This function is responsible of Controlling the Speed of motor
 * @param 	Copy_u16DutyCycle Copy of the Value which assigned to the Register that Register is responsible of duty cycle
 * @return 	none
 */
void HMotor_VoidCarSpeed(u16 Copy_u16DutyCycle)
{
//	MTIMER_VoidUpdateDuty(TIMER_PWM1,Copy_u16DutyCycle);
//	MTIMER_VoidUpdateDuty(TIMER_PWM2,Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL1, Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL2, Copy_u16DutyCycle);

}
/**
 * @fn 		void HMotor_VoidCarSpeedRight(u16)
 * @brief   This function is responsible of Controlling the speed of the right motors
 * @param 	Copy_u16DutyCycle Copy of the Value which assigned to the Register that Register is responsible of duty cycle of the Right motors
 * @return 	none
 */
void HMotor_VoidCarSpeedRight(u16 Copy_u16DutyCycle)
{
//	MTIMER_VoidUpdateDuty(TIMER_PWM1,Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL1, Copy_u16DutyCycle);


}

/**
 * @fn 		void HMotor_VoidCarSpeedLeft(u16)
 * @brief   This function is responsible of Controlling the speed of the Left motors
 * @param 	Copy_u16DutyCycle Copy of the Value which assigned to the Register that Register is responsible of duty cycle of the Left motors
 * @return 	none
 */
void HMotor_VoidCarSpeedLeft(u16 Copy_u16DutyCycle)
{
//	MTIMER_VoidUpdateDuty(TIMER_PWM2,Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL2, Copy_u16DutyCycle);


}
