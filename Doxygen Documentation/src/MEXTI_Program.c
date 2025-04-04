/**
 * @file	MEXTI_Program.c
 * @author 	Hesham Yasser
 * @version 2.0
 * @date 	10 Oct 2023
 * @brief 	EXTI program source file that contains the functions of external interrupts
 */

#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/MCAL/EXTI/MEXTI_Interface.h"
#include "../include/MCAL/EXTI/MEXTI_Private.h"
#include "../include/MCAL/EXTI/MEXTI_Config.h"


extern MEXTI_Configuartions MEXTI_Config[MEXTI_NUMBER];				//<! this is the struct containing EXTI configuratuion

static PtrToFunc_void MEXTI_CallBack[MEXTI_TOTAL_NUMBER];			//<! this is the array of Pointers to function used to store Callback for each EXTI line
/**
 * @fn void MEXTI_voidInit(void)
 * @brief this function is responsible of initilization of *EXTI* Line
 * @param none
 * @return none
 */
void MEXTI_voidInit (void)
{
	/*initialize an iterator to iterate on the EXTIs in configuration source file*/
	u8 local_u8Iterator = 0;
	for (local_u8Iterator = 0 ; local_u8Iterator < MEXTI_NUMBER ; local_u8Iterator++)
	{
		/*Set the EXTI port*/
		SYSCFG->EXTICR[((MEXTI_Config[local_u8Iterator].Line)/4)] &= ~(FOUR_BIT_MASK << (((MEXTI_Config[local_u8Iterator].Line)%4)*4));
		SYSCFG->EXTICR[((MEXTI_Config[local_u8Iterator].Line)/4)] |=  (MEXTI_Config[local_u8Iterator].Port << (((MEXTI_Config[local_u8Iterator].Line)%4)*4));
		/*Set the EXTI mode*/
		if (MEXTI_Config[local_u8Iterator].Mode == MEXTI_FALLING_EDGE)
		{
			SET_BIT(EXTI->FTSR , MEXTI_Config[local_u8Iterator].Line);
		}
		else if (MEXTI_Config[local_u8Iterator].Mode == MEXTI_RISING_EDGE)
		{
			SET_BIT(EXTI->RTSR , MEXTI_Config[local_u8Iterator].Line);
		}
		else
		{
			SET_BIT(EXTI->FTSR , MEXTI_Config[local_u8Iterator].Line);
			SET_BIT(EXTI->RTSR , MEXTI_Config[local_u8Iterator].Line);
		}
		/*Set state of EXTI based on the given Intial Value*/
		if (MEXTI_Config[local_u8Iterator].InitialValue == MEXTI_ENABLED)
		{
			SET_BIT(EXTI->IMR , MEXTI_Config[local_u8Iterator].Line);
		}
		else
		{
			CLR_BIT(EXTI->IMR , MEXTI_Config[local_u8Iterator].Line);
		}
	}

}
/**
 * @fn void MEXTI_voidEnableEXTILine(MEXTI_Line)
 * @brief this function is responsible of Enabling a specific *EXTI* Line
 * @param A_MEXTI_Line this is the EXTI line number to be enabled
 * @return none
 */
void MEXTI_voidEnableEXTILine (MEXTI_Line A_MEXTI_Line)
{
	/*Set the corresponding bit to enable the entered EXTI*/
	SET_BIT(EXTI->IMR , A_MEXTI_Line);
}

/**
 * @fn void MEXTI_voidDisableEXTILine(MEXTI_Line)
 * @brief this function is responsible of Disabling a specific *EXTI* Line
 * @param A_MEXTI_Line this is the EXTI line number to be disabled
 * @return none
 */
void MEXTI_voidDisableEXTILine (MEXTI_Line A_MEXTI_Line)
{
	/*Clear the corresponding bit to disable the entered EXTI*/
	CLR_BIT(EXTI->IMR , A_MEXTI_Line);
}

/**
 * @fn void MEXTI_voidSetCallBack(MEXTI_Line, PtrToFunc_void)
 * @brief this function is responsible for setting the callback function of a *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number that
 * @param A_CallBackFunc this is the function to be executed when the interrupt occurs
 * @return none
 */
void MEXTI_voidSetCallBack (MEXTI_Line A_MEXTI_Line , PtrToFunc_void A_CallBackFunc)
{
	/*Set the entered function to the entered EXTI Callback function pointer*/
	MEXTI_CallBack[A_MEXTI_Line] = A_CallBackFunc;
}

/**
 * @fn void MEXTI_voidSoftwareInterrputRequest(MEXTI_Line)
 * @brief this function is responsible for simulating a sofware interrupt of a specific *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to simulate
 * @return none
 */
void MEXTI_voidSoftwareInterrputRequest (MEXTI_Line A_MEXTI_Line)
{
	/*Set the corresponding bit to trigger an interrupt request*/
	SET_BIT(EXTI->SWIER , A_MEXTI_Line);
}

/**
 * @fn void MEXTI_voidClearPendingFlag(MEXTI_Line)
 * @brief this function is responsible for clearing pending flag of a specific *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to be cleared
 * @return none
 */
void MEXTI_voidClearPendingFlag (MEXTI_Line A_MEXTI_Line)
{
	/*Set the corresponding bit to clear the pending flag*/
	SET_BIT(EXTI->PR , A_MEXTI_Line);
}

/**
 * @fn void MEXTI_voidSelectPort(MEXTI_Line, MEXTI_Port)
 * @brief this function is responsible for setting the port for an *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to be configured
 * @param A_MEXTI_Port this is the selected port
 * @return none
 */
void MEXTI_voidSelectPort (MEXTI_Line A_MEXTI_Line , MEXTI_Port A_MEXTI_Port)
{
	/*Set those bits based on the entered port and EXTI*/
	SYSCFG->EXTICR[(A_MEXTI_Line/4)] &= ~(FOUR_BIT_MASK << ((A_MEXTI_Line%4)*4));
	SYSCFG->EXTICR[(A_MEXTI_Line/4)] |=  (A_MEXTI_Port << ((A_MEXTI_Line%4)*4));
}

/**
 * @fn void MEXTI_voidSetMode(MEXTI_Line, MEXTI_Mode)
 * @brief this function is responsible for setting the edge for a specific *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to be configured
 * @param A_MEXTI_Mode this is the selected edge for the EXTI
 * @return none
 */
void MEXTI_voidSetMode (MEXTI_Line A_MEXTI_Line , MEXTI_Mode A_MEXTI_Mode)
{
	/*Set those bits based on the entered mode and EXTI*/
	if (A_MEXTI_Mode == MEXTI_FALLING_EDGE)
	{
		SET_BIT(EXTI->FTSR , A_MEXTI_Line);
	}
	else if (A_MEXTI_Mode == MEXTI_RISING_EDGE)
	{
		SET_BIT(EXTI->RTSR , A_MEXTI_Line);
	}
	else
	{
		SET_BIT(EXTI->FTSR , A_MEXTI_Line);
		SET_BIT(EXTI->RTSR , A_MEXTI_Line);
	}
}

/**
 * @fn void EXTI0_IRQHandler(void)
 * @brief this is the ISR for the EXTI line 0
 * @return none
 */
void EXTI0_IRQHandler (void)
{
	if (MEXTI_CallBack[MEXTI_LINE0] != NULL)
	{
		MEXTI_CallBack[MEXTI_LINE0]();
	}
	SET_BIT(EXTI->PR , MEXTI_LINE0);
}
/**
 * @fn void EXTI1_IRQHandler(void)
 * @brief this is the ISR for the EXTI line 1
 * @return none
 */
void EXTI1_IRQHandler (void)
{
	if (MEXTI_CallBack[MEXTI_LINE1] != NULL)
	{
		MEXTI_CallBack[MEXTI_LINE1]();
	}
	SET_BIT(EXTI->PR , MEXTI_LINE1);
}
/**
 * @fn void EXTI2_IRQHandler(void)
 * @brief this is the ISR for the EXTI line 2
 * @return none
 */
void EXTI2_IRQHandler (void)
{
	if (MEXTI_CallBack[MEXTI_LINE2] != NULL)
	{
		MEXTI_CallBack[MEXTI_LINE2]();
	}
	SET_BIT(EXTI->PR , MEXTI_LINE2);
}
/**
 * @fn void EXTI3_IRQHandler(void)
 * @brief this is the ISR for the EXTI line 3
 * @return none
 */
void EXTI3_IRQHandler (void)
{
	if (MEXTI_CallBack[MEXTI_LINE3] != NULL)
	{
		MEXTI_CallBack[MEXTI_LINE3]();
	}
	SET_BIT(EXTI->PR , MEXTI_LINE3);
}
/**
 * @fn void EXTI4_IRQHandler(void)
 * @brief this is the ISR for the EXTI line 4
 * @return none
 */
void EXTI4_IRQHandler (void)
{
	if (MEXTI_CallBack[MEXTI_LINE4] != NULL)
	{
		MEXTI_CallBack[MEXTI_LINE4]();
	}
	SET_BIT(EXTI->PR , MEXTI_LINE4);
}
/**
 * @fn void EXTI9_5_IRQHandler(void)
 * @brief this is the ISR for the EXTI line 5 to line 9
 * @return none
 */
void EXTI9_5_IRQHandler (void)
{
	u8 local_u8Iterator;
	for (local_u8Iterator = 5 ; local_u8Iterator < 10 ; local_u8Iterator++)
	{
		if (GET_BIT(EXTI->PR, local_u8Iterator))
		{
			if (MEXTI_CallBack[local_u8Iterator] != NULL)
			{
				MEXTI_CallBack[local_u8Iterator]();
			}
			else
			{
				/* Do Nothing */
			}
			SET_BIT(EXTI->PR , local_u8Iterator);
		}
	}
}
