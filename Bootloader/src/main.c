/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Hosam Ayoub			*********************************/
/********************			Layer: APP					*********************************/
/********************			Version: 1.00				*********************************/
/********************			Date: 1 Oct 2023			*********************************/
/********************************************************************************************/
/********************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/STK/STK_interface.h"
#include "MCAL/FMI/FMI_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "Service/HexParser/HexParser_interface.h"

#define TX_PIN							GPIO_PIN9
#define RX_PIN							GPIO_PIN10

#define SCB_VTOR       					(*(volatile u32*)0xE000ED08)

s8 ReceiveBuffer[100];
volatile u8 u8RecCounter = 0;
volatile u8 TimeOutFlag = 0;
volatile u8 u8WriteReq = 1;
pf EntryPoint = NULL;


void APP_voidStartApplication (void)
{
	TimeOutFlag = 1;
	SCB_VTOR = Global_u32StartAddress;
	EntryPoint  = (*(pf *) (Global_u32StartAddress | 0x4));
	GPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
	EntryPoint();
}


void main (void)
{
	u8 Local_u8RecStatus = 0;
	RCC_voidEnablePeripheral(RCC_APB2, RCC_APB2_USART1);
	RCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOA);
	RCC_voidInit();

	GPIO_voidSetMode(GPIO_PORTA, TX_PIN, GPIO_ALTERNATE);
	GPIO_voidSetMode(GPIO_PORTA, RX_PIN, GPIO_ALTERNATE);

	GPIO_voidSetAlternativeLine(GPIO_PORTA, TX_PIN, GPIO_AF7_USART_1_2);
	GPIO_voidSetAlternativeLine(GPIO_PORTA, RX_PIN, GPIO_AF7_USART_1_2);

	GPIO_voidSetMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
	GPIO_voidOutputPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PUSHPULL, GPIO_MEDIUM_SPEED);
	GPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);

	UART_voidInit();
	UART_voidEnable();

	STK_voidInit();
	STK_voidSetSingleIntervalMS(5000, &APP_voidStartApplication);

	HexParser_voidSetCallBack(&APP_voidStartApplication);
	while (!TimeOutFlag)
	{
		Local_u8RecStatus = UART_u8ReceiveWithoutBlocking(&ReceiveBuffer[u8RecCounter]) ;

		if(Local_u8RecStatus == 1)
		{
			/*indicate The end Of the Record*/
			if(ReceiveBuffer[u8RecCounter] == '\n')
			{
				/*Parse The Record and Write it to flash*/
				HexParser_voidParseRecord(ReceiveBuffer);
				if(u8WriteReq == 1)
				{
					/* Stop Timer Because Application Code In Processing*/
					STK_voidStop();
//					/*Erase The Application Code*/
//					if (Global_u32FlashBaseAddress == 0x08000000)
//						FMI_voidEraseAppArea(FMI_BANK1);
//					else if (Global_u32FlashBaseAddress == 0x08020000)
//						FMI_voidEraseAppArea(FMI_BANK2);
					/* Clear Write request */
					u8WriteReq = 0 ;
				}
				/*Send ok to tool to send the next Record */
				UART_voidTransmit("k");
				/*Reset Buffer Counter*/
				u8RecCounter = 0;
			}
			else
			{
				u8RecCounter++ ;
			}

		}
		else
		{
			// Do Nothing
		}
	}
}
