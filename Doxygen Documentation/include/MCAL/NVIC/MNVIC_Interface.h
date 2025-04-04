/**
 * @file	MNVIC_Interface.h
 * @author 	Hesham Yasser
 * @version 2.5
 * @date 	10 Oct 2023
 * @brief 	the NVIC interface header file that contains the declaration of all NVIC functions
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_


/**
 * @enum MNVIC_Group_t
 * @brief this is the enum containing all options of NVIC Group mode
 */
typedef enum{
	Groups16_NoSub = 3,/**< Groups16_NoSub */
	Groups8_Sub2,      /**< Groups8_Sub2 */
	Groups2_Sub8,      /**< Groups2_Sub8 */
	Groups4_Sub4,      /**< Groups4_Sub4 */
	NoGroup_Sub16      /**< NoGroup_Sub16 */
}MNVIC_Group_t;


/**
 * @fn void MNVIC_voidEnablePeripheralInterrupt(u8)
 * @brief this function is responsible for enabling certain peripheral interrupt
 * @param A_u8Peripheral this is the peripheral number to be enabled
 * @return none
 */
void MNVIC_voidEnablePeripheralInterrupt(u8 A_u8Peripheral);

/**
 * @fn void MNVIC_voidDisablePeripheralInterrupt(u8)
 * @brief this function is responsible for disabling certain peripheral interrupt
 * @param A_u8Peripheral this is the peripheral number to be disabled
 * @return none
 */
void MNVIC_voidDisablePeripheralInterrupt(u8 A_u8Peripheral);

/**
 * @fn void MNVIC_voidSetPeripheralInterruptPending(u8)
 * @brief this function is responsible for setting the pending flag of any interrupt source
 * @param A_u8Peripheral this is the peripheral interrput number to be setted
 * @return none
 */
void MNVIC_voidSetPeripheralInterruptPending(u8 A_u8Peripheral);

/**
 * @fn void MNVIC_voidClearPeripheralInterruptPending(u8)
 * @brief this function is responsible for clearing the pending flag of any interrupt source
 * @param A_u8Peripheral this is the peripheral interrput number to be cleared
 * @return none
 */
void MNVIC_voidClearPeripheralInterruptPending(u8 A_u8Peripheral);

/**
 * @fn void MNVIC_voidGetInterruptState(u8, u8*)
 * @brief this function is responsible for checking the interrupt state of any interrupt source
 * @param A_u8Peripheral this is the interrupt source to be checked
 * @param p_Read this is a pointer to variable to store the state in
 */
void MNVIC_voidGetInterruptState(u8 A_u8Peripheral , u8 * p_Read);

/**
 * @fn void MNVIC_voidSetInterruptGroupMode(MNVIC_Group_t)
 * @brief this function is responsible for setting the group mode of *NVIC*
 * @param A_MNVIC_Group_t_Mode this is the group configurations selected
 * @return none
 */
void MNVIC_voidSetInterruptGroupMode (MNVIC_Group_t  A_MNVIC_Group_t_Mode);

/**
 * @fn void MNVIC_voidSetInterruptPriority(u8, u8, u8)
 * @brief this function is responsible for setting the priority of any interrupt source
 * @param A_u8Peripheral this is the peripheral to be configured
 * @param A_u8GroupNumber this is the selected group for the selected interrupt source
 * @param A_u8SubNumber this is the selected sub-group for the selected interrupt source
 * @return none
 */
void MNVIC_voidSetInterruptPriority (u8 A_u8Peripheral , u8 A_u8GroupNumber , u8 A_u8SubNumber);






#endif /* NVIC_INTERFACE_H_ */
