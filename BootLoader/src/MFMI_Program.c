/*
 * MFMI_Program.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Hesham Yasser
 */



#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/FMI/MFMI_Interface.h"
#include "../include/FMI/MFMI_private.h"
#include "../include/FMI/MFMI_Configurations.h"

void MFMI_voidMassErase (void)
{
	while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
	if (FMI->CR.LOCK == LOCKED)
	{
		FMI->KEYR = KEY1;
		FMI->KEYR = KEY2;
	}
	FMI->CR.PSIZE = HALF_WORD;
	FMI->CR.MER = ENABLED;
	FMI->CR.STRT = ENABLED;
	while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
	SET_BIT(FMI->SR , SR_EOP);
	FMI->CR.MER = DISABLED;
}

void MFMI_voidApplicationAreaErase (void)
{
	while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
	MFMI_Sector local_Sector_Iterator = Sector1_16KB;
	if (FMI->CR.LOCK == 1)
	{
		FMI->KEYR = KEY1;
		FMI->KEYR = KEY2;
	}
	FMI->CR.PSIZE = HALF_WORD;
	for (local_Sector_Iterator = Sector1_16KB ; local_Sector_Iterator <= Sector5_128KB ; local_Sector_Iterator++)
	{
		FMI->CR.SNB = local_Sector_Iterator;
		FMI->CR.SER = ENABLED;
		FMI->CR.STRT = ENABLED;
		while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
		SET_BIT(FMI->SR , SR_EOP);
		FMI->CR.SER = DISABLED;
	}
}
void MFMI_voidSectorErase (MFMI_Sector A_FMI_Sector)
{
	while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
	if (FMI->CR.LOCK == 1)
	{
		FMI->KEYR = KEY1;
		FMI->KEYR = KEY2;
	}
	FMI->CR.PSIZE = HALF_WORD;
	FMI->CR.SNB = A_FMI_Sector;
	FMI->CR.SER = ENABLED;
	FMI->CR.STRT = ENABLED;
	while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
	SET_BIT(FMI->SR , SR_EOP);
	FMI->CR.SER = DISABLED;
}

void MFMI_voidProgramMemory (u32 A_u32Address , u16 * p_u16Data , u32 A_u32DataSize)
{
	while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
	u32 local_u32Iterator ;
	if (FMI->CR.LOCK == 1)
	{
		FMI->KEYR = KEY1;
		FMI->KEYR = KEY2;
	}
	FMI->CR.PSIZE = HALF_WORD;
	for (local_u32Iterator = 0 ; local_u32Iterator < A_u32DataSize ; local_u32Iterator++)
	{
		FMI->CR.PG = ENABLED;
		* (volatile u16 *)A_u32Address = p_u16Data[local_u32Iterator];
		while (GET_BIT(FMI->SR , SR_BSY) == BUSY);
		SET_BIT(FMI->SR , SR_EOP);
		A_u32Address += 2;
		FMI->CR.PG = DISABLED;
	}
}
