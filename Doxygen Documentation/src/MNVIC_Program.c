/**
 * @file	MNVIC_Program.c
 * @author 	Hesham Yasser
 * @version 2.0
 * @date 	4 Oct 2023
 * @brief 	the NVIC program src file that contains all defenations of *NVIC* driver
 */
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/MCAL/NVIC/MNVIC_Interface.h"
#include "../include/MCAL/NVIC/MNVIC_Private.h"
#include "../include/MCAL/NVIC/MNVIC_Config.h"

static MNVIC_Group_t sglobal_MNVIC_Group_t_Mode ;		//<! this variable saves the configuration of groups and sub groups


/**
 * @fn void MNVIC_voidEnablePeripheralInterrupt(u8)
 * @brief this function is responsible for enabling certain peripheral interrupt
 * @param A_u8Peripheral this is the peripheral number to be enabled
 * @return none
 */
void MNVIC_voidEnablePeripheralInterrupt(u8 A_u8Peripheral)
{
	/*Set the corresponding bit to enable peripheral interrupt*/
	SET_BIT(NVIC->ISER[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));
}
/**
 * @fn void MNVIC_voidDisablePeripheralInterrupt(u8)
 * @brief this function is responsible for disabling certain peripheral interrupt
 * @param A_u8Peripheral this is the peripheral number to be disabled
 * @return none
 */
void MNVIC_voidDisablePeripheralInterrupt(u8 A_u8Peripheral)
{
	/*Set the corresponding bit to Disable peripheral interrupt*/
	SET_BIT(NVIC->ICER[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));

}
/**
 * @fn void MNVIC_voidSetPeripheralInterruptPending(u8)
 * @brief this function is responsible for setting the pending flag of any interrupt source
 * @param A_u8Peripheral this is the peripheral interrput number to be setted
 * @return none
 */
void MNVIC_voidSetPeripheralInterruptPending(u8 A_u8Peripheral)
{
	/*Set the corresponding bit to set peripheral pending flag*/
	SET_BIT(NVIC->ISPR[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));

}

/**
 * @fn void MNVIC_voidClearPeripheralInterruptPending(u8)
 * @brief this function is responsible for clearing the pending flag of any interrupt source
 * @param A_u8Peripheral this is the peripheral interrput number to be cleared
 * @return none
 */
void MNVIC_voidClearPeripheralInterruptPending(u8 A_u8Peripheral)
{
	/*Set the corresponding bit to clear peripheral pending falg*/
	SET_BIT(NVIC->ICPR[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));

}

/**
 * @fn void MNVIC_voidGetInterruptState(u8, u8*)
 * @brief this function is responsible for checking the interrupt state of any interrupt source
 * @param A_u8Peripheral this is the interrupt source to be checked
 * @param p_Read this is a pointer to variable to store the state in
 */
void MNVIC_voidGetInterruptState(u8 A_u8Peripheral , u8 * p_Read)
{
	/*Get the state of peripheral interrput*/
	*p_Read = GET_BIT(NVIC->IABR[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));
}

/**
 * @fn void MNVIC_voidSetInterruptGroupMode(MNVIC_Group_t)
 * @brief this function is responsible for setting the group mode of *NVIC*
 * @param A_MNVIC_Group_t_Mode this is the group configurations selected
 * @return none
 */
void MNVIC_voidSetInterruptGroupMode (MNVIC_Group_t  A_MNVIC_Group_t_Mode)
{
	/*Save the group mode in a static global variable*/
	sglobal_MNVIC_Group_t_Mode = A_MNVIC_Group_t_Mode;
	SCB_AIRCR = (SCB_AIRCR_VECT_KEY | A_MNVIC_Group_t_Mode<<AICIR_PRIGROUP_b0);
}

/**
 * @fn void MNVIC_voidSetInterruptPriority(u8, u8, u8)
 * @brief this function is responsible for setting the priority of any interrupt source
 * @param A_u8Peripheral this is the peripheral to be configured
 * @param A_u8GroupNumber this is the selected group for the selected interrupt source
 * @param A_u8SubNumber this is the selected sub-group for the selected interrupt source
 * @return none
 */
void MNVIC_voidSetInterruptPriority (u8 A_u8Peripheral , u8 A_u8GroupNumber , u8 A_u8SubNumber)
{
	/*Switch on the entered mode*/
	switch (sglobal_MNVIC_Group_t_Mode)
	{
	case Groups16_NoSub :
		/*Set group and sub priority based on the mode*/
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<4);
		break;
	case Groups8_Sub2 :
		/*Set group and sub priority based on the mode*/
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<5|A_u8SubNumber<<4);
		break;
	case Groups4_Sub4 :
		/*Set group and sub priority based on the mode*/
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<6|A_u8SubNumber<<4);
		break;
	case Groups2_Sub8 :
		/*Set group and sub priority based on the mode*/
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<7|A_u8SubNumber<<4);
		break;
	case NoGroup_Sub16 :
		/*Set group and sub priority based on the mode*/
		NVIC->IPR[A_u8Peripheral] = (A_u8SubNumber<<4);
		break;
	}
}
