/**
 * @file	MEXTI_Interface.h
 * @author 	Hesham Yasser
 * @version 2.0
 * @date 	10 Oct 2023
 * @brief 	EXTI interface header file that contains the declaration of the functions of external interrupts
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/********************EXTI_LINES**********************/
/**
 * @enum MEXTI_Line
 * @brief this is the enum that contains all *EXTI* line number
 */
typedef enum
{
	MEXTI_LINE0	 = 0,/**< MEXTI_LINE0 */
	MEXTI_LINE1	 ,   /**< MEXTI_LINE1 */
	MEXTI_LINE2	 ,   /**< MEXTI_LINE2 */
	MEXTI_LINE3	 ,   /**< MEXTI_LINE3 */
	MEXTI_LINE4	 ,   /**< MEXTI_LINE4 */
	MEXTI_LINE5	 ,   /**< MEXTI_LINE5 */
	MEXTI_LINE6	 ,   /**< MEXTI_LINE6 */
	MEXTI_LINE7	 ,   /**< MEXTI_LINE7 */
	MEXTI_LINE8	 ,   /**< MEXTI_LINE8 */
	MEXTI_LINE9	 ,   /**< MEXTI_LINE9 */
	MEXTI_LINE10 ,   /**< MEXTI_LINE10 */
	MEXTI_LINE11 ,   /**< MEXTI_LINE11 */
	MEXTI_LINE12 ,   /**< MEXTI_LINE12 */
	MEXTI_LINE13 ,   /**< MEXTI_LINE13 */
	MEXTI_LINE14 ,   /**< MEXTI_LINE14 */
	MEXTI_LINE15     /**< MEXTI_LINE15 */
}MEXTI_Line;



/*********************EXTI_MODES********************/
/**
 * @enum MEXTI_Mode
 * @brief this is the enum that contains all modes of *EXTI*
 */
typedef enum
{
	MEXTI_RISING_EDGE = 0 ,/**< MEXTI_RISING_EDGE */
	MEXTI_FALLING_EDGE	,   /**< MEXTI_FALLING_EDGE */
	MEXTI_ON_CHANGE        /**< MEXTI_ON_CHANGE */
}MEXTI_Mode;


/********************EXTI_State*************/
/**
 * @enum MEXTI_State
 * @brief this is the enum that contains EXTI states
 */
typedef enum
{
	MEXTI_DISABLED = 0,/**< MEXTI_DISABLED */
	MEXTI_ENABLED      /**< MEXTI_ENABLED */
}MEXTI_State;

/********************EXTI_PORTs*****************/
/**
 * @enum MEXTI_Port
 * @brief this is the enum that contains all ports used in *EXTI*
 */
typedef enum
{
	MEXTI_PORTA	= 0,/**< MEXTI_PORTA */
	MEXTI_PORTB	,   /**< MEXTI_PORTB */
	MEXTI_PORTC ,   /**< MEXTI_PORTC */
	MEXTI_PORTD ,   /**< MEXTI_PORTD */
	MEXTI_PORTE ,   /**< MEXTI_PORTE */
	MEXTI_PORTH = 7 /**< MEXTI_PORTH */
}MEXTI_Port;


/***********************APIs************************/
/**
 * @fn void MEXTI_voidInit(void)
 * @brief this function is responsible of initilization of *EXTI* Line
 * @param none
 * @return none
 */
void MEXTI_voidInit (void);

/**
 * @fn void MEXTI_voidEnableEXTILine(MEXTI_Line)
 * @brief this function is responsible of Enabling a specific *EXTI* Line
 * @param A_MEXTI_Line this is the EXTI line number to be enabled
 * @return none
 */
void MEXTI_voidEnableEXTILine (MEXTI_Line A_MEXTI_Line);

/**
 * @fn void MEXTI_voidDisableEXTILine(MEXTI_Line)
 * @brief this function is responsible of Disabling a specific *EXTI* Line
 * @param A_MEXTI_Line this is the EXTI line number to be disabled
 * @return none
 */
void MEXTI_voidDisableEXTILine (MEXTI_Line A_MEXTI_Line);

/**
 * @fn void MEXTI_voidSetCallBack(MEXTI_Line, PtrToFunc_void)
 * @brief this function is responsible for setting the callback function of a *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number that
 * @param A_CallBackFunc this is the function to be executed when the interrupt occurs
 * @return none
 */
void MEXTI_voidSetCallBack (MEXTI_Line A_MEXTI_Line , PtrToFunc_void A_CallBackFunc);

/**
 * @fn void MEXTI_voidSoftwareInterrputRequest(MEXTI_Line)
 * @brief this function is responsible for simulating a sofware interrupt of a specific *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to simulate
 * @return none
 */
void MEXTI_voidSoftwareInterrputRequest (MEXTI_Line A_MEXTI_Line);

/**
 * @fn void MEXTI_voidClearPendingFlag(MEXTI_Line)
 * @brief this function is responsible for clearing pending flag of a specific *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to be cleared
 * @return none
 */
void MEXTI_voidClearPendingFlag (MEXTI_Line A_MEXTI_Line);

/**
 * @fn void MEXTI_voidSelectPort(MEXTI_Line, MEXTI_Port)
 * @brief this function is responsible for setting the port for an *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to be configured
 * @param A_MEXTI_Port this is the selected port
 * @return none
 */
void MEXTI_voidSelectPort (MEXTI_Line A_MEXTI_Line , MEXTI_Port A_MEXTI_Port);

/**
 * @fn void MEXTI_voidSetMode(MEXTI_Line, MEXTI_Mode)
 * @brief this function is responsible for setting the edge for a specific *EXTI* line
 * @param A_MEXTI_Line this is the EXTI line number to be configured
 * @param A_MEXTI_Mode this is the selected edge for the EXTI
 * @return none
 */
void MEXTI_voidSetMode (MEXTI_Line A_MEXTI_Line , MEXTI_Mode A_MEXTI_Mode);


#endif /* EXTI_INTERFACE_H_ */
