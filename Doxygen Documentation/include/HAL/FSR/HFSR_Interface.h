/**
 * @file	HFSR_Interface.h
 * @author 	Diaa Assem
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The Force Sensing Resistor Header file that has all the Prototypes of **FSR** driver
 */

#ifndef HFSR_INTERFACE_H_
#define HFSR_INTERFACE_H_

/**
 * @fn 		void HFSR_voidInit(void)
 * @brief   This function is responsible for initializing and enabling the analog to digital converter from MCAL layer
 * @param 	none
 * @return 	none
 */
void HFSR_voidInit(void);

/**
 * @fn 		u32 HFSR_u32MeasureForce(void);
 * @brief   This function is responsible measure the change in the resistance of the sensor then we can make any calibration to convert this readings to Force readings 
 * @param 	none
 * @return 	the value which indicates to the change in the sensor's resistance 
 */
u32 HFSR_u32MeasureForce(void);

#endif /* HFSR_INTERFACE_H_ */
