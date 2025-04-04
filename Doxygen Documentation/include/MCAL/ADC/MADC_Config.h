/**
 * @file	MADC_Config.h
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The analog to digital converter header file that has all the Modes and Options of **ADC** driver
 */

#ifndef MADC_CONFIG_H_
#define MADC_CONFIG_H_


#define MADC_RESOLUTION													 	    ADC_8_BIT	//!< This macro will select the resolution

#define MADC_PRESCALER												  	     ADC_PRESCALER_4	//!< This macro will select the prescaler 

#define MADC_MODE											        	 ADC_SGL_CHANNEL_SGL_CONVERSION	//!< This macro will select the mode of adc

#define MDAC_DATA_ALIGNMENT												     ADC_RIGHT_ALIGNMENT	//!< This macro will select the method of allignment

#define MADC_EOCS_MODE													    AFTER_ALL_CONVERSIONS	//!< This macro will select when the flag of EOC will be raised

#define MADC_DMA_MODE																DISABLE	//!< This macro will enable or disable the dma mode 

#define MADC_DMA_SELECTION													ADC_DMA_SINGLE_COPY	//!< This macro will select the method of coping the data in memory by dma

#define MADC_EOC_INTERRUPT														     DISABLE	//!< This macro will enable or disable the interrupt after the conversion

#define MADC_REGULAR_CHANNELS_SEQUENCE_LENGTH									     	1	//!< This macro will set the number of used channels in the system

#define MADC_CH0_SAMPLE_TIME													ADC_SAMPLE_3_CYCLES	//!< This macro will set the sampling time of channel 0
#define MADC_CH1_SAMPLE_TIME													ADC_SAMPLE_3_CYCLES	//!< This macro will set the sampling time of channel 1 
#define MADC_CH2_SAMPLE_TIME													ADC_SAMPLE_3_CYCLES	//!< This macro will set the sampling time of channel 2
#define MADC_CH3_SAMPLE_TIME													ADC_SAMPLE_3_CYCLES	//!< This macro will set the sampling time of channel 3
#define MADC_CH4_SAMPLE_TIME													ADC_SAMPLE_3_CYCLES	//!< This macro will set the sampling time of channel 4
#define MADC_CH5_SAMPLE_TIME													ADC_SAMPLE_3_CYCLES	//!< This macro will set the sampling time of channel 5


#define ADC_REGULAR_SEQ_1 															ADC_CHANNEL0	//!< This macro will set the the channel that will convert first
#define ADC_REGULAR_SEQ_2  															ADC_CHANNEL1	//!< This macro will set the the channel that will convert second
#define ADC_REGULAR_SEQ_3  															ADC_CHANNEL1	//!< This macro will set the the channel that will convert third
#define ADC_REGULAR_SEQ_4  															ADC_CHANNEL1	//!< This macro will set the the channel that will convert fourth
#define ADC_REGULAR_SEQ_5  															ADC_CHANNEL1	//!< This macro will set the the channel that will convert fifth
#define ADC_REGULAR_SEQ_6  															ADC_CHANNEL1	//!< This macro will set the the channel that will convert sixth


#endif /* MADC_CONFIG_H_ */
