/*
 * MDMA_private.h
 *
 *  Created on: Sep 17, 2023
 *      Author: Hesham Yasser
 */

#ifndef MDMA_PRIVATE_H_
#define MDMA_PRIVATE_H_


#define DMA1_BASE_ADDRESS			(0x40026000)
#define DMA2_BASE_ADDRESS			(0x40026400)

typedef struct{
	u32 CR;
	u32 NDTR;
	u32 PAR;
	u32 M0AR;
	u32 M1AR;
	u32 FCR;
}DMA_Stream_t;


typedef struct{
	u32 LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;
	DMA_Stream_t S[8];
}DMA_t;

#define DMA1			((volatile DMA_t * )DMA1_BASE_ADDRESS)
#define DMA2			((volatile DMA_t * )DMA2_BASE_ADDRESS)

/*******************MACROs*******************/

#define DMA_NUMBER			2
#define STREAM_NUMBER		8
#define CHANNEL_NUMBER		8
#define MDMA_ENABLE			0
#define TWO_BIT_MASK		0b11
#define THREE_BIT_MASK		0b111
#define CR_CHSEL			25
#define CR_MBURST			23
#define CR_PBURST			21
#define CR_DBM				18
#define CR_PL				16
#define CR_PINCOS			15
#define CR_MSIZE			13
#define CR_PSIZE			11
#define CR_MINC				10
#define CR_PINC				9
#define CR_CIRC				8
#define CR_DIR				6
#define CR_PFCTRL			5
#define CR_TCIE				4
#define CR_HTIE				3
#define CR_TEIE				2
#define CR_DMEIE			1
#define CR_EN				0
#define FCR_FEIE			7
#define FCR_DMDIS			2
#define FCR_FTH				0
#define LIFCR_CTCIF0		5
/*****************Burst transfer**************/

#define MDMA_SINGLE_TRANSFER			0b00
#define MDMA_INCR4						0b01
#define MDMA_INCR8						0b10
#define MDMA_INCR16						0b11

/******************Double Buffer*************/

#define MDMA_DOUBLE_BUFFER_ON			1
#define MDMA_DOUBLE_BUFFER_OFF			0

/*******************Priority*******************/

#define MDMA_PRIORITY_LOW				0b00
#define MDMA_PRIORITY_MED				0b01
#define MDMA_PRIORITY_HIGH				0b10
#define MDMA_PRIORITY_VHIGH				0b11

/***************Peripheral Increment Size*******/

#define MDMA_SIZE_LINKED_PSIZE			0
#define MDMA_SIZE_FIXED_4BYTE			1

/*****************Increment Mode***************/

#define MDMA_POINTER_FIXED						0
#define MDMA_POINTER_INCREMENTED				1

/***************Data Tranfer Direction**********/

#define MDMA_PERIPHERAL_TO_MEMORY				0b00
#define MDMA_MEMORY_TO_PERIPHERAL				0b01
#define MDMA_MEMORY_TO_MEMORY					0b10

/*************Circular Mode*********************/

#define MDMA_CIRCULAR_MODE_ENABLED				1
#define MDMA_CIRCULAR_MODE_DISABLED				0

/***********Peripheral Flow Controller**********/

#define MDMA_DMA_CONTROLLER						0
#define MDMA_PERIPHERAL_CONTROLLER				1

/***************Interrupt States***************/

#define MDMA_INTERRUPT_ENABLED					1
#define MDMA_INTERRUPT_DISABLED					0

/*****************Direct Mode*****************/

#define MDMA_DIRECT_MODE_ENABLED				1
#define MDMA_DIRECT_MODE_DISABLED				0

/****************FIFO Threshold**************/

#define MDMA_FIFO_BY_4							0b00
#define MDMA_FIFO_BY_2							0b01
#define MDMA_FIFO_BY_3BY4						0b10
#define MDMA_FIFO_BY_1							0b11




#endif /* MDMA_PRIVATE_H_ */
