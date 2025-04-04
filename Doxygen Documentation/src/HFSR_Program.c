/**
 * @file	HFSR_Program.c
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The Light Dependent Resistor C file that has the functions body which is responsible for reading the force based on the reading of the adc
 */


#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/ADC/MADC_Interface.h"
#include "../include/HAL/FSR/HFSR_Interface.h"
#include "../include/HAL/FSR/HFSR_Config.h"
#include "../include/HAL/FSR/HFSR_Private.h"

/**
 * @fn 		void HFSR_voidInit(void)
 * @brief   This function is responsible for initializing and enabling the analog to digital converter from MCAL layer
 * @param 	none
 * @return 	none
 */
void HFSR_voidInit(void)
{
	MADC_VoidInit();
	MADC_VoidEnable();
}

/**
 * @fn 		u32 HFSR_u32MeasureForce(void)
 * @brief   This function is responsible for measuring the change in the resistance of the sensor then we can make any calibration to convert this readings to force readings 
 * @param 	none
 * @return 	the value which indicates to the change in the sensor's resistance
 * @details this function is responsible for all the process of measuring the Force step by step:
  * -# The sensor will read the physical value which is the Force 
  * -# The sensor is responsible for converting the physical value to an analog voltage
  * -# The analog voltage will be entered to the adc channel
  * -# The adc will convert the analog reading to digital reading 
  * -# Reading this digital value and convert it to analog value by multiplying it to the step of the adc
  * -# Convert the analog reading to the physical value again  and return it 
 */
u32 HFSR_u32MeasureForce(void)
{
	f32 ADC_u32Read=0;
	MADC_VoidStartConversion();
	ADC_u32Read=MADC_u16ReadSynch();
	f32 AnalogValue=(f32)((ADC_u32Read*3.3)/256UL);

	return	(	(AnalogValue * FIXED_RESISTANCE)	/	(INPUT_VOLTAGE - AnalogValue)	);
}













