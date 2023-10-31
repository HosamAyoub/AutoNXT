/*******************************************************************************************/
/*******************************************************************************************/
/***********************            Author  : Hosam Ayoub            ***********************/
/***********************            Layer   : Service                ***********************/
/***********************            SWC     : HexParser              ***********************/
/***********************            Version : 1.0                    ***********************/
/***********************            Date    : 01 Oct 2023            ***********************/
/*******************************************************************************************/
/*******************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/FMI/FMI_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "Service/HexParser/HexParser_interface.h"
#include "Service/HexParser/HexParser_private.h"
#include "Service/HexParser/HexParser_config.h"

static u16 Global_u16DataBuffer[100];
static pf Global_pfNotificationFunction = NULL;
u32 Global_u32FlashBaseAddress, Global_u32StartAddress;

static u8 HexParser_u8AsciiToHex (u8 Copy_u8Ascii)
{
	u8 Local_u8Hex = 0;
	if (('0' <= Copy_u8Ascii) && (Copy_u8Ascii <= '9'))
	{
		Local_u8Hex = Copy_u8Ascii - '0';
	}
	else if (('A' <= Copy_u8Ascii) && (Copy_u8Ascii <= 'F'))
	{
		Local_u8Hex = Copy_u8Ascii - ('A' - 10);
	}
	return Local_u8Hex;
}

void HexParser_voidParseData (s8 *Pointer_s8Data)
{
	u8 Local_u8CC, Local_u8Digit0, Local_u8Digit1, Local_u8Digit2, Local_u8Digit3, Local_u8Iterator, Local_u8CheckSum = 0, Local_u8Summation = 0;
	u32 Local_u32Address;
	static u8 Local_u8Flag = 1;
	/* Convert character count */
	Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[1]);
	Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[2]);
	Local_u8CC = (Local_u8Digit0 << 4) | (Local_u8Digit1);

	/* Add the previous byte to the summation */
	Local_u8Summation += Local_u8CC;

	/* Convert address */
	Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[3]);
	Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[4]);
	Local_u8Digit2 = HexParser_u8AsciiToHex(Pointer_s8Data[5]);
	Local_u8Digit3 = HexParser_u8AsciiToHex(Pointer_s8Data[6]);
	Local_u32Address = (Global_u32FlashBaseAddress) | (Local_u8Digit0 << 12) | (Local_u8Digit1 << 8) | (Local_u8Digit2 << 4) | (Local_u8Digit3);
	if (Local_u8Flag)
	{
		Global_u32StartAddress = Local_u32Address;
		Local_u8Flag = 0;
	}

	/* Add the previous two bytes to the summation */
	Local_u8Summation += (Local_u8Digit0 << 4) | (Local_u8Digit1);
	Local_u8Summation += (Local_u8Digit2 << 4) | (Local_u8Digit3);

	for (Local_u8Iterator = 0; Local_u8Iterator < (Local_u8CC/2); Local_u8Iterator++)
	{
		Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[9  + (Local_u8Iterator * 4)]);
		Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[10 + (Local_u8Iterator * 4)]);
		Local_u8Digit2 = HexParser_u8AsciiToHex(Pointer_s8Data[11 + (Local_u8Iterator * 4)]);
		Local_u8Digit3 = HexParser_u8AsciiToHex(Pointer_s8Data[12 + (Local_u8Iterator * 4)]);

		/* Convert big endian to little endian */
		Global_u16DataBuffer[Local_u8Iterator] = (Local_u8Digit2 << 12) | (Local_u8Digit3 << 8) | (Local_u8Digit0 << 4) | (Local_u8Digit1);

		/* Add the previous two bytes to the summation */
		Local_u8Summation += (Local_u8Digit0 << 4) | (Local_u8Digit1);
		Local_u8Summation += (Local_u8Digit2 << 4) | (Local_u8Digit3);
	}

	if (Local_u8CC % 2 == 1)
	{
		/* Add the padding half word to the CC */
		Local_u8CC++;

		Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[9  + (Local_u8Iterator * 4)]);
		Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[10 + (Local_u8Iterator * 4)]);
		Local_u8Digit2 = HexParser_u8AsciiToHex('0');
		Local_u8Digit3 = HexParser_u8AsciiToHex('0');

		/* Convert big endian to little endian */
		Global_u16DataBuffer[Local_u8Iterator] = (Local_u8Digit2 << 12) | (Local_u8Digit3 << 8) | (Local_u8Digit0 << 4) | (Local_u8Digit1);
		/* Add the previous two bytes to the summation */
		Local_u8Summation += (Local_u8Digit0 << 4) | (Local_u8Digit1);

		/* Get Checksum */
		Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[11  + (Local_u8Iterator * 4)]);
		Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[12  + (Local_u8Iterator * 4)]);

	}
	else
	{
		/* Get Checksum */
		Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[9  + (Local_u8Iterator * 4)]);
		Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[10 + (Local_u8Iterator * 4)]);
	}

	/* Calculate Checksum  */
	Local_u8CheckSum = (Local_u8Digit0 << 4) | (Local_u8Digit1);

	/* Get the Two's complement of the Summation */
	Local_u8Summation = (0xFF - Local_u8Summation) + 1;

	/* Check if the record is correct or no*/
	if (Local_u8Summation == Local_u8CheckSum)
	{
		FMI_voidFlashWrite(Local_u32Address, Global_u16DataBuffer, (Local_u8CC/2));
	}
	else
	{
		asm("nop");
		/* Do Nothing */
	}
}

void HexParser_voidSetHighAddress (s8 *Pointer_s8Data)
{
	u8 Local_u8CC, Local_u8Digit0, Local_u8Digit1, Local_u8Digit2, Local_u8Digit3, Local_u8CheckSum = 0, Local_u8Summation = 0;
	/* Convert character count */
	Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[1]);
	Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[2]);
	/* Add the previous byte to the summation */
	Local_u8Summation += (Local_u8Digit0 << 4) | (Local_u8Digit1);

	/* Convert address */
	Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[3]);
	Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[4]);
	Local_u8Digit2 = HexParser_u8AsciiToHex(Pointer_s8Data[5]);
	Local_u8Digit3 = HexParser_u8AsciiToHex(Pointer_s8Data[6]);
	Global_u32FlashBaseAddress = (Local_u8Digit0 << 12) | (Local_u8Digit1 << 8) | (Local_u8Digit2 << 4) | (Local_u8Digit3);
	/* Add the previous two bytes to the summation */
	Local_u8Summation += (Local_u8Digit0 << 4) | (Local_u8Digit1);
	Local_u8Summation += (Local_u8Digit2 << 4) | (Local_u8Digit3);

	/* Add 0x04 to the summation as it is the code to set High address */
	Local_u8Summation += 0x04;

	Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[9 ]);
	Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[10]);
	Local_u8Digit2 = HexParser_u8AsciiToHex(Pointer_s8Data[11]);
	Local_u8Digit3 = HexParser_u8AsciiToHex(Pointer_s8Data[12]);
	Global_u32FlashBaseAddress |= (Local_u8Digit0 << 28) | (Local_u8Digit1 << 24) | (Local_u8Digit2 << 20) | (Local_u8Digit3 << 16);

	/* Add the previous two bytes to the summation */
	Local_u8Summation += (Local_u8Digit0 << 4) | (Local_u8Digit1);
	Local_u8Summation += (Local_u8Digit2 << 4) | (Local_u8Digit3);
	/* Get the Two's complement of the Summation */
	Local_u8Summation = (0xFF - Local_u8Summation) + 1;

	/* Calculate Checksum */
	Local_u8Digit0 = HexParser_u8AsciiToHex(Pointer_s8Data[13]);
	Local_u8Digit1 = HexParser_u8AsciiToHex(Pointer_s8Data[14]);
	Local_u8CheckSum = (Local_u8Digit0 << 4) | (Local_u8Digit1);

	/* Check if the record is correct or no*/
	if (Local_u8Summation == Local_u8CheckSum)
	{
		asm("nop");
	}
	else
	{
		/* Do Nothing */
		asm("nop");
	}
}

void HexParser_voidParseRecord (s8 *Pointer_s8Data)
{
	switch (Pointer_s8Data[8])
	{
	case '0':
		HexParser_voidParseData(Pointer_s8Data);
		break;
	case '4':
		/* Set high address */
		HexParser_voidSetHighAddress(Pointer_s8Data);
		break;
	case '1':
		/* End of file */
		if (Pointer_s8Data[11] == '\n')
		{
			/*Send ok to tool to send the next Record */
			UART_voidTransmit("k");
			Global_pfNotificationFunction();
		}
		else
		{
			/*Send ok to tool to send the next Record */
			HexParser_voidParseData(Pointer_s8Data);
		}
		break;
	case '5':
		/* Set high address */
		UART_voidTransmit("k");
		break;
	default:
		break;
	}
}

void HexParser_voidSetCallBack(pf PointerToFunction)
{
	if (PointerToFunction != NULL)
	{
		Global_pfNotificationFunction = PointerToFunction;
	}
	else
	{
		/* Do Nothing */
	}
}
