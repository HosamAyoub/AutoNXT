/**
 * @file     MTIMER_Program.c
 * @author	 Hesham Yasser
 * @version  1.0
 * @date 	 Nov 2, 2023
 * @brief    The MCAL_Timer C file that has the functions body **Ultrasonic** driver.
 *
 */



#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/TIMER/MTIMER_Interface.h"
#include "../include/MCAL/TIMER/MTIMER_Private.h"
#include "../include/MCAL/TIMER/MTIMER_Config.h"


PtrToFunc_void TIMER_CallBack [4];

/**
 * @fn 		void MTIMER_voidEnableTimer(TIMERS_t).
 * @brief 	This Function is to Enable The Specific Timer.
 *
 * @param 	A_Timer Number of selected Timer.
 * @return  none
 * @details This function Enable the specified Timer through CEN bit in CR1 Register of MTimer peripheral.
 */
void MTIMER_voidEnableTimer (TIMERS_t A_Timer)
{
	switch (A_Timer)
	{
	case TIMER2:
		SET_BIT(TIM2->CR1 , CR1_CEN);
		break;
	case TIMER3:
		SET_BIT(TIM3->CR1 , CR1_CEN);
		break;
	case TIMER4:
		SET_BIT(TIM4->CR1 , CR1_CEN);
		break;
	case TIMER5:
		SET_BIT(TIM5->CR1 , CR1_CEN);
		break;
	}
}

/*
 * UP/Down Count		->	CR1
 * Channels Connection	->	CR2
 * Slave mode 			->	SMCR
 * Interrupt mode		->	DIER
 * CC2 Direction 		->	CCMR1
 * CC1 Direction 		->	CCMR1
 * CC4 Direction 		->	CCMR2
 * CC3 Direction 		->	CCMR2
 * PreScaler			->	PSC
 * Caputre Enable & Polarity	-> CCMR
 */

/*
 * Read Values
 */

/*
 * Outcompare mode1,2		-> CCMR1
 * Outcompare mode3,4		-> CCMR2
 * set ccr registers		-> CCR
 *
 */
/**
 * @fn 		void MTIMER_EnableChannelInterrupt(TIMERS_t, CHANNELS_t)
 * @brief	This Function to Enable Capture/Compare interrupt
 *
 * @param	A_Timer     Number of selected Timer.
 * @param 	A_Channel	Number of selected Channel.
 * @return  none
 * @details This Function Enable Capture/Compare interrupt of specified channel through DIER register of MTimer peripheral.
 */

void MTIMER_EnableChannelInterrupt (TIMERS_t A_Timer, CHANNELS_t A_Channel)
{
	switch (A_Timer)
	{
	case TIMER2:
		SET_BIT(TIM2->DIER, A_Channel);
		break;
	case TIMER3:
		SET_BIT(TIM3->DIER, A_Channel);
		break;
	case TIMER4:
		SET_BIT(TIM4->DIER, A_Channel);
		break;
	case TIMER5:
		SET_BIT(TIM5->DIER, A_Channel);
		break;
	}
}

/**
 * @fn 		void MTIMER_voidSetPrescaler(TIMERS_t, u16)
 * @brief   This function to set Prescaler value of selected Timer.
 *
 * @param 	A_Timer			Number of selected Timer.
 * @param 	A_u16Prescaler	Value of Prescaler.
 * @return  none
 * @details This function to set Prescaler value of specified Timer through PSC register of MTimer peripheral.
 */
void MTIMER_voidSetPrescaler (TIMERS_t A_Timer, u16 A_u16Prescaler)
{
	switch (A_Timer)
	{
	case TIMER2:
		TIM2->PSC = A_u16Prescaler;
		break;
	case TIMER3:
		TIM3->PSC = A_u16Prescaler;
		break;
	case TIMER4:
		TIM4->PSC = A_u16Prescaler;
		break;
	case TIMER5:
		TIM5->PSC = A_u16Prescaler;
		break;
	}
}

/**
 * @fn		 void MTIMER_voidSetTimerCountDirection(TIMERS_t, CNT_DIR_t)
 * @brief	 This function to determine the direction of the counter: Upcounting or DownCounting
 *
 * @param    A_Timer			Number of selected Timer.
 * @param    A_CNT_Direction	Direction of Counter.
 * @return   none
 * @details  This function determine the counting mode of specified timer through DIR bit in CR1 register of MTimer peripheral
 * -#if you selected:
 *  - UpCounting: Write 0 on the DIR bit.
 *  - DownCounting: Write 1 on the DIR bit
 */
void MTIMER_voidSetTimerCountDirection (TIMERS_t A_Timer, CNT_DIR_t A_CNT_Direction)
{
	switch (A_Timer)
	{
	case TIMER2:
		switch (A_CNT_Direction)
		{
		case UPCOUNT:
			CLR_BIT (TIM2->CR1, CR1_DIR);
			break;
		case DOWNCOUNT:
			SET_BIT(TIM2->CR1, CR1_DIR);
			break;
		}
		break;
	case TIMER3:
		switch (A_CNT_Direction)
		{
		case UPCOUNT:
			CLR_BIT (TIM3->CR1, CR1_DIR);
			break;
		case DOWNCOUNT:
			SET_BIT(TIM3->CR1, CR1_DIR);
			break;
		}
		break;
	case TIMER4:
		switch (A_CNT_Direction)
		{
		case UPCOUNT:
			CLR_BIT (TIM4->CR1, CR1_DIR);
			break;
		case DOWNCOUNT:
			SET_BIT(TIM4->CR1, CR1_DIR);
			break;
		}
		break;
	case TIMER5:
		switch (A_CNT_Direction)
		{
		case UPCOUNT:
			CLR_BIT (TIM5->CR1, CR1_DIR);
			break;
		case DOWNCOUNT:
			SET_BIT(TIM5->CR1, CR1_DIR);
			break;
		}
		break;
	}
}

/**
 * @fn 		void MTIMER_voidSetChannelDirection(TIMERS_t, CHANNELS_t, CHANNEL_DIR_t)
 * @brief	This Function to determine channel Direction: INPUT/OUTPUT
 *
 * @param   A_Timer          Number of selected Timer.  ِ
 * @param   A_Channel        Number of selected Channel.ِ
 * @param   A_Direction      Direction of Channel.
 * @return  none
 * @details This Function used to determine channel Direction: INPUT/OUTPUT using CC1S bits(2 bits)
 * -#if These 2 bits:
 *  - Are Cleared channel is configured as output.
 *  - first bit is set and second bit is clear channel is configured as input, IC1 is mapped on TI1.
 *  - first bit is clear and second bit is set channel is configured as input, IC1 is mapped on TI2.
 *  - Are SET channel is configured as input, IC1 is mapped on TRC.
 */

void MTIMER_voidSetChannelDirection (TIMERS_t A_Timer, CHANNELS_t A_Channel, CHANNEL_DIR_t A_Direction)
{
	switch (A_Timer)
	{
	case TIMER2:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM2->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC1S);
			TIM2->CCMR1 |=  (A_Direction << CCMR1_CC1S);
			break;
		case CHANNEL2:
			TIM2->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC2S);
			TIM2->CCMR1 |=  (A_Direction << CCMR1_CC2S);
			break;
		case CHANNEL3:
			TIM2->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC3S);
			TIM2->CCMR2 |=  (A_Direction << CCMR2_CC3S);
			break;
		case CHANNEL4:
			TIM2->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC4S);
			TIM2->CCMR2 |=  (A_Direction << CCMR2_CC4S);
			break;
		}
		break;
	case TIMER3:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM3->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC1S);
			TIM3->CCMR1 |=  (A_Direction << CCMR1_CC1S);
			break;
		case CHANNEL2:
			TIM3->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC2S);
			TIM3->CCMR1 |=  (A_Direction << CCMR1_CC2S);
			break;
		case CHANNEL3:
			TIM3->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC3S);
			TIM3->CCMR2 |=  (A_Direction << CCMR2_CC3S);
			break;
		case CHANNEL4:
			TIM3->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC4S);
			TIM3->CCMR2 |=  (A_Direction << CCMR2_CC4S);
			break;
		}
		break;
	case TIMER4:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM4->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC1S);
			TIM4->CCMR1 |=  (A_Direction << CCMR1_CC1S);
			break;
		case CHANNEL2:
			TIM4->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC2S);
			TIM4->CCMR1 |=  (A_Direction << CCMR1_CC2S);
			break;
		case CHANNEL3:
			TIM4->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC3S);
			TIM4->CCMR2 |=  (A_Direction << CCMR2_CC3S);
			break;
		case CHANNEL4:
			TIM4->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC4S);
			TIM4->CCMR2 |=  (A_Direction << CCMR2_CC4S);
			break;
		}
		break;
	case TIMER5:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM5->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC1S);
			TIM5->CCMR1 |=  (A_Direction << CCMR1_CC1S);
			break;
		case CHANNEL2:
			TIM5->CCMR1 &= ~(TWO_BIT_MASK << CCMR1_CC2S);
			TIM5->CCMR1 |=  (A_Direction << CCMR1_CC2S);
			break;
		case CHANNEL3:
			TIM5->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC3S);
			TIM5->CCMR2 |=  (A_Direction << CCMR2_CC3S);
			break;
		case CHANNEL4:
			TIM5->CCMR2 &= ~(TWO_BIT_MASK << CCMR2_CC4S);
			TIM5->CCMR2 |=  (A_Direction << CCMR2_CC4S);
			break;
		}
		break;
	}
}


/**
 * @fn 		void MTIMER_voidSetChannelInputPolarity(TIMERS_t, CHANNELS_t, CHANNEL_POL_t)
 * @brief   This function to determine clock polarity of selected Timer and Channel.
 *
 * @param   A_Timer     Number of selected Timer.  ِ
 * @param   A_Channel   Number of selected Channel.ِ
 * @param   A_Polarity  Polarity of Clock: Rising/Falling/Both edges.
 * @return  none
 * @details This Function to determine clock polarity through CC1P and CC1NP bits in CCER Register
 * -# if:
 * 	- CC1P and CC1NP are cleared The Clock Polarity trigger or capture operations is => noninverted/rising edge.
 *  - CC1P is set and CC1NP is cleared The Clock Polarity trigger or capture operations is => inverted/falling edge.
 *  - CC1P is set and CC1NP is set The Clock Polarity trigger or capture operations is => noninverted/both edges
 *
 */

void MTIMER_voidSetChannelInputPolarity (TIMERS_t A_Timer, CHANNELS_t A_Channel, CHANNEL_POL_t A_Polarity)
{
	switch (A_Timer)
	{
	case TIMER2:
		switch (A_Channel)
		{
		case CHANNEL1:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM2->CCER, CCER_CC1P);
				CLR_BIT(TIM2->CCER, CCER_CC1NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM2->CCER, CCER_CC1P);
				CLR_BIT(TIM2->CCER, CCER_CC1NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM2->CCER, CCER_CC1P);
				SET_BIT(TIM2->CCER, CCER_CC1NP);
				break;
			}
			SET_BIT(TIM2->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM2->CCER, CCER_CC2P);
				CLR_BIT(TIM2->CCER, CCER_CC2NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM2->CCER, CCER_CC2P);
				CLR_BIT(TIM2->CCER, CCER_CC2NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM2->CCER, CCER_CC2P);
				SET_BIT(TIM2->CCER, CCER_CC2NP);
				break;
			}
			SET_BIT(TIM2->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM2->CCER, CCER_CC3P);
				CLR_BIT(TIM2->CCER, CCER_CC3NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM2->CCER, CCER_CC3P);
				CLR_BIT(TIM2->CCER, CCER_CC3NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM2->CCER, CCER_CC3P);
				SET_BIT(TIM2->CCER, CCER_CC3NP);
				break;
			}
			SET_BIT(TIM2->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM2->CCER, CCER_CC4P);
				CLR_BIT(TIM2->CCER, CCER_CC4NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM2->CCER, CCER_CC4P);
				CLR_BIT(TIM2->CCER, CCER_CC4NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM2->CCER, CCER_CC4P);
				SET_BIT(TIM2->CCER, CCER_CC4NP);
				break;
			}
			SET_BIT(TIM2->CCER, CCER_CC4E);
			break;
		}
		break;
	case TIMER3:
		switch (A_Channel)
		{
		case CHANNEL1:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM3->CCER, CCER_CC1P);
				CLR_BIT(TIM3->CCER, CCER_CC1NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM3->CCER, CCER_CC1P);
				CLR_BIT(TIM3->CCER, CCER_CC1NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM3->CCER, CCER_CC1P);
				SET_BIT(TIM3->CCER, CCER_CC1NP);
				break;
			}
			SET_BIT(TIM3->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM3->CCER, CCER_CC2P);
				CLR_BIT(TIM3->CCER, CCER_CC2NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM3->CCER, CCER_CC2P);
				CLR_BIT(TIM3->CCER, CCER_CC2NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM3->CCER, CCER_CC2P);
				SET_BIT(TIM3->CCER, CCER_CC2NP);
				break;
			}
			SET_BIT(TIM3->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM3->CCER, CCER_CC3P);
				CLR_BIT(TIM3->CCER, CCER_CC3NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM3->CCER, CCER_CC3P);
				CLR_BIT(TIM3->CCER, CCER_CC3NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM3->CCER, CCER_CC3P);
				SET_BIT(TIM3->CCER, CCER_CC3NP);
				break;
			}
			SET_BIT(TIM3->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM3->CCER, CCER_CC4P);
				CLR_BIT(TIM3->CCER, CCER_CC4NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM3->CCER, CCER_CC4P);
				CLR_BIT(TIM3->CCER, CCER_CC4NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM3->CCER, CCER_CC4P);
				SET_BIT(TIM3->CCER, CCER_CC4NP);
				break;
			}
			SET_BIT(TIM3->CCER, CCER_CC4E);
			break;
		}
		break;
	case TIMER4:
		switch (A_Channel)
		{
		case CHANNEL1:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM4->CCER, CCER_CC1P);
				CLR_BIT(TIM4->CCER, CCER_CC1NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM4->CCER, CCER_CC1P);
				CLR_BIT(TIM4->CCER, CCER_CC1NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM4->CCER, CCER_CC1P);
				SET_BIT(TIM4->CCER, CCER_CC1NP);
				break;
			}
			SET_BIT(TIM4->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM4->CCER, CCER_CC2P);
				CLR_BIT(TIM4->CCER, CCER_CC2NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM4->CCER, CCER_CC2P);
				CLR_BIT(TIM4->CCER, CCER_CC2NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM4->CCER, CCER_CC2P);
				SET_BIT(TIM4->CCER, CCER_CC2NP);
				break;
			}
			SET_BIT(TIM4->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM4->CCER, CCER_CC3P);
				CLR_BIT(TIM4->CCER, CCER_CC3NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM4->CCER, CCER_CC3P);
				CLR_BIT(TIM4->CCER, CCER_CC3NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM4->CCER, CCER_CC3P);
				SET_BIT(TIM4->CCER, CCER_CC3NP);
				break;
			}
			SET_BIT(TIM4->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM4->CCER, CCER_CC4P);
				CLR_BIT(TIM4->CCER, CCER_CC4NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM4->CCER, CCER_CC4P);
				CLR_BIT(TIM4->CCER, CCER_CC4NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM4->CCER, CCER_CC4P);
				SET_BIT(TIM4->CCER, CCER_CC4NP);
				break;
			}
			SET_BIT(TIM4->CCER, CCER_CC4E);
			break;
		}
		break;
	case TIMER5:
		switch (A_Channel)
		{
		case CHANNEL1:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM5->CCER, CCER_CC1P);
				CLR_BIT(TIM5->CCER, CCER_CC1NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM5->CCER, CCER_CC1P);
				CLR_BIT(TIM5->CCER, CCER_CC1NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM5->CCER, CCER_CC1P);
				SET_BIT(TIM5->CCER, CCER_CC1NP);
				break;
			}
			SET_BIT(TIM5->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM5->CCER, CCER_CC2P);
				CLR_BIT(TIM5->CCER, CCER_CC2NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM5->CCER, CCER_CC2P);
				CLR_BIT(TIM5->CCER, CCER_CC2NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM5->CCER, CCER_CC2P);
				SET_BIT(TIM5->CCER, CCER_CC2NP);
				break;
			}
			SET_BIT(TIM5->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM5->CCER, CCER_CC3P);
				CLR_BIT(TIM5->CCER, CCER_CC3NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM5->CCER, CCER_CC3P);
				CLR_BIT(TIM5->CCER, CCER_CC3NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM5->CCER, CCER_CC3P);
				SET_BIT(TIM5->CCER, CCER_CC3NP);
				break;
			}
			SET_BIT(TIM5->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			switch (A_Polarity)
			{
			case RISING_EDGE:
				CLR_BIT(TIM5->CCER, CCER_CC4P);
				CLR_BIT(TIM5->CCER, CCER_CC4NP);
				break;
			case FALLING_EDGE:
				SET_BIT(TIM5->CCER, CCER_CC4P);
				CLR_BIT(TIM5->CCER, CCER_CC4NP);
				break;
			case BOTH_EDGES:
				SET_BIT(TIM5->CCER, CCER_CC4P);
				SET_BIT(TIM5->CCER, CCER_CC4NP);
				break;
			}
			SET_BIT(TIM5->CCER, CCER_CC4E);
			break;
		}
		break;
	}
}


/**
 * @fn 		u32 MTIMER_u32ReadChannelValue(TIMERS_t, CHANNELS_t)
 * @brief   This Function to Read the captured value from the specified channel.
 *
 * @param	A_Timer	   Number of selected Timer.
 * @param 	A_Channel  The channel from which to read the captured value.
 * @return  u32        The captured value from the specified channel.
 * @details This Function return u32 Captured value from  specified channel using CCR register of MTimer peripheral.
 */
u32 MTIMER_u32ReadChannelValue (TIMERS_t A_Timer, CHANNELS_t A_Channel)
{
	u32 local_ReturnValue = 0;
	switch (A_Timer)
	{
	case TIMER2:
		switch (A_Channel)
		{
		case CHANNEL1:
			local_ReturnValue = TIM2->CCR1;
			break;
		case CHANNEL2:
			local_ReturnValue = TIM2->CCR2;
			break;
		case CHANNEL3:
			local_ReturnValue = TIM2->CCR3;
			break;
		case CHANNEL4:
			local_ReturnValue = TIM2->CCR4;
			break;
		}
		break;
	case TIMER3:
		switch (A_Channel)
		{
		case CHANNEL1:
			local_ReturnValue = TIM3->CCR1;
			break;
		case CHANNEL2:
			local_ReturnValue = TIM3->CCR2;
			break;
		case CHANNEL3:
			local_ReturnValue = TIM3->CCR3;
			break;
		case CHANNEL4:
			local_ReturnValue = TIM3->CCR4;
			break;
		}
		break;
	case TIMER4:
		switch (A_Channel)
		{
		case CHANNEL1:
			local_ReturnValue = TIM4->CCR1;
			break;
		case CHANNEL2:
			local_ReturnValue = TIM4->CCR2;
			break;
		case CHANNEL3:
			local_ReturnValue = TIM4->CCR3;
			break;
		case CHANNEL4:
			local_ReturnValue = TIM4->CCR4;
			break;
		}
		break;
	case TIMER5:
		switch (A_Channel)
		{
		case CHANNEL1:
			local_ReturnValue = TIM5->CCR1;
			break;
		case CHANNEL2:
			local_ReturnValue = TIM5->CCR2;
			break;
		case CHANNEL3:
			local_ReturnValue = TIM5->CCR3;
			break;
		case CHANNEL4:
			local_ReturnValue = TIM5->CCR4;
			break;
		}
		break;
	}
	return local_ReturnValue;
}

/**
 * @fn 		void MTIMER_voidSetCallBack(TIMERS_t, PtrToFunc_void)
 * @brief   This Function is used to Execute Function from other driver according to specific Interrrupt.
 *
 * @param 	A_Timer  Number of selected Timer.
 * @param	A_CallBack pointer to function that will be executed.
 * @return  none.
 * @details This Function holds pointer to Specified Function from other driver to be executed in specific Interrrupt function.
 */
void MTIMER_voidSetCallBack (TIMERS_t A_Timer, PtrToFunc_void A_CallBack)
{
	TIMER_CallBack[A_Timer] = A_CallBack;
}

/**
 * @fn 		void MTIMER_voidSetCounterValue(TIMERS_t, u32)
 * @brief 	This function to set The counter value in CNT register.
 *
 * @param   A_Timer        Number of selected Timer.
 * @param   A_u32CNTValue  The Counter value to set in CNT register.
 * @return  none.
 * @details This Function set a value in a counter register (CNT) of MTimer peripheral.
 */


void MTIMER_voidSetCounterValue (TIMERS_t A_Timer, u32 A_u32CNTValue)
{
	switch (A_Timer)
	{
	case TIMER2:
		TIM2->CNT = A_u32CNTValue;
		break;
	case TIMER3:
		TIM3->CNT = A_u32CNTValue;
		break;
	case TIMER4:
		TIM4->CNT = A_u32CNTValue;
		break;
	case TIMER5:
		TIM5->CNT = A_u32CNTValue;
		break;
	}
}


/**
 * @fn 		void MTIMER_voidSetARRValue(TIMERS_t, u32)
 * @brief   This function to determine The max value of counts the counter will reach it.
 *
 * @param   A_Tِimer			Number of selected Timer.
 * @param   A_u32ARRValue   The Max value of counts the counter will reach it.
 * @return  none.
 * @details This Function Set the maximum value of Ticks through auto-reload register(ARR) of MTimer peripheral.
 */
void MTIMER_voidSetARRValue (TIMERS_t A_Timer, u32 A_u32ARRValue)
{
	switch (A_Timer)
	{
	case TIMER2:
		TIM2->ARR = A_u32ARRValue;
		break;
	case TIMER3:
		TIM3->ARR = A_u32ARRValue;
		break;
	case TIMER4:
		TIM4->ARR = A_u32ARRValue;
		break;
	case TIMER5:
		TIM5->ARR = A_u32ARRValue;
		break;
	}
}

/**
 * @fn 		void MTIMER_voidSetCCRValue(TIMERS_t, CHANNELS_t, u32)
 * @brief 	This function to Set the compare value for the specified channel.
 *
 * @param A_Timer        Number of selected Timer.
 * @param A_Channel      The channel for which to set the compare value.
 * @param A_u32CCRValue  The compare value to be set.
 * @return none.
 * @details This function to Set the compare value for the specified channel in specified Timer through CCR register of MTimer peripheral.
 */
void MTIMER_voidSetCCRValue (TIMERS_t A_Timer, CHANNELS_t A_Channel, u32 A_u32CCRValue)
{
	switch (A_Timer)
	{
	case TIMER2:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM2->CCR1 = A_u32CCRValue;
			break;
		case CHANNEL2:
			TIM2->CCR2 = A_u32CCRValue;
			break;
		case CHANNEL3:
			TIM2->CCR3 = A_u32CCRValue;
			break;
		case CHANNEL4:
			TIM2->CCR4 = A_u32CCRValue;
			break;
		}
		break;
	case TIMER3:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM3->CCR1 = A_u32CCRValue;
			break;
		case CHANNEL2:
			TIM3->CCR2 = A_u32CCRValue;
			break;
		case CHANNEL3:
			TIM3->CCR3 = A_u32CCRValue;
			break;
		case CHANNEL4:
			TIM3->CCR4 = A_u32CCRValue;
			break;
		}
		break;
	case TIMER4:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM4->CCR1 = A_u32CCRValue;
			break;
		case CHANNEL2:
			TIM4->CCR2 = A_u32CCRValue;
			break;
		case CHANNEL3:
			TIM4->CCR3 = A_u32CCRValue;
			break;
		case CHANNEL4:
			TIM4->CCR4 = A_u32CCRValue;
			break;
		}
		break;
	case TIMER5:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM5->CCR1 = A_u32CCRValue;
			break;
		case CHANNEL2:
			TIM5->CCR2 = A_u32CCRValue;
			break;
		case CHANNEL3:
			TIM5->CCR3 = A_u32CCRValue;
			break;
		case CHANNEL4:
			TIM5->CCR4 = A_u32CCRValue;
			break;
		}
		break;
	}
}



/**
 * @fn 		u8 MTIMER_u8ReadInterruptState(TIMERS_t, CHANNELS_t)
 * @brief   This function to read state of Capture/compare interrupt flag of the specified channel.
 *
 * @param   A_Timer   Number of selected Timer.
 * @param   A_Channel The channel from which to read the interrupt state.
 * @return  u8 State value of Capture/compare interrupt flag.
 * @details This Function return u8 Value to determine state of Capture/compare interrupt flag of the specified channel in specified Timer through SR register
 * -#if It returns:
 *   - 0 and channel is configured as output: No match, if channel is input: No input capture occurred.
 *   - 1 and channel is configured as output: The content of the counter TIMx_CNT matches the content of the TIMx_CCR register, if channel is input: The counter value has been captured in TIMx_CCR register.
 */

u8 MTIMER_u8ReadInterruptState (TIMERS_t A_Timer, CHANNELS_t A_Channel)
{
	u8 local_ReturnValue = 0;
	switch (A_Timer)
	{
	case TIMER2:
		local_ReturnValue = GET_BIT(TIM2->SR, A_Channel);
		break;
	case TIMER3:
		local_ReturnValue = GET_BIT(TIM3->SR, A_Channel);
		break;
	case TIMER4:
		local_ReturnValue = GET_BIT(TIM4->SR, A_Channel);
		break;
	case TIMER5:
		local_ReturnValue = GET_BIT(TIM5->SR, A_Channel);
		break;
	}
	return local_ReturnValue;
}


/**
 * @fn 	  void MTIMER_voidSetOutputMode(TIMERS_t, CHANNELS_t, OUT_MODES_t)
 * @brief This function to determine the output mode of of the specified channel.
 *
 * @param  A_Timer       Number of selected Timer.
 * @param  A_Channel 	 Number of selected Channel.
 * @param  A_Mode        Determine the output mode of specified channel.
 * @return none.
 * @details This function to determine the output mode of of the specified channel through OCM bits(Three bits)
 * -# if These 3 bits:
 * 	- Are cleared => Frozen - The comparison between the output compare register TIMx_CCR and the counter TIMx_CNT has no effect on the outputs.
 *  - First bit is set and other 2 bits are cleared =>  Set channel to active level on match.
 *  - First bit cleared, Second bit is set and Third bit cleared => Set channel to inactive level on match.
 *  - First,Second bits are SET and Third bit is cleared => Toggle - OCREF toggles when TIMx_CNT=TIMx_CCR.
 *  - First,Second bits are Cleared and Third bit is set => Force inactive level -OCREF is forced low.
 *  - First,Third bits are set and second bit cleared => Force active level- OCREF is forced high.
 *  - First bit cleared, Second and Third bits are SET => PWM mode 1 - In upcounting, channel is active as long as TIMx_CNT<TIMx_CCRx,else inactive.In downcounting,channel 1 is inactive (OCREF=‘0) as long as TIMx_CNT>TIMx_CCRx else active (OCREF=1).
 *  - Are SETs => PWM mode 2-In upcounting, channel is inactive as long as TIMx_CNT<TIMx_CCRx, else active.In downcounting,channel 1 is active as long as TIMx_CNT>TIMx_CCRx else inactive.
 */
void MTIMER_voidSetOutputMode (TIMERS_t A_Timer, CHANNELS_t A_Channel, OUT_MODES_t A_Mode)
{
	switch (A_Timer)
	{
	case TIMER2:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM2->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC1M);
			TIM2->CCMR1 |=  (A_Mode << CCMR1_OC1M);
			break;
		case CHANNEL2:
			TIM2->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC2M);
			TIM2->CCMR1 |=  (A_Mode << CCMR1_OC2M);
			break;
		case CHANNEL3:
			TIM2->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC3M);
			TIM2->CCMR2 |=  (A_Mode << CCMR2_OC3M);
			break;
		case CHANNEL4:
			TIM2->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC4M);
			TIM2->CCMR2 |=  (A_Mode << CCMR2_OC4M);
			break;
		}
		break;
	case TIMER3:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM3->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC1M);
			TIM3->CCMR1 |=  (A_Mode << CCMR1_OC1M);
			break;
		case CHANNEL2:
			TIM3->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC2M);
			TIM3->CCMR1 |=  (A_Mode << CCMR1_OC2M);
			break;
		case CHANNEL3:
			TIM3->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC3M);
			TIM3->CCMR2 |=  (A_Mode << CCMR2_OC3M);
			break;
		case CHANNEL4:
			TIM3->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC4M);
			TIM3->CCMR2 |=  (A_Mode << CCMR2_OC4M);
			break;
		}
		break;
	case TIMER4:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM4->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC1M);
			TIM4->CCMR1 |=  (A_Mode << CCMR1_OC1M);
			break;
		case CHANNEL2:
			TIM4->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC2M);
			TIM4->CCMR1 |=  (A_Mode << CCMR1_OC2M);
			break;
		case CHANNEL3:
			TIM4->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC3M);
			TIM4->CCMR2 |=  (A_Mode << CCMR2_OC3M);
			break;
		case CHANNEL4:
			TIM4->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC4M);
			TIM4->CCMR2 |=  (A_Mode << CCMR2_OC4M);
			break;
		}
		break;
	case TIMER5:
		switch (A_Channel)
		{
		case CHANNEL1:
			TIM5->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC1M);
			TIM5->CCMR1 |=  (A_Mode << CCMR1_OC1M);
			break;
		case CHANNEL2:
			TIM5->CCMR1 &= ~(THREE_BIT_MASK << CCMR1_OC2M);
			TIM5->CCMR1 |=  (A_Mode << CCMR1_OC2M);
			break;
		case CHANNEL3:
			TIM5->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC3M);
			TIM5->CCMR2 |=  (A_Mode << CCMR2_OC3M);
			break;
		case CHANNEL4:
			TIM5->CCMR2 &= ~(THREE_BIT_MASK << CCMR2_OC4M);
			TIM5->CCMR2 |=  (A_Mode << CCMR2_OC4M);
			break;
		}
		break;
	}
}


/**
 * @fn 	  void MTIMER_voidEnableOutputPin(TIMERS_t, CHANNELS_t)
 * @brief This Function to Enable Capture/Compare output.
 *
 * @param A_Timer        Number of selected Timer.
 * @param A_Channel      The channel for which to Enable Capture/Compare output.
 * @return none.
 * @details This Function This Function to Enable Capture/Compare output through CCxE bit in CCER Register.
 */
void MTIMER_voidEnableOutputPin (TIMERS_t A_Timer, CHANNELS_t A_Channel)
{
	switch (A_Timer)
	{
	case TIMER2:
		switch (A_Channel)
		{
		case CHANNEL1:
			SET_BIT (TIM2->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			SET_BIT (TIM2->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			SET_BIT (TIM2->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			SET_BIT (TIM2->CCER, CCER_CC4E);
			break;
		}
		break;
	case TIMER3:
		switch (A_Channel)
		{
		case CHANNEL1:
			SET_BIT (TIM3->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			SET_BIT (TIM3->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			SET_BIT (TIM3->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			SET_BIT (TIM3->CCER, CCER_CC4E);
			break;
		}
		break;
	case TIMER4:
		switch (A_Channel)
		{
		case CHANNEL1:
			SET_BIT (TIM4->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			SET_BIT (TIM4->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			SET_BIT (TIM4->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			SET_BIT (TIM4->CCER, CCER_CC4E);
			break;
		}
		break;
	case TIMER5:
		switch (A_Channel)
		{
		case CHANNEL1:
			SET_BIT (TIM5->CCER, CCER_CC1E);
			break;
		case CHANNEL2:
			SET_BIT (TIM5->CCER, CCER_CC2E);
			break;
		case CHANNEL3:
			SET_BIT (TIM5->CCER, CCER_CC3E);
			break;
		case CHANNEL4:
			SET_BIT (TIM5->CCER, CCER_CC4E);
			break;
		}
		break;
	}
}


/**
 * @fn     void MTIMER_voidSetPWMOption(TIMERS_t, CHANNELS_t, u32, u32, u16)
 * @brief  This Function Initialize the PWM MTIM peripheral output with the specified configuration.
 *
 * @param A_Timer          Number of selected Timer.
 * @param A_Channel        The channel for which to Output the PWM.
 * @param A_ARRValue	   The Max value of counts the counter will reach it.
 * @param A_CRRValue	   The compare value for the specified channel.
 * @param A_u16Prescaler   The value of Prescaler.
 * @return none.
 * @details -#This Function Initialize the PWM with the specified configuration.
 * 			  -Set Precaler value.
 * 			  -Set Timer counter Direction.
 * 			  -Set Channel Direction.
 * 			  -Set Output Mode.
 * 			  -Set Max No.Counts value.
 * 			  -Set Counter value.
 * 			  -Enable Output pin.
 * 			  -Enable Timer.
 *
 *
 */
void MTIMER_voidSetPWMOption (TIMERS_t A_Timer, CHANNELS_t A_Channel, u32 A_ARRValue, u32 A_CRRValue, u16 A_u16Prescaler)
{
	MTIMER_voidSetPrescaler(A_Timer, A_u16Prescaler);
	MTIMER_voidSetTimerCountDirection(A_Timer, UPCOUNT);
	MTIMER_voidSetChannelDirection(A_Timer, A_Channel, CHANNEL_OUTPUT);
	MTIMER_voidSetOutputMode(A_Timer, A_Channel,PWM_MODE_1);
	MTIMER_voidSetARRValue(A_Timer,A_ARRValue);
	MTIMER_voidSetCCRValue(A_Timer,A_Channel,A_CRRValue);
	MTIMER_voidEnableOutputPin(A_Timer,A_Channel);
	MTIMER_voidEnableTimer(A_Timer);
}

/**
 * @fn void TIM2_IRQHandler(void)
 * @brief Timer2 Interrupt Function.
 *
 */

void TIM2_IRQHandler (void)
{
	if (TIMER_CallBack[TIMER2] != NULL)
	{
		TIMER_CallBack[TIMER2]();
	}
}

/**
 * @fn void TIM3_IRQHandler(void)
 * @brief Timer3 Interrupt Function.
 *
 */
void TIM3_IRQHandler (void)
{
	if (TIMER_CallBack[TIMER3] != NULL)
	{
		TIMER_CallBack[TIMER3]();
	}
}

/**
 * @fn void TIM4_IRQHandler(void)
 * @brief Timer4 Interrupt Function.
 *
 */
void TIM4_IRQHandler (void)
{
	if (TIMER_CallBack[TIMER4] != NULL)
	{
		TIMER_CallBack[TIMER4]();
	}
}

/**
 * @fn void TIM5_IRQHandler(void)
 * @brief Timer5 Interrupt Function.
 *
 */
void TIM5_IRQHandler (void)
{
	if (TIMER_CallBack[TIMER5] != NULL)
	{
		TIMER_CallBack[TIMER5]();
	}
}
