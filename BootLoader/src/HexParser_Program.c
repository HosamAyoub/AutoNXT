/*
 * HexParser_Program.c
 *
 *  Created on: Oct 1, 2023
 *      Author: Hesham Yasser
 */

#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/FMI/MFMI_Interface.h"
#include "../include/HexParser/HexParser_Interface.h"
#include "../include/HexParser/HexParser_private.h"
#include "../include/HexParser/HexParser_Configurations.h"

u16 global_u16HighAddress = 0x0800;
u32 global_u32Address = 0;
u16 DataBuffer[20];
extern u8 global_EndFlag;

static u8 HexParser_u8Ascii2Hex (u8 A_Data)
{
	u8 local_u8Hex = 0;
	switch (A_Data)
	{
	case '0' ... '9':
	local_u8Hex = A_Data-'0';
	break;
	case 'A' ... 'F':
	local_u8Hex = A_Data-'A'+10;
	break;
	case 'a' ... 'f':
	local_u8Hex = A_Data-'a'+10;
	break;
	default:
		break;
	}
	return local_u8Hex;
}

void HexParser_voidParseData (u8 * p_Data)
{
	u8 Data_B0 = 0;
	u8 Data_B1 = 0;
	u16 Data = 0;
	u8 local_u8Iterator = 0;
	u8 local_u8Length = 0;
	/*Get Character Count*/
	u8 CC = (HexParser_u8Ascii2Hex(p_Data[1])<<4)|(HexParser_u8Ascii2Hex(p_Data[2]));
	/*Get First Byte of Low Address*/
	u8 LowAddress_B0 = (HexParser_u8Ascii2Hex(p_Data[5])<<4)|(HexParser_u8Ascii2Hex(p_Data[6]));
	/*Get Second Byte of Low Address*/
	u8 LowAddress_B1 = (HexParser_u8Ascii2Hex(p_Data[3])<<4)|(HexParser_u8Ascii2Hex(p_Data[4]));
	/*Oring the Two Bytes to get the total low address*/
	u16 Low_Address = (LowAddress_B1 << 8)|(LowAddress_B0);
	if (((HexParser_u8Ascii2Hex(p_Data[7])<<4)|(HexParser_u8Ascii2Hex(p_Data[8]))) == 0x04)
	{
		/*Get First Byte of High Address*/
		u8 HighAddress_B0 = (HexParser_u8Ascii2Hex(p_Data[11])<<4)|(HexParser_u8Ascii2Hex(p_Data[12]));
		/*Get Second Byte of High Address*/
		u8 HighAddress_B1 = (HexParser_u8Ascii2Hex(p_Data[9])<<4)|(HexParser_u8Ascii2Hex(p_Data[10]));
		global_u16HighAddress = (HighAddress_B1<<8 | HighAddress_B0);
	}
	else if (((HexParser_u8Ascii2Hex(p_Data[7])<<4)|(HexParser_u8Ascii2Hex(p_Data[8]))) == 0x01)
	{
		global_EndFlag = 1;
	}
	else if (((HexParser_u8Ascii2Hex(p_Data[7])<<4)|(HexParser_u8Ascii2Hex(p_Data[8]))) == 0x00)
	{
		global_u32Address = (global_u16HighAddress << 16 | Low_Address);
		for (local_u8Iterator = 0 ; local_u8Iterator < (CC/2) ; local_u8Iterator++)
		{
			Data_B0 = (HexParser_u8Ascii2Hex(p_Data[(local_u8Iterator*4)+9])<<4)|(HexParser_u8Ascii2Hex(p_Data[(local_u8Iterator*4)+10]));
			Data_B1 = (HexParser_u8Ascii2Hex(p_Data[(local_u8Iterator*4)+11])<<4)|(HexParser_u8Ascii2Hex(p_Data[(local_u8Iterator*4)+12]));
			Data = (Data_B1<<8)|(Data_B0);
			DataBuffer[local_u8Iterator] = Data;
		}

		MFMI_voidProgramMemory(global_u32Address , DataBuffer , (CC/2));
	}
}
