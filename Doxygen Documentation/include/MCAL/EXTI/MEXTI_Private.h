/**
 * @file	MEXTI_Private.h
 * @author 	Hesham Yasser
 * @version 2.0
 * @date 	10 Oct 2023
 * @brief 	EXTI private header file that contains some private declarations
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


#define EXTI_BASE_ADDRESS				(0x40013C00)		//<! this is the base address of EXTI registers

/**
 * @struct EXTI_t
 * @brief struct that contains the registers of EXTI
 */
typedef struct{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}EXTI_t;

#define EXTI							((volatile EXTI_t *)EXTI_BASE_ADDRESS)		//<! this is a pointer to EXTI registers





/***********************EXTI_Configrations_Struct********************/
/**
 * @struct  MEXTI_Configuartions
 * @brief struct that contains the configurations of EXTI driver
 */
typedef struct{
	MEXTI_Line Line;
	MEXTI_Port Port;
	MEXTI_Mode Mode;
	MEXTI_State InitialValue;
}MEXTI_Configuartions;


/****************************MACROs***************************/

#define MEXTI_TOTAL_NUMBER				16

#define FOUR_BIT_MASK					0b1111


/****************************SYSCONFIG*************************/

#define SYSCFG_BASE_ADDRESS				(0x40013800)
/**
 * @struct SYSCFG_t
 * @brief struct that contains the registers of SYSCFG driver
 */
typedef struct{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];
	u32 RESERVED1[2];
	u32 CMPCR;
}SYSCFG_t;

#define SYSCFG							((volatile SYSCFG_t * )SYSCFG_BASE_ADDRESS)


#endif /* EXTI_PRIVATE_H_ */
