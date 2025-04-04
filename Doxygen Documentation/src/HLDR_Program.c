/**
 * @file	HLDR_Program.c
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The Light Dependent Resistor C file that has the functions body which is responsible for reading the light intensity based on the reading of the adc
 */
 
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/ADC/MADC_Interface.h"
#include "../include/HAL/LDR/HLDR_Interface.h"
#include "../include/HAL/LDR/HLDR_Config.h"
#include "../include/HAL/LDR/HLDR_Private.h"

/**
 * @fn 		void HLDR_voidInit(void)
 * @brief   This function is responsible for initializing and enabling the analog to digital converter from MCAL layer
 * @param 	none
 * @return 	none
 */
void HLDR_voidInit(void)
{
	MADC_VoidInit();
	MADC_VoidEnable();
}

/**
 * @fn 		u32 HLDR_u32MeasureLightIntensity(void)
 * @brief   This function is responsible measure the change in the resistance of the sensor then we can make any calibration to convert this readings to light intensity readings 
 * @param 	none
 * @return 	the value which indicates to the change in the sensor's resistance
 * @details this function is responsible for all the process of measuring the light intensity step by step:
  * -# The sensor will read the physical value which is the light intensity 
  * -# The sensor is responsible for converting the physical value to an analog voltage
  * -# The analog voltage will be entered to the adc channel
  * -# The adc will convert the analog reading to digital reading 
  * -# Reading this digital value and convert it to analog value by multiplying it to the step of the adc
  * -# Concert the analog reading to the physical value again  and return it 
 */
u32 HLDR_u32MeasureLightIntensity(void)
{
	f32 ADC_u32Read=0;
	f32 AnalogValue=0;
//	MADC_VoidStartConversion();
	MADC_VoidStartChannelConversion(ADC_CHANNEL0);
	ADC_u32Read=(f32)MADC_u16ReadSynch();
	AnalogValue=(f32)((ADC_u32Read*3.3)/256UL);
	return	(	(AnalogValue * FIXED_RESISTANCE)	/	(INPUT_VOLTAGE - AnalogValue)	);
}










