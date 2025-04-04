/**
 * @file     HUltrasonic_Private.h
 * @author	 Hesham Yasser
 * @version  1.0
 * @date 	 Nov 3, 2023
 * @brief    The HAL_Ultrasonic Header file that has private functions **Ultrasonic** driver.
 *
 */


#ifndef ULTRASONIC_PRIVATE_H_
#define ULTRASONIC_PRIVATE_H_

/**
 * @fn void HUltrasonic_voidCallBack(void)
 * @param 	none
 * @brief This Function Capture value from the specified channel (ECHO-pin) and calculate distance.
 *
 */
static void HUltrasonic_voidCallBack (void);



#endif /* ULTRASONIC_PRIVATE_H_ */
