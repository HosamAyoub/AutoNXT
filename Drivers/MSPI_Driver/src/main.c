#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/SPI/MSPI_Interface.h"
#include "../include/STK/MSTK_Interface.h"

void main (void)
{
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOB);
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_SPI1);
	MSPI_voidInit();
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN0 , GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA , GPIO_PIN0 , GPIO_PUSH_PULL , GPIO_MID_SPEED);
	MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN0 , GPIO_RESET);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN5 , GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA , GPIO_PIN5 , GPIO_AF5);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN6 , GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA , GPIO_PIN6 , GPIO_AF5);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN7 , GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA , GPIO_PIN7 , GPIO_AF5);

	u8 local_u8Iterator = 0;

	while (1)
	{
		for (local_u8Iterator = 0 ; local_u8Iterator < 16 ; local_u8Iterator++)
		{
			MSPI_voidSendReceiveData(local_u8Iterator);
			MSTK_voidDelayms(200);
		}

	}
}

