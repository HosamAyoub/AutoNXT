/**
 * @file HUltrasonic_Interface.h
 * @author	 Hesham Yasser
 * @version  1.0
 * @date 	 Nov 3, 2023
 * @brief  The HAL_Ultrasonic Header file that has all the prototypes and arguments of **Ultrasonic** driver
 *
 */

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

/**
 * @fn void HUltrasonic_voidInit(void)
 * @param 	none
 * @brief This Function initializes the Ultrasonic sensor with the provided configuration.
 * @return none.
 */
void HUltrasonic_voidInit (void);

/**
 * @fn void HUltrasonic_voidTrigger(void)
 * @param 	none
 * @brief This Function to Send trigger Signal on Trigger pin of ultrasonic sensor.
 * @return none.
 *
 */
void HUltrasonic_voidTrigger (void);

/**
 * @fn u16 HUltrasonic_u16ReadDistanceNonBlocking(void)
 * @param 	none
 * @brief This Function Reads the distance measured by the Ultrasonic sensor.
 *
 * @return u16  Distance measured by the sensor in centimeters.
 */
u16 HUltrasonic_u16ReadDistanceNonBlocking (void);
/**
 * @fn u16 HUltrasonic_voidReadDistanceBlocking(void)
 * @param 	none
 * @brief  Function to Trigger Signal on Trigger pin of ultrasonic sensor and capture the Rising and falling edges
 *
 * @return u16  Distance measured by the sensor in centimeters.
 */
u16 HUltrasonic_voidReadDistanceBlocking (void);


#endif /* ULTRASONIC_INTERFACE_H_ */
