/**
 * @file	MSPI_Configurations.h
 * @author 	Hesham Yasser
 * @version 1.0
 * @date 	20 sep 2023
 * @brief 	The Serial peripheral interface header file that has all the configurations and options and modes of the **SPI**
 */

#ifndef MSPI_CONFIGURATIONS_H_
#define MSPI_CONFIGURATIONS_H_

/******************ٍSPI1 Configuration**************/

/*
 * MSPI1_STATE :-
 	 * MSPI_ENABLED
 	 * MSPI_DISABLED
 */
#define MSPI1_STATE				MSPI_ENABLED						//!< this macro select the state of the SPI_1

/*
 * MSPI1_CLK_MODE :-
 	 * MSPI_CLK_MODE_0
 	 * MSPI_CLK_MODE_1
 	 * MSPI_CLK_MODE_2
 	 * MSPI_CLK_MODE_3
 */
#define MSPI1_CLK_MODE			MSPI_CLK_MODE_3						//!< this macro select the clock state of the SPI_1

/*
 * MSPI1_MASTER_SLAVE :-
 	 * MSPI_MASTER
 	 * MSPI_SLAVE
 */
#define MSPI1_MASTER_SLAVE		MSPI_MASTER							//!< this macro select the mode of the node 

/*
 * MSPI1_PRESCALER :-
 	 * MSPI_PRESCALER_BY2
 	 * MSPI_PRESCALER_BY4
 	 * MSPI_PRESCALER_BY8
 	 * MSPI_PRESCALER_BY16
 	 * MSPI_PRESCALER_BY32
 	 * MSPI_PRESCALER_BY64
 	 * MSPI_PRESCALER_BY128
 	 * MSPI_PRESCALER_BY256
 */
#define MSPI1_PRESCALER		MSPI_PRESCALER_BY4						//!< this macro select the prescaler of the clock of the SPI_1

/*
 * MSPI1_DATA_ORDER :-
 	 * MSPI_MSB_FIRST
 	 * MSPI_LSB_FIRST
 */
#define MSPI1_DATA_ORDER	MSPI_MSB_FIRST							//!< this macro select the method of transmitting the data

/*
 * MSPI1_SS_MANAGE :-
 	 * MSPI_HW_SLAVE_MANAGEMENT
 	 * MSPI_SW_SLAVE_MANAGEMENT
 */
#define MSPI1_SS_MANAGE		MSPI_HW_SLAVE_MANAGEMENT				//!< this macro select the method of handling the slave either by software or hardware

/*
 * MSPI1_DATA_SIZE :-
 	 * MSPI_8BIT_DATA
 	 * MSPI_16BIT_DATA
 */
#define MSPI1_DATA_SIZE		MSPI_8BIT_DATA							//!< this macro select the size of the data

/*
 * MSPI1_TX_INTERRUPT_STATE :-
 	 * MSPI_INTERRUPT_ENABLE
 	 * MSPI_INTERRUPT_DISABLE
 */
#define MSPI1_TX_INTERRUPT_STATE	MSPI_INTERRUPT_DISABLE			//!< this macro select the status of the interrupt of the empty buffer

/*
 * MSPI1_RX_INTERRUPT_STATE :-
 	 * MSPI_INTERRUPT_ENABLE
 	 * MSPI_INTERRUPT_DISABLE
 */
#define MSPI1_RX_INTERRUPT_STATE	MSPI_INTERRUPT_DISABLE			//!< this macro select the status of the interrupt of the not empty buffer

/******************ٍSPI2 Configuration**************/

/*
 * MSPI2_STATE :-
 	 * MSPI_ENABLED
 	 * MSPI_DISABLED
 */
#define MSPI2_STATE				MSPI_ENABLED						//!< this macro select the state of the SPI_2

/*
 * MSPI2_CLK_MODE :-
 	 * MSPI_CLK_MODE_0
 	 * MSPI_CLK_MODE_1
 	 * MSPI_CLK_MODE_2
 	 * MSPI_CLK_MODE_3
 */
#define MSPI2_CLK_MODE			MSPI_CLK_MODE_3						//!< this macro select the clock state of the SPI_2

/*
 * MSPI2_MASTER_SLAVE :-
 	 * MSPI_MASTER
 	 * MSPI_SLAVE
 */
#define MSPI2_MASTER_SLAVE		MSPI_SLAVE							//!< this macro select the mode of the node 

/*
 * MSPI2_PRESCALER :-
 	 * MSPI_PRESCALER_BY2
 	 * MSPI_PRESCALER_BY4
 	 * MSPI_PRESCALER_BY8
 	 * MSPI_PRESCALER_BY16
 	 * MSPI_PRESCALER_BY32
 	 * MSPI_PRESCALER_BY64
 	 * MSPI_PRESCALER_BY128
 	 * MSPI_PRESCALER_BY256
 */
#define MSPI2_PRESCALER		MSPI_PRESCALER_BY4						//!< this macro select the prescaler of the clock of the SPI_2

/*
 * MSPI2_DATA_ORDER :-
 	 * MSPI_MSB_FIRST
 	 * MSPI_LSB_FIRST
 */
#define MSPI2_DATA_ORDER	MSPI_MSB_FIRST							//!< this macro select the method of transmitting the data					

/*
 * MSPI2_SS_MANAGE :-
 	 * MSPI_HW_SLAVE_MANAGEMENT
 	 * MSPI_SW_SLAVE_MANAGEMENT
 */
#define MSPI2_SS_MANAGE		MSPI_HW_SLAVE_MANAGEMENT				//!< this macro select the method of handling the slave either by software or hardware

/*
 * MSPI2_DATA_SIZE :-
 	 * MSPI_8BIT_DATA
 	 * MSPI_16BIT_DATA
 */
#define MSPI2_DATA_SIZE		MSPI_8BIT_DATA							//!< this macro select the size of the data

/*
 * MSPI2_TX_INTERRUPT_STATE :-
 	 * MSPI_INTERRUPT_ENABLE
 	 * MSPI_INTERRUPT_DISABLE
 */
#define MSPI2_TX_INTERRUPT_STATE	MSPI_INTERRUPT_DISABLE			//!< this macro select the status of the interrupt of the empty buffer

/*
 * MSPI2_RX_INTERRUPT_STATE :-
 	 * MSPI_INTERRUPT_ENABLE
 	 * MSPI_INTERRUPT_DISABLE
 */
#define MSPI2_RX_INTERRUPT_STATE	MSPI_INTERRUPT_ENABLE			//!< this macro select the status of the interrupt of the not empty buffer



#endif /* MSPI_CONFIGURATIONS_H_ */
