/**
 * @file	 MTIMER_Private.h
 * @author	 Hesham Yasser
 * @version  1.0
 * @date 	 Nov 2, 2023
 * @brief	 The MCAL_Timer Private file that has all the addresses of the registers, their base address and any private macros of **MTIMER** driver
 *
 */
#ifndef MTIMER_PRIVATE_H_
#define MTIMER_PRIVATE_H_

#define TIMER2_BASE_ADDRESS				(0x40000000) //!< The **MTIMER2** Base address
#define TIMER3_BASE_ADDRESS				(0x40000400) //!< The **MTIMER3** Base address
#define TIMER4_BASE_ADDRESS				(0x40000800) //!< The **MTIMER4** Base address
#define TIMER5_BASE_ADDRESS				(0x40000C00) //!< The **MTIMER5** Base address
/**
 * @struct TIMER_t
 * @brief  This struct has all MTIMER register
 *
 */
typedef struct
{
	u32 CR1;	 				//!< MTIM Control register 1
	u32 CR2; 	 				//!< MTIM Control register 2
	u32 SMCR;	 				//!< MTIM Slave mode Control register
	u32 DIER;	 				//!< MTIM DMA/Interrupt enable register
	u32 SR;                     //!< MTIM STATUS register
	u32 EGR;                    //!< MTIM Event generation register
	u32 CCMR1;                  //!< MTIM Capture/Compare mode register 1
	u32 CCMR2;                  //!< MTIM Capture/Compare mode register 2
	u32 CCER;                   //!< MTIM Capture/Compare Enable register
	u32 CNT;                    //!< MTIM Counter register
	u32 PSC;                    //!< MTIM Prescaler register
	u32 ARR;                    //!< MTIM Auto-Reload register
	u32 RESERVED1;              //!< RESERVED
	u32 CCR1;                   //!< MTIM Capture/Compare register 1
	u32 CCR2;                   //!< MTIM Capture/Compare register 2
	u32 CCR3;                   //!< MTIM Capture/Compare register 3
	u32 CCR4;                   //!< MTIM Capture/Compare register 4
	u32 RESERVED2;              //!< RESERVED
	u32 DCR;                    //!< MTIM DMA Control register
	u32 DMAR;                   //!< MTIM DMA address for full transfer
}TIMER_t;

/**
 * @def   TIM2
 * @brief TIM2 peripheral base address.
 *
 */
#define TIM2			((volatile TIMER_t *)TIMER2_BASE_ADDRESS)

/**
 * @def   TIM3
 * @brief TIM3 peripheral base address.
 *
 */
#define TIM3			((volatile TIMER_t *)TIMER3_BASE_ADDRESS)

/**
 * @def   TIM4
 * @brief TIM4 peripheral base address.
 *
 */
#define TIM4			((volatile TIMER_t *)TIMER4_BASE_ADDRESS)

/**
 * @def   TIM5
 * @brief TIM5 peripheral base address.
 *
 */
#define TIM5			((volatile TIMER_t *)TIMER5_BASE_ADDRESS)


/*****************MACROs****************/

#define CR1_CEN					0        //!< Counter Enable Bit, This Bit set to 1 to Enable The Timer
#define CR1_DIR					4        //!< Direction Bit, This Bit is used to Select Counter Direction upcounter or downcounter

#define CCMR1_CC1S				0        //!< Capture/Compare 1 selection, These Bits used to define the direction of channel(input/output)
#define CCMR1_CC2S				8        //!< Capture/Compare 2 selection, These Bits used to define the direction of channel(input/output)
#define CCMR2_CC3S				0        //!< Capture/Compare 3 selection, These Bits used to define the direction of channel(input/output)
#define CCMR2_CC4S				8        //!< Capture/Compare 4 selection, These Bits used to define the direction of channel(input/output)

#define CCMR1_OC1M				4        //!< Output compare 1 mode, These bits define the behavior of the output reference signal.
#define CCMR1_OC2M				12       //!< Output compare 2 mode, These bits define the behavior of the output reference signal.

#define CCMR2_OC3M				4        //!< Output compare 3 mode, These bits define the behavior of the output reference signal.
#define CCMR2_OC4M				12       //!< Output compare 4 mode, These bits define the behavior of the output reference signal.

#define CCER_CC1E				0        //!< Capture/Compare 1 output enable
#define CCER_CC1P				1        //!< Capture/Compare 1 output Polarity
#define CCER_CC1NP				3        //!< Capture/Compare 1 output Polarity

#define CCER_CC2E				4        //!< Capture/Compare 2 output enable
#define CCER_CC2P				5        //!< Capture/Compare 2 output Polarity
#define CCER_CC2NP				7        //!< Capture/Compare 2 output Polarity

#define CCER_CC3E				8        //!< Capture/Compare 3 output enable
#define CCER_CC3P				9        //!< Capture/Compare 3 output Polarity
#define CCER_CC3NP				11       //!< Capture/Compare 3 output Polarity

#define CCER_CC4E				12       //!< Capture/Compare 4 output enable
#define CCER_CC4P				13       //!< Capture/Compare 4 output Polarity
#define CCER_CC4NP				15       //!< Capture/Compare 4 output Polarity

#define TWO_BIT_MASK			0b11     //!< Mask of 2 bits
#define THREE_BIT_MASK			0b111    //!< Mask of 3 bits

#endif /* MTIMER_PRIVATE_H_ */
