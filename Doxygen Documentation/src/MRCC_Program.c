/**
 * @file MRCC_Program.c
 * @author Seif Eldeen Ashraf
 * @version 2.0
 * @date 18 Sep 2023
 * @brief The Reset Clock Control C file that has the functions body which is responsible for peripherals clock
 */
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/RCC/MRCC_Interface.h"
#include "../include/MCAL/RCC/MRCC_Private.h"
#include "../include/MCAL/RCC/MRCC_Config.h"


/**
 * @fn 		void MRCC_voidInit (void)
 * @brief   This function is responsible of Initializing Reset Clock Control
 * @param 	none
 * @return 	none
 * @details This function initialize the system clock:
 * -# Check that the system clock is External or PLL or Internal then wait for the Ready flag then switch to to chosen Clock
 * -# if The chosen Clock is external ,Function will check if it's source is Crystal or RC then Check if Clock Security Enabl or Disable
 * -# if The chosen Clock is PLL ,Function will check if PLL's source is HSI or HSE then set PLL Multiplication Factor and  PLL Prescaler
 * -# Wait for the ready flag in Chosen Clock then Switch to chosen clock
 */

void MRCC_voidInit (void)
{
	#if SYS_CLK == MRCC_HSI

		/* Set HSITRIM (High speed internal clock trimming) default value */
		RCC->CR &= ~(HSITRIM_MASK);
		RCC->CR |= HSITRIM_MASK;

		/* Enable HSI and Disable others */
		CLR_BIT(RCC->CR, CR_HSE_ON);
		CLR_BIT(RCC->CR, CR_PLL_ON);
		SET_BIT(RCC->CR, CR_HSI_ON);

		/* Polling on HSI ready flag */
		while (!GET_BIT(RCC->CR, CR_HSI_RDY));

		/* Switch to HSI */
		RCC->CFGR &= ~(TWO_BITS_MASK << CFGR_SW0);
		RCC->CFGR |= SW_HSI;

	#elif SYS_CLK == MRCC_HSE
		/* Check The clock source of HSE */
		#if HSE_SOURCE == MRCC_HSE_CRYSTAL
			/* Disable Bypass PIN */
			CLR_BIT(RCC->CR, CR_HSE_BYP);
		#elif HSE_SOURCE == MRCC_HSE_RC
			/* Enable Bypass PIN */
			SET_BIT(RCC->CR, CR_HSE_BYP);
		#else
			#error "Check HSE Clock source in MRCC_conf.h"
		#endif
		/* Enable HSE and Disable others */
		CLR_BIT(RCC->CR, CR_PLL_ON);
		CLR_BIT(RCC->CR, CR_HSI_ON);
		SET_BIT(RCC->CR, CR_HSE_ON);

		/* Polling on HSE ready flag */
		while (!GET_BIT(RCC->CR, CR_HSE_RDY));

		/* Switch to HSE */
		RCC->CFGR &= ~(TWO_BITS_MASK << CFGR_SW0);
		RCC->CFGR |= SW_HSE;

		/* Clock Security System */
		#if CLK_SECURITY == MRCC_CLK_SECURITY_ENABLE
			SET_BIT(RCC->CR, CR_CSS_ON);
		#elif CLK_SECURITY == MRCC_CLK_SECURITY_DISABLE
			CLR_BIT(RCC->CR, CR_CSS_ON);
		#else
			#error "Check Clock security in MRCC_conf.h"
		#endif

	#elif SYS_CLK == MRCC_PLL

		/* Set PLL Clock Source */
		#if PLL_SOURCE == MRCC_PLL_HSI
			/* Set PLL Source to HSI */
			CLR_BIT(RCC->PLLCFGR, PLLCFGR_PLLCFGR);
		#elif PLL_SOURCE == MRCC_PLL_HSE
			/* Check The clock source of HSE */
			#if HSE_SOURCE == MRCC_HSE_CRYSTAL
				/* Disable Bypass PIN */
				CLR_BIT(RCC->CR, CR_HSE_BYP);
			#elif HSE_SOURCE == MRCC_HSE_RC
				/* Enable Bypass PIN */
				SET_BIT(RCC->CR, CR_HSE_BYP);
			#else
				#error "Check PLL HSE Clock source in MRCC_conf.h"
			#endif
			/* Set PLL Source to HSE */
			SET_BIT(RCC->PLLCFGR, PLLCFGR_PLLCFGR);
		#else
			#error "Check PLL Clock Source in MRCC_conf.h"
		#endif

		/* Set PLL Prescaler */
		RCC->PLLCFGR &= ~(TWO_BITS_MASK << PLLCFGR_PLLP0);
		RCC->PLLCFGR |= (PLL_PRESCALER << PLLCFGR_PLLP0);

		/* Set PLL Multiplication Factor */
		RCC->PLLCFGR &= ~(NINE_BITS_MASK << PLLCFGR_PLLN);
		RCC->PLLCFGR |= (PLL_MULTIPLICATION_FACTOR << PLLCFGR_PLLN);

		/* Enable PLL and Disable others */
		CLR_BIT(RCC->CR, CR_HSI_ON);
		CLR_BIT(RCC->CR, CR_HSE_ON);
		SET_BIT(RCC->CR, CR_PLL_ON);

		/* Polling on PLL ready flag */
		while (!GET_BIT(RCC->CR, CR_PLL_RDY));

		/* Switch to PLL */
		RCC->CFGR &= ~(TWO_BITS_MASK << CFGR_SW0);
		RCC->CFGR |= SW_PLL;

	#else
		#error "Check System Clock source in MRCC_conf.h"
	#endif
}
/**
 * @fn 		void MRCC_voidEnablePeripheral (u32,u32)
 * @brief 	This function responsible of Enabling the peripheral Clock From RCC
 * @param 	Copy_u32BusID Copy of the Bus id in which the Peripheral Located
 * @param 	Copy_u32PeripheralID Copy of the Peripheral Id to access it in its bus
 * @return	none
 */
void MRCC_voidEnablePeripheral (u32 Copy_u32BusID, u32 Copy_u32PeripheralID)
{
	if (Copy_u32PeripheralID < 32)
	{
		switch (Copy_u32BusID)
		{
		/* Enable peripheral in APB1 bus */
		case MRCC_APB1: SET_BIT(RCC->APB1ENR, Copy_u32PeripheralID); break;
		/* Enable peripheral in APB2 bus */
		case MRCC_APB2: SET_BIT(RCC->APB2ENR, Copy_u32PeripheralID); break;
		/* Enable peripheral in AHB1 bus */
		case MRCC_AHB1: SET_BIT(RCC->AHB1ENR, Copy_u32PeripheralID); break;
		/* Enable peripheral in AHB2 bus */
		case MRCC_AHB2: SET_BIT(RCC->AHB2ENR, Copy_u32PeripheralID); break;
		default: break;
		}
	}
	else
	{
		/* Do nothing */
	}
}


/**
 * @fn 		void MRCC_voidDisablePeripheral (u32,u32)
 * @brief 	This function responsible of Disabling the peripheral Clock From RCC
 * @param 	Copy_u32BusID Copy of the Bus id in which the Peripheral Located
 * @param 	Copy_u32PeripheralID Copy of the Peripheral Id to access it in its bus
 * @return	none
 */
void MRCC_voidDisablePeripheral (u32 Copy_u32BusID, u32 Copy_u32PeripheralID)
{
	if (Copy_u32PeripheralID < 32)
	{
		switch (Copy_u32BusID)
		{
		/* Disable peripheral in APB1 bus */
		case MRCC_APB1: CLR_BIT(RCC->APB1ENR, Copy_u32PeripheralID); break;
		/* Disable peripheral in APB2 bus */
		case MRCC_APB2: CLR_BIT(RCC->APB2ENR, Copy_u32PeripheralID); break;
		/* Disable peripheral in AHB1 bus */
		case MRCC_AHB1: CLR_BIT(RCC->AHB1ENR, Copy_u32PeripheralID); break;
		/* Disable peripheral in AHB2 bus */
		case MRCC_AHB2: CLR_BIT(RCC->AHB2ENR, Copy_u32PeripheralID); break;
		default: break;
		}
	}
	else
	{
		/* Do nothing */
	}
}
/**
 * @fn 		void MRCC_voidSetAPB2Prescaler (u8)
 * @brief 	This function responsible of Determining the APB2 Bus Prescaler
 * @param 	Copy_u8Prescaler Copy of the prescaler value that will be assigned to APB2 Bus
 * @return	none
 */
void MRCC_voidSetAPB2Prescaler (u8 Copy_u8Prescaler)
{
	/* Check if the entered prescaler is in the valid range */
	if (Copy_u8Prescaler <= MRCC_APB_16_PRESCALER)
	{
		/* Set prescaler by bit masking */
		RCC->CFGR &= ~(THREE_BITS_MASK	 << CFGR_PPRE2);
		RCC->CFGR |= (Copy_u8Prescaler << CFGR_PPRE2);
	}
	else
	{
		/* Do Nothing */
	}
}

/**
 * @fn 		void MRCC_voidSetAPB1Prescaler (u8)
 * @brief 	This function responsible of Determining the APB1 Bus Prescaler
 * @param 	Copy_u8Prescaler Copy of the prescaler value that will be assigned to APB1 Bus
 * @return	none
 */
void MRCC_voidSetAPB1Prescaler (u8 Copy_u8Prescaler)
{
	/* Check if the entered prescaler is in the valid range */
	if (Copy_u8Prescaler <= MRCC_APB_16_PRESCALER)
	{
		/* Set prescaler by bit masking */
		RCC->CFGR &= ~(THREE_BITS_MASK	 << CFGR_PPRE1);
		RCC->CFGR |= (Copy_u8Prescaler << CFGR_PPRE1);
	}
	else
	{
		/* Do Nothing */
	}
}

/**
 * @fn 		void MRCC_voidSetAHB1Prescaler (u8)
 * @brief 	This function responsible of Determining the AHB1 Bus Prescaler
 * @param 	Copy_u8Prescaler Copy of the prescaler value that will be assigned to AHB1 Bus
 * @return	none
 */
void MRCC_voidSetAHB1Prescaler (u8 Copy_u8Prescaler)
{
	/* Check if the entered prescaler is in the valid range */
	if (Copy_u8Prescaler <= MRCC_AHB_512_PRESCALER)
	{
		/* Set prescaler by bit masking */
		RCC->CFGR &= ~(FOUR_BITS_MASK << CFGR_HPRE);
		RCC->CFGR |= (Copy_u8Prescaler << CFGR_HPRE);
	}
	else
	{
		/* Do Nothing */
	}
}
