#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/NVIC/MNVIC_Interface.h"
#include "../include/EXTI/MEXTI_Interface.h"
#include "../include/STK/MSTK_Interface.h"
void Handler1 (void);
void Handler2 (void);


void main (void)
{
	MRCC_voidInit();
	MSTK_voidInit();

	MNVIC_voidSetInterruptGroupMode(Groups16_NoSub);
	MNVIC_voidSetInterruptPriority(6,0,0);
	MNVIC_voidSetInterruptPriority(7,1,0);

	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOB);
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_SYSCFG);
	MGPIO_voidSetPinMode(GPIO_PORTB , GPIO_PIN0 , GPIO_INPUT);
	MGPIO_voidSetPinInputMode(GPIO_PORTB , GPIO_PIN0 , GPIO_PULLUP);
	MGPIO_voidSetPinMode(GPIO_PORTB , GPIO_PIN1 , GPIO_INPUT);
	MGPIO_voidSetPinInputMode(GPIO_PORTB , GPIO_PIN1 , GPIO_PULLUP);

	MEXTI_voidInit();
	MEXTI_voidSetCallBack(MEXTI_LINE0 , Handler2);
	MEXTI_voidSetCallBack(MEXTI_LINE1 , Handler1);
	MNVIC_voidEnablePeripheralInterrupt(6);
	MNVIC_voidEnablePeripheralInterrupt(7);
	u8 local_u8Iterator = 0;

	for ( local_u8Iterator = 0 ; local_u8Iterator < 8 ; local_u8Iterator++)
	{
		MGPIO_voidSetPinMode(GPIO_PORTA , local_u8Iterator , GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTA , local_u8Iterator , GPIO_PUSH_PULL , GPIO_LOW_SPEED);
		MGPIO_voidSetResetPin(GPIO_PORTA , local_u8Iterator , GPIO_RESET);
	}

	MEXTI_voidEnableEXTILine(MEXTI_LINE0);
	MEXTI_voidEnableEXTILine(MEXTI_LINE1);
	while (1)
	{

	}
}


void Handler1 (void)
{
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN1,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN2,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN3,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN4,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_PIN_LOW);
	while (1)
	{

		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN1,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN1,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN2,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN2,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN3,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN3,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN4,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN4,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_PIN_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_PIN_HIGH);
		MSTK_voidDelayms(1000);


	}
}
void Handler2 (void)
{
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN1,GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN2,GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN3,GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN4,GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN5,GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN6,GPIO_PIN_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_PIN_HIGH);
		MSTK_voidDelayms(3000);
}
