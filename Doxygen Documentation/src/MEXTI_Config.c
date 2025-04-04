/**
 * @file	MEXTI_Config.c
 * @author 	Hesham Yasser
 * @version 2.0
 * @date 	10 Oct 2023
 * @brief 	EXTI Configurations source file that contains some configuration of EXTI driver
 */


#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/MCAL/EXTI/MEXTI_Interface.h"
#include "../include/MCAL/EXTI/MEXTI_private.h"
#include "../include/MCAL/EXTI/MEXTI_Config.h"


/*
 * MEXTI_Configuartions {
	 * Line
	 * Port
	 * Mode
	 * Initial Value
 * }
 */


MEXTI_Configuartions MEXTI_Config [MEXTI_NUMBER] =			//<! this is the struct containing EXTI configuratuion
{
		{
				MEXTI_LINE0,
				MEXTI_PORTB,
				MEXTI_FALLING_EDGE,
				MEXTI_DISABLED
		}
		,
		{
				MEXTI_LINE1,
				MEXTI_PORTB,
				MEXTI_FALLING_EDGE,
				MEXTI_DISABLED
		}

};


