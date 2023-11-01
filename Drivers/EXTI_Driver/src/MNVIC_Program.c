/*
 * NVIC_Program.c
 *
 *  Created on: Sep 11, 2023
 *      Author: Hesham Yasser
 */
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/NVIC/MNVIC_Interface.h"
#include "../include/NVIC/MNVIC_private.h"
#include "../include/NVIC/MNVIC_Configurations.h"

// ENABLE SYSCFG IN RCC BEFORE STARTING
static MNVIC_Group_t sglobal_MNVIC_Group_t_Mode ;

void MNVIC_voidEnablePeripheralInterrupt(u8 A_u8Peripheral)
{
	SET_BIT(NVIC->ISER[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));
}
void MNVIC_voidDisablePeripheralInterrupt(u8 A_u8Peripheral)
{
	SET_BIT(NVIC->ICER[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));

}
void MNVIC_voidSetPeripheralInterruptPending(u8 A_u8Peripheral)
{
	SET_BIT(NVIC->ISPR[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));

}
void MNVIC_voidClearPeripheralInterruptPending(u8 A_u8Peripheral)
{
	SET_BIT(NVIC->ICPR[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));

}
void MNVIC_voidGetInterruptState(u8 A_u8Peripheral , u8 * p_Read)
{
	*p_Read = GET_BIT(NVIC->IABR[(A_u8Peripheral/BITS_IN_REGISTER)] , (A_u8Peripheral%BITS_IN_REGISTER));
}
void MNVIC_voidSetInterruptGroupMode (MNVIC_Group_t  A_MNVIC_Group_t_Mode)
{
	sglobal_MNVIC_Group_t_Mode = A_MNVIC_Group_t_Mode;
	SCB_AIRCR = (SCB_AIRCR_VECT_KEY | A_MNVIC_Group_t_Mode<<AICIR_PRIGROUP_b0);
}


void MNVIC_voidSetInterruptPriority (u8 A_u8Peripheral , u8 A_u8GroupNumber , u8 A_u8SubNumber)
{
	switch (sglobal_MNVIC_Group_t_Mode)
	{
	case Groups16_NoSub :
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<4);
		break;
	case Groups8_Sub2 :
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<5|A_u8SubNumber<<4);
		break;
	case Groups4_Sub4 :
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<6|A_u8SubNumber<<4);
		break;
	case Groups2_Sub8 :
		NVIC->IPR[A_u8Peripheral] = (A_u8GroupNumber<<7|A_u8SubNumber<<4);
		break;
	case NoGroup_Sub16 :
		NVIC->IPR[A_u8Peripheral] = (A_u8SubNumber<<4);
		break;
	}
}
