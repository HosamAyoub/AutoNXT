/**
 * @file     HUltrasonic_Config.h
 * @author	 Hesham Yasser
 * @version  1.0
 * @date 	 Nov 3, 2023
 * @brief    The HAL_Ultrasonic Header file that has the configurations of **Ultrasonic** driver.
 *
 */


#ifndef ULTRASONIC_CONFIGURATIONS_H_
#define ULTRASONIC_CONFIGURATIONS_H_

/**
 * @def   ULTRASONIC_TRIG_PORT
 * @brief GPIO Port used for Trigger.
 *
 */
#define ULTRASONIC_TRIG_PORT			GPIO_PORTA
/**
 * @def   ULTRASONIC_TRIG_PIN
 * @brief GPIO Pin used for Trigger.
 *
 */
#define ULTRASONIC_TRIG_PIN				GPIO_PIN4

/**
 * @def   ULTRA_SONIC_TIMER
 * @brief Number of Timer that used with Ultrasonic Sensor.
 *
 */
#define ULTRA_SONIC_TIMER				TIMER2



#endif /* ULTRASONIC_CONFIGURATIONS_H_ */
