/**
 * @file	HLDR_Interface.h
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The Light Dependent Resistor Header file that has all the Prototypes of **LDR** driver
 */

#ifndef HLDR_INTERFACE_H_
#define HLDR_INTERFACE_H_

/**
 * @fn 		void HLDR_voidInit(void)
 * @brief   This function is responsible for initializing and enabling the analog to digital converter from MCAL layer
 * @param 	none
 * @return 	none
 */
void HLDR_voidInit(void);

/**
 * @fn 		u32 HLDR_u32MeasureLightIntensity(void)
 * @brief   This function is responsible measure the change in the resistance of the sensor then we can make any calibration to convert this readings to light intensity readings 
 * @param 	none
 * @return 	the value which indicates to the change in the sensor's resistance 
 */
u32 HLDR_u32MeasureLightIntensity(void);



#endif /* HLDR_INTERFACE_H_ */
