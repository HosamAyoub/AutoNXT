/**
 * @file	MADC_Interface.h
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The analog to digital interface header file that has all the prototypes of **ADC** driver
 */

#ifndef MADC_INTERFACE_H_
#define MADC_INTERFACE_H_


/****************Channels******************/
#define ADC_CHANNEL0													0	//!< This macro defines channel 0 and is an argument @ref MADC_VoidStartChannelConversion
#define ADC_CHANNEL1													1	//!< This macro defines channel 1 and is an argument @ref MADC_VoidStartChannelConversion
#define ADC_CHANNEL2													2	//!< This macro defines channel 2 and is an argument @ref MADC_VoidStartChannelConversion
#define ADC_CHANNEL3													3	//!< This macro defines channel 3 and is an argument @ref MADC_VoidStartChannelConversion
#define ADC_CHANNEL4													4	//!< This macro defines channel 4 and is an argument @ref MADC_VoidStartChannelConversion
#define ADC_CHANNEL5													5	//!< This macro defines channel 5 and is an argument @ref MADC_VoidStartChannelConversion

/******************APIs********************/


/**
 * @fn 		void MADC_VoidInit(void)
 * @brief   This function is responsible of Initializing the adc and it's options and modes
 * @param 	none
 * @return 	none
 */
void MADC_VoidInit(void);

/**
 * @fn 		void MADC_VoidEnable(void)
 * @brief   This function is responsible for enabling the adc peripheral
 * @param 	none
 * @return 	none
 */
void MADC_VoidEnable(void);

/**
 * @fn 		void MADC_VoidDisable(void)
 * @brief   This function is responsible of Disabling the adc peripheral
 * @param 	none
 * @return 	none
 */
void MADC_VoidDisable(void);

/**
 * @fn 		void MADC_VoidStartConversion(void)
 * @brief   This function is responsible of Starting the conversion
 * @param 	none
 * @return 	none
 */
void MADC_VoidStartConversion(void);

/**
 * @fn 		void MADC_VoidStopConversion(void)
 * @brief   This function is responsible for stopping the conversion
 * @param 	none
 * @return 	none
 */
void MADC_VoidStopConversion(void);

/**
 * @fn 		u32 MADC_u16ReadSynch(void)
 * @brief   This function is responsible for reading the converted data which stored in data register 
 * @param 	none
 * @return 	the converted data which is digital value
 */
u32 MADC_u16ReadSynch(void);

/**
 * @fn 		void MADC_SetCallBack(pf ADC_CallBack)
 * @brief   This function is responsible for assign the global pointer to function with the specific function that will be executed when interrupt happens
 * @param 	the address or the name of the function that will be executed when interrupt happens
 * @return 	none
 */
void MADC_SetCallBack(pf ADC_CallBack);

/**
 * @fn 		void MADC_VoidStartChannelConversion(u8 A_u8Channel)
 * @brief   This function is responsible for starting the conversion for specific channel
 * @param 	the channel which responsible for the conversion
 * @return 	none
 */
void MADC_VoidStartChannelConversion(u8 A_u8Channel);

#endif /* MADC_INTERFACE_H_ */
