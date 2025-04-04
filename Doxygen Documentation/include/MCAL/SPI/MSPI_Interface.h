/**
 * @file	MSPI_Interface.h
 * @author 	Hesham Yasser
 * @version 1.0
 * @date 	20 sep 2023
 * @brief 	The Serial peripheral interface header file that has all the Prototypes of the functions of **SPI** driver
 */

#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

/*********************MACROs***********************/

#define MSPI_ENABLED			1					//!< this macro assigned to the state that will make the spi enabled
#define MSPI_DISABLED			0					//!< this macro assigned to the state that will make the spi disabled


#define MSPI_CLK_MODE_0			0					//!< this macro is used to select the clock to read at rising and send at falling
#define MSPI_CLK_MODE_1			1					//!< this macro is used to select the clock to read at falling and send at rising 
#define MSPI_CLK_MODE_2			2					//!< this macro is used to select the clock to read at falling and send at rising
#define MSPI_CLK_MODE_3			3					//!< this macro is used to select the clock to read at rising and send at falling


#define MSPI_MASTER				1					//!< this macro is used to select the node to work in master mode
#define MSPI_SLAVE				0					//!< this macro is used to select the node to work in slave mode


#define MSPI_PRESCALER_BY2 		0b000				//!< this macro is used to select the clock of the SPI to be divided by 2
#define MSPI_PRESCALER_BY4		0b001				//!< this macro is used to select the clock of the SPI to be divided by 4
#define MSPI_PRESCALER_BY8 		0b010				//!< this macro is used to select the clock of the SPI to be divided by 8
#define MSPI_PRESCALER_BY16		0b011				//!< this macro is used to select the clock of the SPI to be divided by 16
#define MSPI_PRESCALER_BY32 	0b100``				//!< this macro is used to select the clock of the SPI to be divided by 32
#define MSPI_PRESCALER_BY64		0b101				//!< this macro is used to select the clock of the SPI to be divided by 64
#define MSPI_PRESCALER_BY128 	0b110				//!< this macro is used to select the clock of the SPI to be divided by 128	
#define MSPI_PRESCALER_BY256 	0b111				//!< this macro is used to select the clock of the SPI to be divided by 256


#define MSPI_MSB_FIRST			1					//!< this macro is used to select the most significant bit to be sent first 
#define MSPI_LSB_FIRST			0					//!< this macro is used to select the least significant bit to be sent first 


#define MSPI_HW_SLAVE_MANAGEMENT		1			//!< this macro is used to select hardware managment for the slave
#define MSPI_SW_SLAVE_MANAGEMENT		0			//!< this macro is used to select software mangment for the slave


#define MSPI_8BIT_DATA					0			//!< this macro is used to select the size of the data to be 8 bits
#define MSPI_16BIT_DATA					1			//!< this macro is used to select the size of the data to be 16 bits

#define MSPI_INTERRUPT_ENABLE			1			//!< this macro is used to enable any interrupt 
#define MSPI_INTERRUPT_DISABLE			0			//!< this macro is used to disable any interrupt 

/**********************APIs*******************/


void MSPI1_voidInit(void);

/**
 * @fn 		u16 MSPI1_voidSendReceiveData (u16 A_u16Data)
 * @brief   This function is responsible for Sending and Receiving the data through shift register
 * @param 	(u16)the data that will be sent through spi
 * @return 	(u16)the data that will be received through spi
 */
u16 MSPI1_voidSendReceiveData (u16 A_u16Data);

/**
 * @fn 		void MSPI1_voidSetCallBack (PtrToFunc_void p_CallBackFunc)
 * @brief   This funciton used to set the address of the function that wants to executed into the global pointer to funciton
 * @param 	pointer to function which hold the specific address of the funciton that will be executed when interrupt occurs 
 * @return 	none
 */
void MSPI1_voidSetCallBack (PtrToFunc_void p_CallBackFunc);


/**
 * @fn 		void MSPI2_voidInit(void)
 * @brief   This function is responsible for initializing the spi setting all desired configurations and modes 
 * @param 	none
 * @return 	none
 */
void MSPI2_voidInit(void);


/**
 * @fn 		u16 MSPI2_voidSendReceiveData (u16 A_u16Data)
 * @brief   This function is responsible for Sending and Receiving the data through SPI_2
 * @param 	(u16)the data that will be sent through spi
 * @return 	(u16)the data that will be received through spi
 */
u16 MSPI2_voidSendReceiveData (u16 A_u16Data);

/**
 * @fn 		void MSPI2_voidSetCallBack (PtrToFunc_void p_CallBackFunc)
 * @brief   This funciton used to set the address of the function that wants to executed into the global pointer to funciton
 * @param 	pointer to function which hold the specific address of the funciton that will be executed when interrupt occurs 
 * @return 	none
 */
void MSPI2_voidSetCallBack (PtrToFunc_void p_CallBackFunc);

/**
 * @fn 		u16 MSPI2_u16ReadReceivedValue(void)
 * @brief   This funciton used to read the data register asynchronous after the interrupt occurs
 * @param 	none
 * @return 	(u16) the received data through after interrupt occurs
 */
u16 MSPI2_u16ReadReceivedValue(void);


#endif /* MSPI_INTERFACE_H_ */
