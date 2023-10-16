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

#define SCB_VTOR       					(*(volatile u32*)0xE000ED08)

volatile u8 ReceiveBuffer[100];
volatile u8 u8RecCounter = 0;
volatile u8 TimeOutFlag = 0;
volatile u8 u8WriteReq = 1;
pf EntryPoint = NULL;


void APP_voidStartApplication (void)
{
	TimeOutFlag = 1;
	SCB_VTOR = 0x08004000;
	EntryPoint  = (*(pf *) 0x08004004);
	EntryPoint();
}

void main (void)
{
	u8 Local_u8RecStatus = 0;
	RCC_voidEnablePeripheral(RCC_APB2, RCC_APB2_USART1);
	RCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOA);
	RCC_voidInit();

	GPIO_voidSetMode(GPIO_PORTA, GPIO_PIN9, GPIO_ALTERNATE);
	GPIO_voidSetMode(GPIO_PORTA, GPIO_PIN10, GPIO_ALTERNATE);

	GPIO_voidSetAlternativeLine(GPIO_PORTA, GPIO_PIN9, GPIO_AF7_USART_1_2);
	GPIO_voidSetAlternativeLine(GPIO_PORTA, GPIO_PIN10, GPIO_AF7_USART_1_2);

	GPIO_voidSetMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
	GPIO_voidOutputPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PUSHPULL, GPIO_MEDIUM_SPEED);
	GPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);

	UART_voidInit();
	UART_voidEnable();
	STK_voidInit();
	STK_voidSetSingleIntervalMS(5000, &APP_voidStartApplication);
	while (!TimeOutFlag)
	{
		Local_u8RecStatus = UART_u8ReceiveWithoutBlocking(&ReceiveBuffer[u8RecCounter]) ;

		if(Local_u8RecStatus == 1)
		{
			/*Stop Timer Because Application Code In Processing*/
			STK_voidStop(); //Stop Timer

			/*indicate The end Of the Record*/
			if(ReceiveBuffer[u8RecCounter] == '\n')
			{
				if(u8WriteReq == 1)
				{
					/*Erase The Application Code*/
					FMI_voidEraseAppArea();
					u8WriteReq = 0 ;
				}
				/*Parse The Record and Write it to flash*/
				HexParser_voidParseRecord(ReceiveBuffer);
				/*Send ok to tool to send the next Record */
				UART_voidTransmit("k", 1);
				/*Reset Buffer Counter*/
				u8RecCounter = 0;
			}
			else
			{
				u8RecCounter++ ;
			}

			/*End Of File*/
			if(ReceiveBuffer[8] == '1' && ReceiveBuffer[9] == 'F' && ReceiveBuffer[10] == 'F')
			{
				/*Wait 1 sec then jump to Application*/
				STK_voidSetSingleIntervalMS(1000, &APP_voidStartApplication) ;
				/*Indicate to Successful Flashing*/
				GPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW) ;
			}

		}
		else
		{
			// Do Nothing
		}
	}
}
