/**
 * @file	MNVIC_Private.h
 * @author 	Hesham Yasser
 * @version 2.0
 * @date 	4 Oct 2023
 * @brief 	the NVIC private header file that contains private declatations used in the NVIC driver
 */

#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


#define NVIC_BASE_ADDRESS			(0xE000E100)			//<! this is the base address of NVIC registers


/**
 * @struct NVIC_t
 * @brief this struct contains the NVIC registers
 */
typedef struct {
	u32 ISER[8];
	u32 RESERVED1[24];
	u32 ICER[8];
	u32 RESERVED2[24];
	u32 ISPR[8];
	u32 RESERVED3[24];
	u32 ICPR[8];
	u32 RESERVED4[24];
	u32 IABR[8];
	u32 RESERVED5[56];
	u8 	IPR	[240];
	u32 RESERVED6[580];
	u32 STIR;
}NVIC_t;

#define NVIC				((volatile NVIC_t *)NVIC_BASE_ADDRESS)		//<! this is a pointer to NVIC registers

#define SCB_AIRCR			(*(volatile u32 *)0xE000ED0C)				//<! this is a pointer to SCB_AIRCR register

/**********************MACROs*********************/

#define BITS_IN_REGISTER			32								//<! this macro defines number of bits in register
#define AICIR_PRIGROUP_b0			8								//<! this macro defines the starting bit to set Groups options
#define THREE_BIT_MASK				0b111							//<! this macro is used in masking three bits
#define SCB_AIRCR_VECT_KEY			0x05FA0000						//<! this is the key to enable editing in SCB_AIRCR register


#endif /* NVIC_PRIVATE_H_ */
