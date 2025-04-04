
/**
 * @file	main.c
 * @author 	Seif Eldeen Ashraf
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief 	The main application C file that has the functions body which is responsible for  the apllication
 */


#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
/*************************MCAL Includes*******************************/
#include "../include/MCAL/RCC/MRCC_Interface.h"
#include "../include/MCAL/GPIO/MGPIO_Interface.h"
#include "../include/MCAL/ADC/MADC_Interface.h"
#include "../include/MCAL/NVIC/MNVIC_Interface.h"
#include "../include/MCAL/EXTI/MEXTI_Interface.h"
#include "../include/MCAL/TIMER/MTIMER_Interface.h"
#include "../include/MCAL/UART/MUART_Interface.h"
#include "../include/MCAL/SPI/MSPI_Interface.h"

/*************************HAL Includes*******************************/
#include "../include/HAL/MOTOR/HMotor_Interface.h"
#include "../include/HAL/LDR/HLDR_Interface.h"
#include "../include/HAL/FSR/HFSR_Interface.h"
#include "../include/HAL/Ultrasonic/HUltrasonic_Interface.h"


/************************* OS Includes*******************************/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "queue.h"
#include "portmacro.h"






TaskHandle_t Move_Handle;                 //!< The Handle of The Movement  task
TaskHandle_t Ultrasonic_Handle;           //!< The Handle of The Ultrasonic Handle task
TaskHandle_t LDR_Handle;                  //!< The Handle of The LDR Handle task
TaskHandle_t Airbag_handle;               //!< The Handle of The Airbag Handle task
TaskHandle_t Accident_handle;             //!< The Handle of The Accident Handle task
xSemaphoreHandle Accident_Key;            //!< The Key is Responsible of activating the Accident Task

/**
 * @fn 		static void Movement_handler(void*)
 * @brief 	This Task responsible of Movement the car
 * @param 	parameters pointer to anything we need to pass to the created task
 * @return	none
 */
static void Movement_handler(void*parameters)
{
	s8 x=0;
	u32 speed=0;
	while(1)
	{
		x=0;
		MUART2_u8ReceiveWithoutBlocking(&x);
		switch(x)
		{
		case 'F':
			HMotor_VoidCarForword();
			break;
		case 'B':
			HMotor_VoidCarBackword();
			break;
		case 'R':
			HMotor_VoidCarRight();
			break;
		case 'L':
			HMotor_VoidCarLeft();
			break;
		case 'S':
			speed=speed+100;
			HMotor_VoidCarSpeed(speed);
			break;
		case 'H':
			speed=speed-100;
			HMotor_VoidCarSpeed(speed);
			break;
		case 'Y':
			break;
		default :
			HMotor_VoidCarStop();
			break;
		}

		vTaskDelay(1);
	}
}

/**
 * @fn 		static void Ultrasonic_handler(void*)
 * @brief 	This Task responsible of Adaptive Cruise Control feature of the car
 * @param 	parameters pointer to anything we need to pass to the created task
 * @return	none
 */
static void Ultrasonic_handler(void*parameters)
{
	static u32 speed=0;
	static s32 Distance = 0;
	while(1)
	{
		Distance = HUltrasonic_voidReadDistanceBlocking();
		if ((Distance*25) >= 1000 )
		{
			speed = 1000;
		}
		else if (Distance <= 6)
		{
			speed = 0;
		}
		else
		{
			speed = (Distance*25);
		}
		HMotor_VoidCarSpeed(speed);
		HMotor_VoidCarForword();
		vTaskDelay(1);
	}
}

/**
 * @fn 		static void LDR_Task(void*)
 * @brief 	This Task responsible of Adaptive Light Control feature of the car
 * @param 	parameters pointer to anything we need to pass to the created task
 * @return	none
 */
static void LDR_Task(void*parameters)
{
	u32 LDR_Read=0;
	while(1)
	{
		LDR_Read=HLDR_u32MeasureLightIntensity();
		if(LDR_Read>10000)
		{
			LDR_Read=10000;
		}
		else
		{

		}
		MTIMER_voidSetCCRValue(TIMER3,CHANNEL3,(LDR_Read/10));
		vTaskDelay(10);
	}
}

/**
 * @fn 		static void Airbag_Task(void*)
 * @brief 	This Task responsible of Airbag feature of the car
 * @param 	parameters pointer to anything we need to pass to the created task
 * @return	none
 */

static void Airbag_Task(void*parameters)
{
	u32 Airbag_Read=0;
	while(1)
	{
		MADC_VoidStartChannelConversion(ADC_CHANNEL1);
		Airbag_Read=HFSR_u32MeasureForce();
		if(Airbag_Read<40000)
		{
			xSemaphoreGive(Accident_Key);
		}
		else
		{

		}
		vTaskDelay(1);
	}
}

/**
 * @fn 		static void Accident_Task(void*)
 * @brief 	This Task responsible of notification to us that the Air Bag Feature is Activated
 * @param 	parameters pointer to anything we need to pass to the created task
 * @return	none
 */

static void Accident_Task(void*parameters)
{


	while(1)
	{
		xSemaphoreTake(Accident_Key,portMAX_DELAY);
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN8, GPIO_PIN_HIGH);
		vTaskSuspendAll();
	}

}

/**
 * @fn 		static void Airbag_Task(void*)
 * @brief 	This Task responsible of Lane keep Task of the car
 * @param 	parameters pointer to anything we need to pass to the created task
 * @return	none
 */
static void Lane_Keep_Task(void*parameters)
{
	u8 Lane_Keep_Data=0;
	while(1)
	{
		Lane_Keep_Data= MSPI2_u16ReadReceivedValue();
		if(Lane_Keep_Data=='L')
		{
			HMotor_VoidCarLeft();
		}
		else if(Lane_Keep_Data=='R')
		{
			HMotor_VoidCarRight();
		}
		else
		{
			HMotor_VoidCarForword();
		}
		vTaskDelay(50);
	}


}
/**
 * @fn 		void main (void)
 * @brief   This function is responsible of application
 * @param 	none
 * @return 	none
 * @details This function initialize the system clock:
 * -# Enabling the clock of the system and enable every Peripheral we use in the application
 * -# initializing the peripherals and the hardware components we used in the application
 * -# Enabling the related pins to the peripherals and initialize it
 * -# Creating the tasks and the semaphores we need in the application
 */



int main(void)
{

	BaseType_t status;
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(MRCC_AHB1, MRCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(MRCC_AHB1, MRCC_AHB1_GPIOB);
	MRCC_voidEnablePeripheral(MRCC_APB2, MRCC_APB2_USART1);
	MRCC_voidEnablePeripheral(MRCC_APB1, MRCC_APB1_USART2);
	MRCC_voidEnablePeripheral(MRCC_APB1, MRCC_APB1_TIM4);
	MRCC_voidEnablePeripheral(MRCC_APB1, MRCC_APB1_TIM3);
	MRCC_voidEnablePeripheral(MRCC_APB1, MRCC_APB1_TIM2);
	MRCC_voidEnablePeripheral(MRCC_APB2, MRCC_APB2_ADC1);
	MRCC_voidEnablePeripheral(MRCC_APB1, MRCC_APB1_SPI2);

	/******************ADC**********************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_ANALOG);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_ANALOG);

	/******************HC-05 pins*****************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN2, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA, GPIO_PIN2, GPIO_AF7);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN3, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA, GPIO_PIN3, GPIO_AF7);
	/***************Ultrasonic Trig***************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN4, GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA, GPIO_PIN4, GPIO_PUSH_PULL,GPIO_MID_SPEED );
	MGPIO_voidSetResetPin(GPIO_PORTA, GPIO_PIN4, GPIO_RESET);

	/*****************Ultrasonic echo*************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN5, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA, GPIO_PIN5, GPIO_AF1);

	/*******************Motor Init pins*********************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN6, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA, GPIO_PIN6, GPIO_AF2);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN7, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA, GPIO_PIN7, GPIO_AF2);
	/*********************** FSR LED ***************************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN8, GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA, GPIO_PIN8, GPIO_PUSH_PULL,GPIO_MID_SPEED );
	/****************Uart1******************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN9, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA, GPIO_PIN9, GPIO_AF7);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN10, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTA, GPIO_PIN10, GPIO_AF7);

	/*********Light control led**************/
	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN0, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTB, GPIO_PIN0, GPIO_AF2);
	MTIMER_voidSetPWMOption(TIMER3, CHANNEL3, 1000, 0, 15);
	/*************SPI pins init****************/
	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN12, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTB, GPIO_PIN12, GPIO_AF5);
	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN13, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTB, GPIO_PIN13, GPIO_AF5);
	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN14, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTB, GPIO_PIN14, GPIO_AF5);
	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN15, GPIO_ALT_FUNC);
	MGPIO_voidSetPinAltrenativeFunction(GPIO_PORTB, GPIO_PIN15, GPIO_AF5);

	/***********Some inits**************/

	MUART1_voidInit();
	MUART1_voidEnable();
	MUART2_voidInit();
	MUART2_voidEnable();
	MSPI2_voidInit();
	HUltrasonic_voidInit();
	MADC_VoidInit();
	MADC_VoidEnable();
	HMotor_VoidCarInit();

	/******************Bluetooth**********************/
	status=xTaskCreate(Movement_handler,"RC Car",150,0,1,&Move_Handle);
	configASSERT(status==pdPASS);
	/*******************LDR Task***********************/
	status=xTaskCreate(LDR_Task,"LDR",150,0,1,&LDR_Handle);
	configASSERT(status==pdPASS);

	/*******************  Adaptive cruise control ***********************/
	status=xTaskCreate(Ultrasonic_handler,"Ultrasonic",150,0,3,&Ultrasonic_Handle);
	configASSERT(status==pdPASS);

	/***************** Air Bag***************************/
	status=xTaskCreate(Airbag_Task,"Airbag",150,0,4,&Airbag_handle);
	configASSERT(status==pdPASS);

	status=xTaskCreate(Accident_Task,"Accident",150,0,6,&Accident_handle);
	configASSERT(status==pdPASS);
	/*********** Create Accident Key************/
	Accident_Key=xSemaphoreCreateBinary();
	Normal_mode=xSemaphoreCreateBinary();


	vTaskStartScheduler();

	while(1)
	{

	}
}
