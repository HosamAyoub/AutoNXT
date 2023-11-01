#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"


void main (void)
{
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOB);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN0 , GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA , GPIO_PIN0 , GPIO_PUSH_PULL , GPIO_LOW_SPEED);
	MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN0 , GPIO_SET);
	while (1)
	{

	}
}

