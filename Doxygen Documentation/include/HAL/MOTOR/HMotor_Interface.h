/**
 * @file	HMotor_Interface.h
 * @author 	Seif Eldeen Ashraf
 * @version 1.0
 * @date 	10 Oct 2023
 * @brief    The Motor Interface Header file that has all the prototypes and arguments of **Motor** driver
 */

#ifndef HMOTORDRIVER_INTERFACE_H_
#define HMOTORDRIVER_INTERFACE_H_
/**
 * @fn 		void HMotor_VoidCarInit(void)
 * @brief   This function is responsible of Initializing the motor
 * @param 	none
 * @return 	none
 * @details This function initialize the motor:
 * -# Switching the pins which controls the motor to Output mode
 * -#Initializing the Timer's Channels with PWM
 */
void HMotor_VoidCarInit(void);
/**
 * @fn 		void HMotor_VoidCarForword(void)
 * @brief   This function is responsible of Moving The Motor Forward
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarForword(void);
/**
 * @fn 		void HMotor_VoidCarBackword(void)
 * @brief   This function is responsible of Moving The Motor Backward
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarBackword(void);
/**
 * @fn 		void HMotor_VoidCarStop(void)
 * @brief   This function is responsible of Stopping the motor
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarStop(void);

/**
 * @fn 		void HMotor_VoidCarRight(void)
 * @brief   This function is responsible of Moving The Motor Right
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarRight(void);
/**
 * @fn 		void HMotor_VoidCarLeft(void)
 * @brief   This function is responsible of Moving The Motor Left
 * @param 	none
 * @return 	none
 */
void HMotor_VoidCarLeft(void);
/**
 * @fn 		void HMotor_VoidCarSpeed(u16)
 * @brief   This function is responsible of Controlling the Speed of motor
 * @param 	Copy_u16DutyCycle Copy of the Value which assigned to the Register that Register is responsible of duty cycle
 * @return 	none
 */
void HMotor_VoidCarSpeed(u16 Copy_u16DutyCycle);
/**
 * @fn 		void HMotor_VoidCarSpeedRight(u16)
 * @brief   This function is responsible of Controlling the speed of the right motors
 * @param 	Copy_u16DutyCycle Copy of the Value which assigned to the Register that Register is responsible of duty cycle of the Right motors
 * @return 	none
 */
void HMotor_VoidCarSpeedRight(u16 Copy_u16DutyCycle);
/**
 * @fn 		void HMotor_VoidCarSpeedLeft(u16)
 * @brief   This function is responsible of Controlling the speed of the Left motors
 * @param 	Copy_u16DutyCycle Copy of the Value which assigned to the Register that Register is responsible of duty cycle of the Left motors
 * @return 	none
 */
void HMotor_VoidCarSpeedLeft(u16 Copy_u16DutyCycle);
#endif /* HMOTORDRIVER_INTERFACE_H_ */
