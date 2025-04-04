/**
 * @file HUltrasonic_Program.c
 * @author	 Hesham Yasser
 * @version  1.0
 * @date 	 Nov 3, 2023
 * @brief  The HAL_Ultrasonic C file that has the functions body of **MTIMER** driver.
 *
 */



#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/GPIO/MGPIO_Interface.h"
#include "../include/MCAL/TIMER/MTIMER_Interface.h"
#include "../include/HAL/Ultrasonic/HUltrasonic_Interface.h""
#include "../include/HAL/Ultrasonic/HUltrasonic_Private.h""
#include "../include/HAL/Ultrasonic/HUltrasonic_Config.h"


u16 global_u16Distance = 0;

/**
 * @fn void HUltrasonic_voidInit(void)
 * @param 	none
 * @brief This Function initializes the Ultrasonic sensor with the provided configuration.
 * @return none.
 * @details -#This function initializes the Ultrasonic sensor with the provided configuration:
 * 				- SET Prescaler value of Ultrasonic Timer to 15
 * 				- SET Timer Count Direction to UPCOUNT.
 * 				- SET Channel Clock Polarity trigger to Rising egde.
 * 				- SET This Channel Interrupt.
 * 				- SET another Channel Direction as input.
 * 				- SET This channel interrupt.
 * 				- CallBack Function With Ultrasonic CallBack Function.
 * 				- SET Max value of counts to 0xffff.
 * 				- Enable Timer.
 *
 *
 *
 */

void HUltrasonic_voidInit (void)
{
	MTIMER_voidSetPrescaler(ULTRA_SONIC_TIMER, 15);
	MTIMER_voidSetTimerCountDirection(ULTRA_SONIC_TIMER, UPCOUNT);
	MTIMER_voidSetChannelDirection(ULTRA_SONIC_TIMER, CHANNEL1, CHANNELx_INPUT_TIx);
	MTIMER_voidSetChannelInputPolarity(ULTRA_SONIC_TIMER, CHANNEL1, RISING_EDGE);
	MTIMER_EnableChannelInterrupt(ULTRA_SONIC_TIMER, CHANNEL1);
	MTIMER_voidSetChannelDirection(ULTRA_SONIC_TIMER, CHANNEL2, CHANNELx_INPUT_TIy);
	MTIMER_voidSetChannelInputPolarity(ULTRA_SONIC_TIMER, CHANNEL2, FALLING_EDGE);
	MTIMER_EnableChannelInterrupt(ULTRA_SONIC_TIMER, CHANNEL2);
	MTIMER_voidSetCallBack(ULTRA_SONIC_TIMER, HUltrasonic_voidCallBack);
	MTIMER_voidSetARRValue(ULTRA_SONIC_TIMER, 0xffff);
	MTIMER_voidEnableTimer(ULTRA_SONIC_TIMER);
}

/**
 * @fn void HUltrasonic_voidTrigger(void)
 * @param 	none
 * @brief This Function to Send trigger Signal on Trigger pin of ultrasonic sensor.
 * @return none.
 * @details This Function used to trigger signal on Trigger Pin through SET Trigger Pin For about 10 seconds then Reset it.
 *
 */
void HUltrasonic_voidTrigger (void)
{
	MGPIO_voidSetResetPin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_SET);
	for (u32 Delay = 0 ; Delay < 100 ; Delay++)
	{
		asm("NOP");
	}
	MGPIO_voidSetResetPin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_RESET);
}


/**
 * @fn u16 HUltrasonic_u16ReadDistanceNonBlocking(void)
 * @param 	none
 * @brief This Function Reads the distance measured by the Ultrasonic sensor.
 *
 * @return u16  Distance measured by the sensor in centimeters.
 * @details This Function return Distance value through Global Variable.
 */

u16 HUltrasonic_u16ReadDistanceNonBlocking (void)
{
	return global_u16Distance;
}

/**
 * @fn u16 HUltrasonic_u16ReadDistanceNonBlocking(void)
 * @param 	none
 * @brief This Function Reads the distance measured by the Ultrasonic sensor.
 *
 * @return u16  Distance measured by the sensor in centimeters.
 * @details This Function return Distance value through Global Variable.
 */
/**
 * @fn void HUltrasonic_voidCallBack(void)
 * @param 	none
 * @brief This Function Capture value from the specified channel (ECHO-pin) and calculate distance.
 * @details This Function read interrupt state for first channel and if its value 1 => Read captured value from MTIM Peripheral using CCR register and clear the counter,
 * Then read interrupt state for second channel and if its value 1 => Read captured value from MTIM Peripheral using CCR register and calculate distance.
 *
 *
 */
static void HUltrasonic_voidCallBack (void)
{
	u32 local_u32Value = 0;
	if (MTIMER_u8ReadInterruptState(ULTRA_SONIC_TIMER, CHANNEL1) == 1)
	{
		MTIMER_u32ReadChannelValue(ULTRA_SONIC_TIMER, CHANNEL1);
		MTIMER_voidSetCounterValue(ULTRA_SONIC_TIMER, 0);
	}
	else if (MTIMER_u8ReadInterruptState(ULTRA_SONIC_TIMER, CHANNEL2) == 1)
	{
		local_u32Value = MTIMER_u32ReadChannelValue(ULTRA_SONIC_TIMER, CHANNEL2);
		global_u16Distance = local_u32Value/58;
	}
}

/**
 * @fn u16 HUltrasonic_voidReadDistanceBlocking(void)
 * @param 	none
 * @brief  Function to Trigger Signal on Trigger pin of ultrasonic sensor and capture the Rising and falling edges
 *
 * @return u16  Distance measured by the sensor in centimeters.
 * @details This Function used to trigger signal on Trigger Pin through SET Trigger Pin For about 10 seconds then Reset it the wait for rising edge,Read captured value in First channel
 *  Reset value of counter and waiting to falling edge then read captured value in channel2 and calculate distance.
 */

u16 HUltrasonic_voidReadDistanceBlocking (void)
{
	/*Send Trigger signal*/
	u32 local_u32Value = 0;
	MGPIO_voidSetResetPin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_SET);
	for (u32 Delay = 0 ; Delay < 100 ; Delay++)
	{
		asm("NOP");
	}
	MGPIO_voidSetResetPin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_RESET);
	/*Wait for rising edge*/
	while(MTIMER_u8ReadInterruptState(ULTRA_SONIC_TIMER, CHANNEL1) == 0);
	MTIMER_u32ReadChannelValue(ULTRA_SONIC_TIMER, CHANNEL1);
	MTIMER_voidSetCounterValue(ULTRA_SONIC_TIMER, 0);
	/*Wait for falling edge*/
	while(MTIMER_u8ReadInterruptState(ULTRA_SONIC_TIMER, CHANNEL2) == 0);
	local_u32Value = MTIMER_u32ReadChannelValue(ULTRA_SONIC_TIMER, CHANNEL2);
	global_u16Distance = local_u32Value/58;
	return global_u16Distance;
}

