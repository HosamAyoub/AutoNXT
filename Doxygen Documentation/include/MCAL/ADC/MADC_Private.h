/**
 * @file	MADC_Private.h
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The analog to digital converter header file that has all the addresses of the registers, their base address and any private macros of **ADC** driver
 */

#ifndef MADC_PRIVATE_H_
#define MADC_PRIVATE_H_

#define MADC_BASE_ADDRESS												(0X40012000)	//!< The **ADC** Base address

/**
 * @struct 	MADC_t
 * @brief	This struct has the ADC register
 *
 */
typedef struct
{
	u32 SR;			//!< ADC Status register
	u32 CR1;		//!< ADC Control register 1
	u32 CR2;		//!< ADC Control register 2
	u32 SMPPR1;		//!< ADC Sample Time register 1
	u32 SMPPR2;		//!< ADC Sample Time register 2
	u32 JOFR1;		//!< ADC injected channel data offset register 1
	u32 JOFR2;		//!< ADC injected channel data offset register 2
	u32 JOFR3;		//!< ADC injected channel data offset register 3
	u32 JOFR4;		//!< ADC injected channel data offset register 4
	u32 HTR;		//!< ADC watchdog higher threshold register
	u32 LTR;		//!< ADC watchdog lower threshold register
	u32 SQR1;		//!< ADC regular sequence register 1
	u32 SQR2;		//!< ADC regular sequence register 2
	u32 SQR3;		//!< ADC regular sequence register 3
	u32 JSQR;		//!< ADC injected sequence register
	u32 JDR1;		//!< ADC injected data register 1
	u32 JDR2;		//!< ADC injected data register 2
	u32 JDR3;		//!< ADC injected data register 3
	u32 JDR4;		//!< ADC injected data register 4
	u32 DR;			//!< ADC regular data register
}MADC_t;

/**
 * @struct 	MADC_COMMON_REG_t
 * @brief	This struct has the ADC Common register
 *
 */

typedef struct
{
	u32 CSR;		//!< ADC common status register
	u32 CCR;		//!< ADC common control register
	u32 CDR;		//!< ADC common data register
}MADC_COMMON_REG_t;


#define MADC														((volatile	MADC_t*)MADC_BASE_ADDRESS)	//!< This function set the specified BIT

#define MADC_COMMON_REG										((volatile	MADC_COMMON_REG_t*)(MADC_BASE_ADDRESS+0x300))	//!< This function set the specified BIT



/**********************************************GENERAL_MACROS**************************************************/


#define ENABLE															1	//!< This macro indicates to enable 1
#define DISABLE															0	//!< This macro indicates to disable 0


#define ADC_6_BIT												      	3	//!< Programming resolution is 6 bits resolution of the conversion
#define ADC_8_BIT												      	2	//!< Programming resolution is 8 bits resolution of the conversion
#define ADC_10_BIT												      	1	//!< Programming resolution is 10 bits resolution of the conversion
#define ADC_12_BIT												      	0	//!< Programming resolution is 12 bits resolution of the conversion


#define ADC_PRESCALER_2											      	0	//!< Selecting the clock to be divided by 2
#define ADC_PRESCALER_4											      	1	//!< Selecting the clock to be divided by 4
#define ADC_PRESCALER_6											      	2	//!< Selecting the clock to be divided by 6
#define ADC_PRESCALER_8											      	3	//!< Selecting the clock to be divided by 8

#define ADC_RIGHT_ALIGNMENT												0	//!< Selecting Right alinged method to store the converted data by adc in the data register
#define ADC_LEFT_ALIGNMENT												1	//!< Selecting Left alinged method to store the converted data by adc in the data register

#define AFTER_ALL_CONVERSIONS											0	//!< Selecting the flag to be raised after all conversions of the channels 
#define AFTER_EACH_CONVERSION											1	//!< Selecting the flag to be raised after each conversion of each channel

#define ADC_DMA_SINGLE_COPY   											0	//!< Selecting the single copy of data to the memory
#define ADC_DMA_FREE_RUNNING_COPY   									1	//!< Selecting continous copies of data to the memory


#define ADC_SAMPLE_3_CYCLES												0	//!< Select the sampling time of the adc to be 3 times of the adc clock
#define ADC_SAMPLE_15_CYCLES											1	//!< Selecting the sampling time of the adc to be 15 times of the adc clock
#define ADC_SAMPLE_28_CYCLES											2	//!< Selecting the sampling time of the adc to be 28 times of the adc clock
#define ADC_SAMPLE_56_CYCLES											3	//!< Selecting the sampling time of the adc to be 56 times of the adc clock
#define ADC_SAMPLE_84_CYCLES											4	//!< Selecting the sampling time of the adc to be 84 times of the adc clock
#define ADC_SAMPLE_112_CYCLES											5	//!< Selecting the sampling time of the adc to be 112 times of the adc clock
#define ADC_SAMPLE_144_CYCLES											6	//!< Selecting the sampling time of the adc to be 144 times of the adc clock
#define ADC_SAMPLE_480_CYCLES											7	//!< Selecting the sampling time of the adc to be 480 times of the adc clock



#define ADC_SGL_CHANNEL_SGL_CONVERSION									0	//!< Selecting single channel and only single conversion
#define ADC_SGL_CHANNEL_CONS_CONVERSION									1	//!< Selecting single channel and continuously conversions 
#define ADC_MUL_CHANNEL_SGL_CONVERSION									2	//!< Selecting a multiple channels and single conversion for each channel
#define ADC_MUL_CHANNEL_CONS_CONVERSION									3	//!< Selecting a multiple channels and continuously conversion for each channel
#define ADC_DISCONTINOUS												4	//!< Selecting ADC Discountinous mode




/**********************************************BIT_MACROS**************************************************/

#define CR1_EOCIE														5	//!< This bit enables the interrupt at the end of conversion by a regular channel
#define CR1_JEOCIE														7	//!< This bit enables the interrupt at the end of conversion by a injected channel
#define CR1_SCAN														8	//!< This bit is set in order to select the multiple channels
#define CR1_JAUTO														10	//!< This bit is set to enable the conversion of injected group of channels after conversion by regular group of channels 
#define CR2_ADON														0	//!< This bit is set to Power on the adc peripheral
#define CR2_SWSTART														30	//!< This bit is set to make the regular channel to start the conversion 
#define CR2_JSWSTART													22	//!< This bit is set to make the injected channel to start the conversion
#define CR2_CONT														1	//!< This bit is set in order to select the continuously conversions
#define CR2_EOCS														10	//!< This bit flag is raised at the end of conversion 
#define CR2_ALIGN														11	//!< This bit is set in order to select the method of storing the data in data regeister
#define CR2_DMA														    8	//!< This bit is set to enable the dma functionality after the conversion by the channels
#define CR2_DDS															9	//!< This bit enable or disable the request of dma after convers
#define SR_STRT															4	//!< This bit is raised when a regular channel starts conversion
#define SR_JSTRT														3	//!< This bit is raised when an injected channel starts conversion
#define SR_EOC															1	//!< This bit falg is raised when a regular channel ends the conversion
#define SR_JEOC															2	//!< This bit flag is raised when an injected channel ends the conversion

/**********************************************MASK_MACROS**************************************************/
#define RESOLUTION_MASK													3	//!< This Mask will be used to clear the bits of resolution befor set it with the desired option
#define RESOLUTION_BITS													24	//!< This Mask will be used to shift the desired resolution with the value of this mask

#define PRESCALER_MASK													3	//!< This Mask will be used to clear the bits of Prescaler befor set it with the desired option
#define PRESCALER_BITS													16	//!< This Mask will be used to shift the desired prescaler with the value of this mask

#define SAMPLE_MASK														7	//!< This Mask will be used to clear the bits of Sampling time befor set it with the desired option
#define SAMPLE_BITS														3	//!< This Mask will be used to shift the desired Sampling time with the value of this mask

#define LENGTH_MASK														15	//!< This Mask will be used to clear the bits of Length befor set it with the desired Length
#define LENGTH_BITS														20	//!< This Mask will be used to shift the desired Length with the value of this mask

#define SEQUENCE_MASK													31	//!< This Mask will be used to clear the bits of Desired Section of channel befor set it with the desired Channel
#define SEQUENCE_BITS													5	//!< This Mask will be used to shift the desired Channel with the value of this mask

#endif /* MADC_PRIVATE_H_ */
