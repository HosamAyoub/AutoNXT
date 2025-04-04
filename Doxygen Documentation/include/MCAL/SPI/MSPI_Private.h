/**
 * @file	MSPI_Private.h
 * @author 	Hesham Yasser
 * @version 1.0
 * @date 	20 sep 2023
 * @brief 	The Serial peripheral interface header file that has all the addresses of the registers, their base address and any private macros of **SPI** driver
 */

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_


#define SPI1_BASE_ADDRESS			(0x40013000)	//!< The **SPI_1** Base Address
#define SPI2_BASE_ADDRESS			(0x40003800)	//!< The **SPI_2** Base Address
#define SPI3_BASE_ADDRESS			(0x40003C00)	//!< The **SPI_3** Base Address	
#define SPI4_BASE_ADDRESS			(0x40013400)	//!< The **SPI_4** Base Address

/**
 * @struct 	SPI_t
 * @brief	This struct has the SPI register
 *
 */
typedef struct{
	u32 CR1;		//!< SPI control register 1
	u32 CR2;		//!< SPI control register 2
	u32 SR;			//!< SPI status register
	u32 DR;			//!< SPI data register
	u32 CRCPR;		//!< SPI CRC Polynomial register
	u32 RXCRCR;		//!< SPI RXC RCR register
	u32 TXCRCR;		//!< SPI TX CRC register
	u32 I2SCFGR;	//!< SPI I2S Configuration register
	u32 I2SPR;		//!< SPI I2S prescaler register
}SPI_t;

#define SPI1			((volatile SPI_t *)SPI1_BASE_ADDRESS)	//!< Pointer that pointee to the starting of the struct of registers of SPI_1
#define SPI2			((volatile SPI_t *)SPI2_BASE_ADDRESS)	//!< Pointer that pointee to the starting of the struct of registers of SPI_2
#define SPI3			((volatile SPI_t *)SPI3_BASE_ADDRESS)	//!< Pointer that pointee to the starting of the struct of registers of SPI_3
#define SPI4			((volatile SPI_t *)SPI4_BASE_ADDRESS)	//!< Pointer that pointee to the starting of the struct of registers of SPI_4



#define SPI_NUMBER						4			//!< This macro will define the length of array of the global pointers to function

#define TWO_BIT_MASK					0b11		//!< this macro is used to clear any two bits next to each other

#define THREE_BIT_MASK					0b111		//!< this macro is used to clear any three bits next to each other

#define SPI_BUSY						1			//!< this bit flag indicates to the transmission buffer is not empty or busy

/**************CR1*****************/

#define CR1_DFF							11			//!< this bit select the size of data that waill be transmitted or received

#define CR1_SSM							9			//!< this bit select the slave will be controled by software 

#define CR1_SSI							8			//!< the value of this bit will be assigned to the NSS pin in case the SSM bit is set

#define CR1_LSBFIRST					7			//!< this bit will define the method that the data will be transmitted by

#define CR1_SPE							6			//!< this bit macro will be set in order to enable the spi peripheral
	
#define CR1_BR							3			//!< this macro will select the baud rate of transmission

#define CR1_MSTR						2			//!< this bit has to set in order to go with master mode
	
#define CR1_CLK_SELECT					0			//!< the clock select mode will be shifted by this macro

/**************CR2*****************/

#define CR2_TXEIE						7			//!< this bit enable the interrupt of the embty buffer

#define CR2_RXNEIE						6			//!< this bit enable the interrupt of the buffer not empty

/***************SR******************/

#define SR_TXE							1			//!< this bit flag is raised when the buffer is empty

#define SR_RXNE							0			//!< this bit flag is raised when the buffer is not empty

#define SR_BSY							7			//!< this bit flag is raised when the TX buffer is busy and SPI can't transmit any data befor checking that this bit is down





#endif /* MSPI_PRIVATE_H_ */
