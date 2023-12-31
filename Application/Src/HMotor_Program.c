/*
 * HMotorDriver_Program.c
 *
 *  Created on: Oct 10, 2023
 *      Author: lenovo
 */

#include "../include/LIB/STD_Types.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/GPIO/MGPIO_Interface.h"
#include "../include/MCAL/TIMER/MTIMER_Interface.h"
#include "../include/HAL/MOTOR/HMotor_Interface.h"
#include "../include/HAL/MOTOR/HMotor_Config.h"




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
void HMotor_VoidCarForword(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);

}

void HMotor_VoidCarBackword(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_RESET);
    MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_SET);

}

void HMotor_VoidCarRight(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);
}

void HMotor_VoidCarLeft(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_SET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);
}


void HMotor_VoidCarStop(void)
{
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN1,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN2,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN3,GPIO_RESET);
	MGPIO_voidSetPinValue(MOTORDRIVER_PORT,MOTORDRIVER_IN4,GPIO_RESET);
}


void HMotor_VoidCarSpeed(u16 Copy_u16DutyCycle)
{
//	MTIMER_VoidUpdateDuty(TIMER_PWM1,Copy_u16DutyCycle);
//	MTIMER_VoidUpdateDuty(TIMER_PWM2,Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL1, Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL2, Copy_u16DutyCycle);

}

void HMotor_VoidCarSpeedRight(u16 Copy_u16DutyCycle)
{
//	MTIMER_VoidUpdateDuty(TIMER_PWM1,Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL1, Copy_u16DutyCycle);


}

void HMotor_VoidCarSpeedLeft(u16 Copy_u16DutyCycle)
{
//	MTIMER_VoidUpdateDuty(TIMER_PWM2,Copy_u16DutyCycle);
	MTIMER_voidSetCCRValue(TIMER_PWM, CHANNEL2, Copy_u16DutyCycle);


}
