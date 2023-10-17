#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/USART/MUSART_Interface.h"
#include "../include/STK/MSTK_Interface.h"
#include "../include/FMI/MFMI_Interface.h"
#include "../include/HexParser/HexParser_Interface.h"
u8 ReceivedLine[100];
u8 global_EndFlag = 0;

#define SCB_VTOR			(*(volatile u32 *) 0xE000ED08)

PtrToFunc_void StartApp = NULL;
void main (void)
{
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_USART1);
	MRCC_voidEnablePeripheral(RCC_APB1 , RCC_APB1_USART2);
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_USART6);
	MUSART_voidInit();
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN9 , GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA , GPIO_PIN9 , GPIO_AF7);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN10 , GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA , GPIO_PIN10 , GPIO_AF7);
	MUSART_EnableUSART(MUSART_USART1);
	u8 local_u8WriteFlag = 0;
	u8 local_u8StartFlag = 0;
	u8 local_u8Counter = 0;
	if (local_u8StartFlag == 0)
	{
		MUSART_voidTransmit(MUSART_USART1 ,(u16*) "Q" , 1);
		MUSART_voidReceive(MUSART_USART1, (u16 *)&local_u8WriteFlag);
	}
	while (1)
	{
		if (local_u8WriteFlag == 'R')
		{
			if (local_u8StartFlag == 0)
			{
				MFMI_voidApplicationAreaErase();
				local_u8StartFlag = 1;
			}

			if (global_EndFlag != 1)
			{
				MUSART_voidTransmit(MUSART_USART1 ,(u16*) "K" , 1);
				MUSART_voidReceive(MUSART_USART1, (u16 *)&(ReceivedLine[local_u8Counter]));
			}
			else
			{
				MUSART_voidTransmit(MUSART_USART1 ,(u16*) "N" , 1);
				SCB_VTOR = 0x08004000;
				StartApp = (*(PtrToFunc_void * )0x08004004);
				StartApp();
			}
			while (ReceivedLine[local_u8Counter] != '\n')
			{
				local_u8Counter ++;
				MUSART_voidReceive(MUSART_USART1, (u16 *)&(ReceivedLine[local_u8Counter]));
			}
			if (ReceivedLine[local_u8Counter] == '\n')
			{
				local_u8Counter = 0;
				HexParser_voidParseData(ReceivedLine);
			}
		}
		else
		{
			SCB_VTOR = 0x08004000;
			StartApp = (*(PtrToFunc_void * )0x08004004);
			StartApp();
		}
	}
}

