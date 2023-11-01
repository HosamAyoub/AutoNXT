/*
 * MDMA_Interface.h
 *
 *  Created on: Sep 17, 2023
 *      Author: Hesham Yasser
 */

#ifndef MDMA_INTERFACE_H_
#define MDMA_INTERFACE_H_

/*****************DMAs******************/

#define MDMA1				0
#define MDMA2				1

/****************Streams****************/

#define MDMA_STREAM0		0
#define MDMA_STREAM1		1
#define MDMA_STREAM2		2
#define MDMA_STREAM3		3
#define MDMA_STREAM4		4
#define MDMA_STREAM5		5
#define MDMA_STREAM6		6
#define MDMA_STREAM7		7

/***************Channels****************/

#define MDMA_CHANNEL0		0
#define MDMA_CHANNEL1		1
#define MDMA_CHANNEL2		2
#define MDMA_CHANNEL3		3
#define MDMA_CHANNEL4		4
#define MDMA_CHANNEL5		5
#define MDMA_CHANNEL6		6
#define MDMA_CHANNEL7		7

/***************Data Size***************/

#define MDMA_BYTE				0b00
#define MDMA_HALF_WORD			0b01
#define MDMA_WORD				0b10

/*****************APIs******************/

void MDMA_voidInit(void);

void MDMA_voidSetStreamConfigurations(u8   A_u8DMAID,
								 u8	  A_u8StreamID,
								 u8   A_u8ChannelID,
								 u32* p_u8SourceAddress,
								 u32* p_u8DestinationAddress,
								 u8	  A_u8DataSize,
								 u16  A_u16BlockSize);

void MDMA_voidSetCallBack(u8 A_u8DMAID , u8 A_u8StreamID ,PtrToFunc_void A_CallBack);

void MDMA_voidEnableStream (u8 A_u8DMAID , u8 A_u8StreamID);


#endif /* MDMA_INTERFACE_H_ */
