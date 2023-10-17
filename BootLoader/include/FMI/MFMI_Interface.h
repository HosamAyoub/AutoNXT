/*
 * MFMI_Interface.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Hesham Yasser
 */

#ifndef MFMI_INTERFACE_H_
#define MFMI_INTERFACE_H_

/***********Sectors*************/
typedef enum{
	Sector0_16KB,
	Sector1_16KB,
	Sector2_16KB,
	Sector3_16KB,
	Sector4_64KB,
	Sector5_128KB,
}MFMI_Sector;

/*************APIs*************/

void MFMI_voidMassErase (void);

void MFMI_voidApplicationAreaErase (void);

void MFMI_voidSectorErase (MFMI_Sector A_FMI_Sector);

void MFMI_voidProgramMemory (u32 A_u32Address , u16 * p_u16Data , u32 A_u32DataSize);

#endif /* MFMI_INTERFACE_H_ */
