#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/DMA/MDMA_Interface.h"
#include "../include/NVIC/MNVIC_Interface.h"

void DMA_Handler (void);

void main (void)
{
	u32 Arr1[1000] = {0};
	u32 Arr2[1000] ;
	u32 Arr3[1000] = {10,10,10,10};
	u32 Arr4[1000] ;
	u16 local_u16Iterator = 0;
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_DMA1);
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_DMA2);
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MDMA_voidInit();
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN0 , GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA , GPIO_PIN0 , GPIO_PUSH_PULL , GPIO_LOW_SPEED);
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN1 , GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA , GPIO_PIN1 , GPIO_PUSH_PULL , GPIO_LOW_SPEED);
	MNVIC_voidEnablePeripheralInterrupt(56);
	MDMA_voidSetStreamConfigurations(MDMA2 , MDMA_STREAM0 , MDMA_CHANNEL0 , Arr1 , Arr2 , MDMA_WORD , 1000);
	MDMA_voidSetCallBack(MDMA2 , MDMA_STREAM0 , DMA_Handler);
	MDMA_voidEnableStream(MDMA2 , MDMA_STREAM0);
	for (local_u16Iterator = 0 ; local_u16Iterator < 1000 ; local_u16Iterator++)
	{
		Arr4[local_u16Iterator] = Arr3[local_u16Iterator];
	}
	MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN1 , GPIO_SET);
	while (1)
	{

	}
}


void DMA_Handler (void)
{
	MGPIO_voidSetResetPin(GPIO_PORTA , GPIO_PIN0 , GPIO_SET);
}

