/**
 * @file HMotor_Config.h
 * @author Seif eldeen ashraf
 * @version 2.0
 * @date 18 Sep 2023
 * @brief The Motor header file that has all the configurations of the **Motor** driver
 */

#ifndef HMOTORDRIVER_CONFIG_H_
#define HMOTORDRIVER_CONFIG_H_



#define  MOTORDRIVER_PORT		GPIO_PORTB      //!<  The Port which has the pins that controls the motor

#define  MOTORDRIVER_IN1		GPIO_PIN6       //!<  The PIN1 that controls the motor

#define  MOTORDRIVER_IN2		GPIO_PIN1       //!<  The PIN2 that controls the motor

#define  MOTORDRIVER_IN3		GPIO_PIN2       //!<  The PIN3 that controls the motor

#define  MOTORDRIVER_IN4		GPIO_PIN5       //!<  The PIN4 that controls the motor

#define  TIMER_PWM				TIMER3          //!<  The Timer that controls the  Speed of motor

#define PRELOAD_VALUE			1000             //!<  The value that Initializes the  duty cycle of motor

#define NO_DUTYCYCLE			0               //!<  The value that Initializes the  duty cycle of motor with Zero
#endif /* HMOTORDRIVER_CONFIG_H_ */
