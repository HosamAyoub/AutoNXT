/*
 * MRCC_Program.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Hesham Yasser
 */




#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/RCC/MRCC_private.h"
#include "../include/RCC/MRCC_Configurations.h"


void MRCC_voidInit (void)
{
#if SYS_CLK == RCC_HSI
	// Enable HSI
	SET_BIT(RCC->CR , CR_HSI_ON);
	// Wait till HSI is Ready
	while (GET_BIT(RCC->CR , CR_HSI_RDY) == RCC_NOT_READY);
	// Masking The Switching Bits
	RCC->CFGR &= ~(TWO_BIT_MASK << SW_b0);
	// Select HSI as System Clk Source
	RCC->CFGR |= (SW_HSI << SW_b0);

#elif SYS_CLK == RCC_HSE
	// Enable HSE
	SET_BIT(RCC->CR , CR_HSE_ON);
	// Wait till HSE is Ready
	while (GET_BIT(RCC->CR , CR_HSE_RDY) == RCC_NOT_READY);
	// Masking The Switching Bits
	RCC->CFGR &= ~(TWO_BIT_MASK << SW_b0);
	// Select HSE as System Clk Source
	RCC->CFGR |= (SW_HSE << SW_b0);

#elif SYS_CLK == RCC_PLL
	// Enable PLL
	SET_BIT(RCC->CR , CR_PLL_ON);
	// Wait till PLL is Ready
	while (GET_BIT(RCC->CR , CR_PLL_RDY) == RCC_NOT_READY);
	// Masking The Switching Bits
	RCC->CFGR &= ~(TWO_BIT_MASK << SW_b0);
	// Select PLL as System Clk Source
	RCC->CFGR |= (SW_PLL << SW_b0);

#else
#error WRONG_SYS_CLK
#endif
/*Enable or Disable CSS*/
#if RCC_CLK_SECURITY_SYSTEM == RCC_CSS_OFF
	/*Disable CSS*/
	CLR_BIT (RCC->CR , CR_CSSON);
#else
	/*Enable CSS*/
	SET_BIT (RCC->CR , CR_CSSON);
#endif
}
void MRCC_voidEnablePeripheral(u32 A_u32BusAddress , u32 A_u32Peripheral)
{
	/*Some Input Validation*/
	if (A_u32BusAddress < RCC_NUMBER_OF_BUSES && A_u32Peripheral < BITS_PER_REGISTER)
	{
		/*Switch on The Bus*/
		switch (A_u32BusAddress)
		{
		case RCC_APB1:
			/*Set Corresponding Bit to Enable That Peripheral in APB1 Bus*/
			SET_BIT(RCC->APB1ENR,A_u32Peripheral);
			break;
		case RCC_APB2:
			/*Set Corresponding Bit to Enable That Peripheral in APB2 Bus*/
			SET_BIT(RCC->APB2ENR,A_u32Peripheral);
			break;
		case RCC_AHB1:
			/*Set Corresponding Bit to Enable That Peripheral in AHB1 Bus*/
			SET_BIT(RCC->AHB1ENR,A_u32Peripheral);
			break;
		case RCC_AHB2:
			/*Set Corresponding Bit to Enable That Peripheral in AHB2 Bus*/
			SET_BIT(RCC->AHB2ENR,A_u32Peripheral);
			break;
		default:
			break;
		}
	}
}
void MRCC_voidDisablePeripheral(u32 A_u32BusAddress , u32 A_u32Peripheral)
{
	/*Some Input Validation*/
	if (A_u32BusAddress < RCC_NUMBER_OF_BUSES && A_u32Peripheral < BITS_PER_REGISTER)
	{
		/*Switch on The Bus*/
		switch (A_u32BusAddress)
		{
		case RCC_APB1:
			/*Clear Corresponding Bit to Disable That Peripheral in APB1 Bus*/
			CLR_BIT(RCC->APB1ENR,A_u32Peripheral);
			break;
		case RCC_APB2:
			/*Clear Corresponding Bit to Disable That Peripheral in APB2 Bus*/
			CLR_BIT(RCC->APB2ENR,A_u32Peripheral);
			break;
		case RCC_AHB1:
			/*Clear Corresponding Bit to Disable That Peripheral in AHB1 Bus*/
			CLR_BIT(RCC->AHB1ENR,A_u32Peripheral);
			break;
		case RCC_AHB2:
			/*Clear Corresponding Bit to Disable That Peripheral in AHB2 Bus*/
			CLR_BIT(RCC->AHB2ENR,A_u32Peripheral);
			break;
		default:
			break;
		}
	}
}

void MRCC_voidSetAPB1Prescaler (u8 A_u8APB1Prescaler)
{
	/*Some Input Validation*/
	if (A_u8APB1Prescaler <= RCC_APB_PRESCALER_BY_16)
	{
		/*Clear Those bits*/
		RCC->CFGR &= ~(THREE_BIT_MASK << CR_PPRE1);
		/*Set Those bits based on the entered prescaler*/
		RCC->CFGR |= (A_u8APB1Prescaler << CR_PPRE1);
	}
}
void MRCC_voidSetAPB2Prescaler (u8 A_u8APB2Prescaler)
{
	/*Some Input Validation*/
	if (A_u8APB2Prescaler <= RCC_APB_PRESCALER_BY_16)
	{
		/*Clear Those bits*/
		RCC->CFGR &= ~(THREE_BIT_MASK << CR_PPRE2);
		/*Set Those bits based on the entered prescaler*/
		RCC->CFGR |= (A_u8APB2Prescaler << CR_PPRE2);
	}
}
void MRCC_voidSetAHBPrescaler (u8 A_u8AHBPrescaler)
{
	/*Some Input Validation*/
	if (A_u8AHBPrescaler <= RCC_AHB_PRESCALER_BY_512)
	{
		/*Clear Those bits*/
		RCC->CFGR &= ~(FOUR_BIT_MASK << CR_HPRE);
		/*Set Those bits based on the entered prescaler*/
		RCC->CFGR |= (A_u8AHBPrescaler << CR_HPRE);
	}
}
