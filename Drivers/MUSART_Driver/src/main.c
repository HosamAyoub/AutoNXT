#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/USART/MUSART_Interface.h"
#include "../include/STK/MSTK_Interface.h"

void main (void)
{
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOB);
	MRCC_voidEnablePeripheral(RCC_APB1 , RCC_APB1_USART2);
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_USART1);
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_USART6);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN0 , GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA , GPIO_PIN0 , GPIO_PUSH_PULL , GPIO_LOW_SPEED);
	MUSART_voidInit();

	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN9 , GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA , GPIO_PIN9 , GPIO_AF7);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN10 , GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA , GPIO_PIN10 , GPIO_AF7);
//	MGPIO_voidSetPinMode(GPIO_PORTB , GPIO_PIN6 , GPIO_ALT_FUNC);
//	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTB , GPIO_PIN6 , GPIO_AF7);
//	MGPIO_voidSetPinMode(GPIO_PORTB , GPIO_PIN7 , GPIO_ALT_FUNC);
//	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTB , GPIO_PIN7 , GPIO_AF7);

	MUSART_EnableUSART(MUSART_USART1);
	MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN0 , GPIO_SET);


	u16 local_u8Value = 0;
	u16 local_u8ValueAS = '0';
	while (1)
	{
//		MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN0 , GPIO_SET);
//		for (local_u8Value = 0 ; local_u8Value < 10 ; local_u8Value++)
//		{
//			MUSART_voidTransmit(MUSART_USART1 , &(local_u8ValueAS) , 1);
//			MSTK_voidDelayms(100);
//			local_u8ValueAS++;
//		}
		MUSART_voidReceive(MUSART_USART1, &local_u8Value);
		MUSART_voidTransmit(MUSART_USART1 , &local_u8Value , 1);

	}

}

