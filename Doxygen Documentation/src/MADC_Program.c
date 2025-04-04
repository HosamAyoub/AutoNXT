/**
 * @file	MADC_Program.c
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The Analog to Digital converter C file that has the functions body which is resposible for the conversion process by the channels and the reading values after the conversions
 */


#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/ADC/MADC_Interface.h"
#include "../include/MCAL/ADC/MADC_Config.h"
#include "../include/MCAL/ADC/MADC_Private.h"


pf MADC_CallBack_Global = NULL;	//!< this pointer to function is used to hold the address of the specific funcoitn that will be executed when interrupt occures

/**
 * @fn 		void MADC_VoidInit(void)
 * @brief   This function is responsible of Initializing the adc and it's options and modes
 * @param 	none
 * @return 	none
 * @details This function will deal with the different modes and options and configurations of adc like: 
  * -# Set the resolution of the conversion of the channels of adc 
  * -# Set the mode of adc define the status either in single channels or multiple channels mode and single and also define the method of conversion either snigle or continuously 
  * -# Set the method of storing the data in data register after the conversion 
  * -# Set the time to notificate the system or raising a bit flag either after each conversion or after all conversions and select if the interrupt is desired or not 
  * -# Set the sampling time for each channel and also set the channels of conversion in the order and set the number of channels in the system
  * -# Set the dma options or disable the dma in general
  * -# Select the prescaler of the peripheral

 */
void MADC_VoidInit(void)
{

	u8 Iterator1_u8Local = 0;
	u8 SampleTime_u8arr[6] = {MADC_CH0_SAMPLE_TIME,MADC_CH1_SAMPLE_TIME,MADC_CH2_SAMPLE_TIME,MADC_CH3_SAMPLE_TIME,MADC_CH4_SAMPLE_TIME,MADC_CH5_SAMPLE_TIME};
	u8 RegularSequence_u8arr[6] = {ADC_REGULAR_SEQ_1,ADC_REGULAR_SEQ_2,ADC_REGULAR_SEQ_3,ADC_REGULAR_SEQ_4,ADC_REGULAR_SEQ_5,ADC_REGULAR_SEQ_6};

	/*Set the resolution for sampling*/
	MADC->CR1 &= ( ~(RESOLUTION_MASK << RESOLUTION_BITS) );
	MADC ->CR1 |= (MADC_RESOLUTION << RESOLUTION_BITS);

	/*Set the adc mode*/
	#if MADC_MODE == ADC_SGL_CHANNEL_SGL_CONVERSION
	CLR_BIT(MADC->CR1,CR1_SCAN);
	CLR_BIT(MADC->CR2,CR2_CONT);

	#elif MADC_MODE == ADC_SGL_CHANNEL_CONS_CONVERSION
	CLR_BIT(MADC->CR1,CR1_SCAN);
	SET_BIT(MADC->CR2,CR2_CONT);

	#elif MADC_MODE == ADC_MUL_CHANNEL_SGL_CONVERSION
	SET_BIT(MADC->CR1,CR1_SCAN);
	CLR_BIT(MADC->CR2,CR2_CONT);

	#elif MADC_MODE == ADC_MUL_CHANNEL_CONS_CONVERSION
	SET_BIT(MADC->CR1,CR1_SCAN);
	SET_BIT(MADC->CR2,CR2_CONT);

	#elif MADC_MODE == ADC_DISCONTINOUS

	#endif

	/*Set the data alignment*/
	#if MDAC_DATA_ALIGNMENT == ADC_RIGHT_ALIGNMENT
	CLR_BIT(MADC->CR2,CR2_ALIGN);
	#else
	SET_BIT(MADC->CR2,CR2_ALIGN);
	#endif

	#if MADC_EOCS_MODE == AFTER_ALL_CONVERSIONS
	CLR_BIT(MADC->CR2,CR2_EOCS);
	#else
	SET_BIT(MADC->CR2,CR2_EOCS);
	#endif

	#if MADC_DMA_MODE == ENABLE
	SET_BIT(MADC->CR2,CR2_DMA);
	#else
	CLR_BIT(MADC->CR2,CR2_DMA);
	#endif

	#if MADC_DMA_SELECTION == ADC_DMA_FREE_RUNNING_COPY
	SET_BIT(MADC->CR2,CR2_DDS);
	#else
	CLR_BIT(MADC->CR2,CR2_DDS);
	#endif

	/*Set the length of channels*/
	MADC->SQR1 &= (~(LENGTH_MASK << LENGTH_BITS));
	MADC->SQR1 |= ((MADC_REGULAR_CHANNELS_SEQUENCE_LENGTH-1) << LENGTH_BITS);

	/*Set the sampling time for the channels*/
	for(Iterator1_u8Local = 0; Iterator1_u8Local < MADC_REGULAR_CHANNELS_SEQUENCE_LENGTH; Iterator1_u8Local++)
	{
		MADC->SMPPR2 &= (~	(SAMPLE_MASK << (Iterator1_u8Local	* SAMPLE_BITS) )    );
		MADC->SMPPR2 |= (SampleTime_u8arr[Iterator1_u8Local] << (Iterator1_u8Local * SAMPLE_BITS) );
	}

	/*Set the regular Sequence Channels*/
	for(Iterator1_u8Local = 0; Iterator1_u8Local < MADC_REGULAR_CHANNELS_SEQUENCE_LENGTH; Iterator1_u8Local++)
	{
		MADC->SQR3 &= (~	(SEQUENCE_MASK << (SEQUENCE_BITS * Iterator1_u8Local)	)	);
		MADC->SQR3 |= (RegularSequence_u8arr[Iterator1_u8Local]	<< (SEQUENCE_BITS * Iterator1_u8Local)	);
	}

	/*Select the interrupt enable or disable*/
	#if MADC_EOC_INTERRUPT == ENABLE
	SET_BIT(MADC->CR1,CR1_EOCIE);
	#else
	CLR_BIT(MADC->CR1,CR1_EOCIE);
	#endif

	/*Set the prescaler*/
	MADC_COMMON_REG->CCR &= (~(PRESCALER_MASK <<PRESCALER_BITS));
	MADC_COMMON_REG ->CCR |= (MADC_PRESCALER << PRESCALER_BITS);
}

/**
 * @fn 		void MADC_VoidEnable(void)
 * @brief   This function is responsible for enabling the adc peripheral
 * @param 	none
 * @return 	none
 */
void MADC_VoidEnable(void)
{
	SET_BIT(MADC->CR2,CR2_ADON);
}

/**
 * @fn 		void MADC_VoidDisable(void)
 * @brief   This function is responsible of Disabling the adc peripheral
 * @param 	none
 * @return 	none
 */
void MADC_VoidDisable(void)
{
	CLR_BIT(MADC->CR2,CR2_ADON);
}

/**
 * @fn 		void MADC_VoidStartConversion(void)
 * @brief   This function is responsible of Starting the conversion
 * @param 	none
 * @return 	none
 */
void MADC_VoidStartConversion(void)
{
	SET_BIT(MADC->CR2,CR2_SWSTART);
}

/**
 * @fn 		void MADC_VoidStopConversion(void)
 * @brief   This function is responsible for stopping the conversion
 * @param 	none
 * @return 	none
 */
void MADC_VoidStopConversion(void)
{
	CLR_BIT(MADC->CR2,CR2_SWSTART);
}

/**
 * @fn 		u32 MADC_u16ReadSynch(void)
 * @brief   This function is responsible for reading the converted data which stored in data register 
 * @param 	none
 * @return 	the converted data which is digital value
 */
u32 MADC_u16ReadSynch(void)
{
	while(GET_BIT(MADC->SR,SR_EOC) == 0);
	return (MADC->DR);
}

/**
 * @fn 		void MADC_SetCallBack(pf ADC_CallBack)
 * @brief   This function is responsible for assign the global pointer to function with the specific function that will be executed when interrupt happens
 * @param 	the address or the name of the function that will be executed when interrupt happens
 * @return 	none
 */
void MADC_SetCallBack(pf ADC_CallBack)
{
	MADC_CallBack_Global = ADC_CallBack;
}

/**
 * @fn 		void ADC_IRQHandler(void)
 * @brief   This Handler function will be executed when the interrupt event generated and when execution this function will call the global pointer which hold the address of the specific function that will be ecexuted when interrupt happens 
 * @param 	the address or the name of the function that will be executed when interrupt happens
 * @return 	none
 */
void ADC_IRQHandler(void)
{
	MADC_CallBack_Global();
}

/**
 * @fn 		void MADC_VoidStartChannelConversion(u8 A_u8Channel)
 * @brief   This function is responsible for starting the conversion for specific channel
 * @param 	the channel which responsible for the conversion
 * @return 	none
 */
void MADC_VoidStartChannelConversion(u8 A_u8Channel)
{
	MADC->SQR3 &= (~	(SEQUENCE_MASK << (0)	)	);
	MADC->SQR3 |= (A_u8Channel	<< (0)	);
	SET_BIT(MADC->CR2,CR2_SWSTART);
}




