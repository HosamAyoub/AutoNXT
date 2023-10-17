/*
 * MFMI_private.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Hesham Yasser
 */

#ifndef MFMI_PRIVATE_H_
#define MFMI_PRIVATE_H_

#define FMI_BASE_ADDRESS			(0x40023C00)


typedef struct{
	u32 PG : 1;
	u32 SER : 1;
	u32 MER : 1;
	u32 SNB : 4;
	u32 Res1 : 1;
	u32 PSIZE : 2;
	u32 Res2 : 6;
	u32 STRT : 1;
	u32 Res3 : 7;
	u32 EOPIE : 1;
	u32 ERRIE : 1;
	u32 Res4 : 5;
	u32 LOCK : 1;
}CR_t;

typedef struct{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	CR_t CR;
	u32 OPTCR;
}FMI_t;



#define FMI							((volatile FMI_t * )FMI_BASE_ADDRESS)


/**********************Macros********************/

#define KEY1  					0x45670123
#define KEY2  					0xCDEF89AB

#define LOCKED					1

#define ENABLED					1

#define DISABLED				0

#define BUSY					1

#define HALF_WORD				0b01

#define SR_BSY					16
#define SR_EOP					0


#endif /* MFMI_PRIVATE_H_ */
