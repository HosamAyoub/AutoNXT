/**
 * @file     MTIMER_Interface.h
 * @author	 Hesham Yasser
 * @version  1.0
 * @date 	 Nov 2, 2023
 * @brief    The MCAL_Timer Header file that has all the prototypes and arguments of **MTIMER** driver
 *
 */


#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_


/****************Timers****************/

/**
 * @enum   TIMERS_t
 * @brief  Enumeration for the Selected Timer of MTIM peripheral
 *
 */
typedef enum
{
	TIMER2,//!< TIMER2
	TIMER3,//!< TIMER3
	TIMER4,//!< TIMER4
	TIMER5 //!< TIMER5
}TIMERS_t;

/**************Channels****************/
/**
 * @enum 	CHANNELS_t
 * @brief	Enumeration for the Selected Channel of MTIM peripheral
 *
 */
typedef enum
{
	CHANNEL1 = 1,//!< CHANNEL1
	CHANNEL2,    //!< CHANNEL2
	CHANNEL3,    //!< CHANNEL3
	CHANNEL4     //!< CHANNEL4
}CHANNELS_t;


/************Channel Directions*********/

/**
 * @enum 	CHANNEL_DIR_t
 * @brief   Enumeration for the Direction of selected Channel of MTIM peripheral
 *
 */
typedef enum
{
	CHANNEL_OUTPUT,    //!< CHANNEL_OUTPUT
	CHANNELx_INPUT_TIx,//!< CHANNELx_INPUT_TIx
	CHANNELx_INPUT_TIy,//!< CHANNELx_INPUT_TIy
	CHANNEL_INPUT_TRC, //!< CHANNEL_INPUT_TRC

}CHANNEL_DIR_t;

/**************Count Directions*********/
/**
 * @enum    CNT_DIR_t
 * @brief   Enumeration for the counter mode of a MTIM peripheral
 *
 */
typedef enum
{
	UPCOUNT, //!< UPCOUNT
	DOWNCOUNT//!< DOWNCOUNT
}CNT_DIR_t;

/************Channel input polarity********/

/**
 * @enum 	CHANNEL_POL_t
 * @brief	Enumeration for the clock polarity of a MTIM peripheral
 *
 */
typedef enum
{
	RISING_EDGE,  //!< RISING_EDGE
	FALLING_EDGE, //!< FALLING_EDGE
	BOTH_EDGES = 3//!< BOTH_EDGES
}CHANNEL_POL_t;

/*************Output Modes***************/

/**
 * @enum    OUT_MODES_t
 * @brief	Enumeration for the output mode of a MTIM peripheral
 *
 */
typedef enum
{
	FROZEN,           //!< FROZEN
	ACTIVE_ON_MATCH,  //!< ACTIVE_ON_MATCH
	INACTIVE_ON_MATCH,//!< INACTIVE_ON_MATCH
	TOGGLE,           //!< TOGGLE
	FORCE_INACTIVE,   //!< FORCE_INACTIVE
	FORCE_ACTIVE,     //!< FORCE_ACTIVE
	PWM_MODE_1,       //!< PWM_MODE_1
	PWM_MODE_2        //!< PWM_MODE_2
}OUT_MODES_t;



/******************APIs****************/
/**
 * @fn 		void MTIMER_voidEnableTimer(TIMERS_t).
 * @brief 	This Function is to Enable The Specific Timer.
 *
 * @param 	A_Timer Number of selected Timer.
 * @return  none
 *
 */
void MTIMER_voidEnableTimer (TIMERS_t A_Timer);

/**
 * @fn 		void MTIMER_EnableChannelInterrupt(TIMERS_t, CHANNELS_t)
 * @brief	This Function to Enable Capture/Compare interrupt
 *
 * @param	A_Timer     Number of selected Timer.
 * @param 	A_Channel	Number of selected Channel.
 * @return  none
 */
void MTIMER_EnableChannelInterrupt (TIMERS_t A_Timer, CHANNELS_t A_Channel);

/**
 * @fn 		void MTIMER_voidSetPrescaler(TIMERS_t, u16)
 * @brief   This function to set Prescaler value of selected Timer.
 *
 * @param 	A_Timer			Number of selected Timer.
 * @param 	A_u16Prescaler	Value of Prescaler.
 * @return  none
 */

void MTIMER_voidSetPrescaler (TIMERS_t A_Timer, u16 A_u16Prescaler);

/**
 * @fn		 void MTIMER_voidSetTimerCountDirection(TIMERS_t, CNT_DIR_t)
 * @brief	 This function to determine the direction of the counter: Upcounting or DownCounting
 *
 * @param    A_Timer			Number of selected Timer.
 * @param    A_CNT_Direction	Direction of Counter.
 * @return   none
 */
void MTIMER_voidSetTimerCountDirection (TIMERS_t A_Timer, CNT_DIR_t A_CNT_Direction);

/**
 * @fn 		void MTIMER_voidSetChannelInputPolarity(TIMERS_t, CHANNELS_t, CHANNEL_POL_t)
 * @brief   This function to determine clock polarity of selected Timer and Channel.
 *
 * @param   A_Timer     Number of selected Timer.  ِ
 * @param   A_Channel   Number of selected Channel.ِ
 * @param   A_Polarity  Polarity of Clock: Rising/Falling/Both edges.
 * @return  none
 */
void MTIMER_voidSetChannelInputPolarity (TIMERS_t A_Timer, CHANNELS_t A_Channel, CHANNEL_POL_t A_Polarity);

/**
 * @fn 		void MTIMER_voidSetChannelDirection(TIMERS_t, CHANNELS_t, CHANNEL_DIR_t)
 * @brief	This Function to determine channel Direction: INPUT/OUTPUT
 *
 * @param A_Timer          Number of selected Timer.  ِ
 * @param A_Channel        Number of selected Channel.ِ
 * @param A_Direction      Direction of Channel.
 * @return  none
 */
void MTIMER_voidSetChannelDirection (TIMERS_t A_Timer, CHANNELS_t A_Channel, CHANNEL_DIR_t A_Direction);

/**
 * @fn 		u32 MTIMER_u32ReadChannelValue(TIMERS_t, CHANNELS_t)
 * @brief   This Function to Read the captured value from the specified channel.
 *
 * @param	A_Timer	   Number of selected Timer.
 * @param 	A_Channel  The channel from which to read the captured value.
 * @return  u32        The captured value from the specified channel.
 */
u32 MTIMER_u32ReadChannelValue (TIMERS_t A_Timer, CHANNELS_t A_Channel);

/**
 * @fn 		void MTIMER_voidSetCallBack(TIMERS_t, PtrToFunc_void)
 * @brief   This Function is used to Execute Function from other driver according to specific Interrrupt.
 *
 * @param 	A_Timer  Number of selected Timer.
 * @param	A_CallBack pointer to function that will be executed.
 * @return  none.
 */
void MTIMER_voidSetCallBack (TIMERS_t A_Timer, PtrToFunc_void A_CallBack);

/**
 * @fn 		void MTIMER_voidSetCounterValue(TIMERS_t, u32)
 * @brief 	This function to set The counter value in CNT register.
 *
 * @param   A_Timer        Number of selected Timer.
 * @param   A_u32CNTValue  The Counter value to set in CNT register.
 * @return  none.
 */
void MTIMER_voidSetCounterValue (TIMERS_t A_Timer, u32 A_u32CNTValue);

/**
 * @fn 		void MTIMER_voidSetARRValue(TIMERS_t, u32)
 * @brief   This function to determine The max value of counts the counter will reach it.
 *
 * @param   A_Tِimer			Number of selected Timer.
 * @param   A_u32ARRValue   The Max value of counts the counter will reach it.
 * @return  none.
 */
void MTIMER_voidSetARRValue (TIMERS_t A_Timer, u32 A_u32ARRValue);

/**
 * @fn 		u8 MTIMER_u8ReadInterruptState(TIMERS_t, CHANNELS_t)
 * @brief   This function to read state of Capture/compare interrupt flag of the specified channel.
 *
 * @param   A_Timer   Number of selected Timer.
 * @param   A_Channel The channel from which to read the interrupt state.
 * @return  u8 State value of Capture/compare interrupt flag.
 */
u8 MTIMER_u8ReadInterruptState (TIMERS_t A_Timer, CHANNELS_t A_Channel);

/**
 * @fn 	  void MTIMER_voidSetOutputMode(TIMERS_t, CHANNELS_t, OUT_MODES_t)
 * @brief This function to determine the output mode of of the specified channel.
 *
 * @param  A_Timer       Number of selected Timer.
 * @param  A_Channel 	 Number of selected Channel.
 * @param  A_Mode        Determine the output mode of specified channel.
 * @return none.
 */
void MTIMER_voidSetOutputMode (TIMERS_t A_Timer, CHANNELS_t A_Channel, OUT_MODES_t A_Mode);

/**
 * @fn 		void MTIMER_voidSetCCRValue(TIMERS_t, CHANNELS_t, u32)
 * @brief 	This function to Set the compare value for the specified channel.
 *
 * @param A_Timer        Number of selected Timer.
 * @param A_Channel      The channel for which to set the compare value.
 * @param A_u32CCRValue  The compare value to be set.
 * @return none.
 */
void MTIMER_voidSetCCRValue (TIMERS_t A_Timer, CHANNELS_t A_Channel, u32 A_u32CCRValue);
/**
 * @fn 	  void MTIMER_voidEnableOutputPin(TIMERS_t, CHANNELS_t)
 * @brief This Function to Enable Capture/Compare output.
 *
 * @param A_Timer        Number of selected Timer.
 * @param A_Channel      The channel for which to Enable Capture/Compare output.
 * @return none.
 */
void MTIMER_voidEnableOutputPin (TIMERS_t A_Timer, CHANNELS_t A_Channel);

/**
 * @fn     void MTIMER_voidSetPWMOption(TIMERS_t, CHANNELS_t, u32, u32, u16)
 * @brief  This Function Initialize the PWM MTIM peripheral output with the specified configuration.
 *
 * @param A_Timer          Number of selected Timer.
 * @param A_Channel        The channel for which to Output the PWM.
 * @param A_ARRValue	   The Max value of counts the counter will reach it.
 * @param A_CRRValue	   The compare value for the specified channel.
 * @param A_u16Prescaler   The value of Prescaler.
 * @return none.
 */
void MTIMER_voidSetPWMOption (TIMERS_t A_Timer, CHANNELS_t A_Channel, u32 A_ARRValue, u32 A_CRRValue, u16 A_u16Prescaler);


#endif /* MTIMER_INTERFACE_H_ */
