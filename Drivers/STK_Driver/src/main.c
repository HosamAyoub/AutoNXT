#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/STK/MSTK_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"

void main (void)
{
	MRCC_voidInit();
	MSTK_voidInit();
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN0 , GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA , GPIO_PIN0 , GPIO_PUSH_PULL , GPIO_LOW_SPEED);
	while (1)
	{
		MSTK_voidDelayms(1000);
		MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN0 , GPIO_SET);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN0 , GPIO_RESET);
	}
}

