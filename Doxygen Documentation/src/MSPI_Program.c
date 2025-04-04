/**
 * @file	MSPI_Program.c
 * @author 	Hesham Yasser
 * @version 1.0
 * @date 	20 sep 2023
 * @brief 	The Serial peripheral interface header file that has all implementations of the functions of the **SPI** driver
 */


#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/SPI/MSPI_Interface.h"
#include "../include/SPI/MSPI_Private.h"
#include "../include/SPI/MSPI_Config.h"

PtrToFunc_void SPI_CallBack[SPI_NUMBER];

void MSPI1_voidInit (void)
{
	/*Set Data Size*/
#if MSPI1_DATA_SIZE == MSPI_16BIT_DATA
	SET_BIT (SPI1->CR1 , CR1_DFF);
#else
	CLR_BIT (SPI1->CR1 , CR1_DFF);
#endif
	/*Set slave management mode*/
#if MSPI1_SS_MANAGE == MSPI_SW_SLAVE_MANAGEMENT
	SET_BIT (SPI1->CR1 , CR1_SSM);
	SET_BIT(SPI1->CR1 , CR1_SSI);
#else
	CLR_BIT (SPI1->CR1 , CR1_SSM);
#endif
	/*Set Data Order*/
#if MSPI1_DATA_ORDER == MSPI_LSB_FIRST
	SET_BIT (SPI1->CR1 , CR1_LSBFIRST);
#else
	CLR_BIT (SPI1->CR1 , CR1_LSBFIRST);
#endif
	/*Set Clock Mode*/
	SPI1->CR1 &= ~(TWO_BIT_MASK<<CR1_CLK_SELECT);
	SPI1->CR1 |= (MSPI1_CLK_MODE<<CR1_CLK_SELECT);
	/*Set Interrupt States*/
#if MSPI1_TX_INTERRUPT_STATE == MSPI_INTERRUPT_ENABLE
	SET_BIT (SPI1->CR2 , CR2_TXEIE);
#else
	CLR_BIT (SPI1->CR2 , CR2_TXEIE);
#endif
#if MSPI1_RX_INTERRUPT_STATE == MSPI_INTERRUPT_ENABLE
	SET_BIT (SPI1->CR2 , CR2_RXNEIE);
#else
	CLR_BIT (SPI1->CR2 , CR2_RXNEIE);
#endif
	/*Set SPI Mode*/
#if MSPI1_MASTER_SLAVE == MSPI_MASTER
	SET_BIT (SPI1->CR1 , CR1_MSTR);
	/*Set Prescaler*/
	SPI1->CR1 &= ~(THREE_BIT_MASK<<CR1_BR);
	SPI1->CR1 |= (MSPI1_PRESCALER<<CR1_CLK_SELECT);
#else
	CLR_BIT (SPI1->CR1 , CR1_MSTR);
#endif
	/*ٍSet SPI State*/
#if MSPI1_STATE == MSPI_ENABLED
	SET_BIT (SPI1->CR1 , CR1_SPE);
#else
	CLR_BIT (SPI1->CR1 , CR1_SPE);
#endif
}

u16 MSPI1_voidSendReceiveData (u16 A_u16Data)
{
	/*Put data in SPI Data Register*/
#if MSPI1_DATA_SIZE == MSPI_16BIT_DATA
	SPI1->DR = A_u16Data;
#else
	SPI1->DR = (u8) A_u16Data;
#endif
	/*wait until SPI finishes*/
	while (GET_BIT(SPI1->SR , SR_BSY) == SPI_BUSY);
	return SPI1->DR;
}

void MSPI1_voidSetCallBack (PtrToFunc_void p_CallBackFunc)
{
	/*Set Call Back Function*/
	SPI_CallBack[0] = p_CallBackFunc;
}


void SPI1_IRQHandler (void)
{
	if (SPI_CallBack[0] != NULL)
	{
		SPI_CallBack[0]();
	}
}

/**
 * @fn 		void MSPI2_voidInit(void)
 * @brief   This function is responsible for initializing the spi setting all desired configurations and modes 
 * @param 	none
 * @return 	none
 * @details this function set all the configurations selected and modes which is:
   * -# Setting the size of the data  
   * -# Setting the method of management the slave  
   * -# Set the method of transmitting and receiving the data
   * -# Select which interrupt is enable and which is disable in the system
   * -# Select the clock state and set the prescaler to the spi peripheral
   * -# Select the mode of the spi either if it master or slave and select it to be enable or disable
   * -# Select the mode of the spi either if it master or slave and select it to be enable or disable
 */
void MSPI2_voidInit (void)
{
	/*Set Data Size*/
#if MSPI2_DATA_SIZE == MSPI_16BIT_DATA
	SET_BIT (SPI2->CR1 , CR1_DFF);
#else
	CLR_BIT (SPI2->CR1 , CR1_DFF);
#endif
	/*Set slave management mode*/
#if MSPI2_SS_MANAGE == MSPI_SW_SLAVE_MANAGEMENT
	SET_BIT (SPI2->CR1 , CR1_SSM);
	SET_BIT(SPI2->CR1 , CR1_SSI);
#else
	CLR_BIT (SPI2->CR1 , CR1_SSM);
#endif
	/*Set Data Order*/
#if MSPI2_DATA_ORDER == MSPI_LSB_FIRST
	SET_BIT (SPI2->CR1 , CR1_LSBFIRST);
#else
	CLR_BIT (SPI2->CR1 , CR1_LSBFIRST);
#endif
	/*Set Clock Mode*/
	SPI2->CR1 &= ~(TWO_BIT_MASK<<CR1_CLK_SELECT);
	SPI2->CR1 |= (MSPI2_CLK_MODE<<CR1_CLK_SELECT);
	/*Set Interrupt States*/
#if MSPI2_TX_INTERRUPT_STATE == MSPI_INTERRUPT_ENABLE
	SET_BIT (SPI2->CR2 , CR2_TXEIE);
#else
	CLR_BIT (SPI2->CR2 , CR2_TXEIE);
#endif
#if MSPI2_RX_INTERRUPT_STATE == MSPI_INTERRUPT_ENABLE
	SET_BIT (SPI2->CR2 , CR2_RXNEIE);
#else
	CLR_BIT (SPI2->CR2 , CR2_RXNEIE);
#endif
	/*Set SPI Mode*/
#if MSPI2_MASTER_SLAVE == MSPI_MASTER
	SET_BIT (SPI2->CR1 , CR1_MSTR);
	/*Set Prescaler*/
	SPI2->CR1 &= ~(THREE_BIT_MASK<<CR1_BR);
	SPI2->CR1 |= (MSPI2_PRESCALER<<CR1_CLK_SELECT);
#else
	CLR_BIT (SPI2->CR1 , CR1_MSTR);
#endif
	/*ٍSet SPI State*/
#if MSPI2_STATE == MSPI_ENABLED
	SET_BIT (SPI2->CR1 , CR1_SPE);
#else
	CLR_BIT (SPI2->CR1 , CR1_SPE);
#endif
}

/**
 * @fn 		u16 MSPI2_voidSendReceiveData (u16 A_u16Data)
 * @brief   This function is responsible for Sending and Receiving the data through SPI_2
 * @param 	(u16)the data that will be sent through spi
 * @return 	(u16)the data that will be received through spi
 */
u16 MSPI2_voidSendReceiveData (u16 A_u16Data)
{
	/*Put data in SPI Data Register*/
#if MSPI2_DATA_SIZE == MSPI_16BIT_DATA
	SPI2->DR = A_u16Data;
#else
	SPI2->DR = (u8) A_u16Data;
#endif
	/*wait until SPI finishes*/
	while (GET_BIT(SPI2->SR , SR_BSY) == SPI_BUSY);
	return SPI2->DR;
}

/**
 * @fn 		void MSPI2_voidSetCallBack (PtrToFunc_void p_CallBackFunc)
 * @brief   This funciton used to set the address of the function that wants to executed into the global pointer to funciton
 * @param 	pointer to function which hold the specific address of the funciton that will be executed when interrupt occurs 
 * @return 	none
 */
void MSPI2_voidSetCallBack (PtrToFunc_void p_CallBackFunc)
{
	/*Set Call Back Function*/
	SPI_CallBack[1] = p_CallBackFunc;
}

/**
 * @fn 		void SPI2_IRQHandler (void)
 * @brief   This funciton is going to be executed when the interrupt occurs then it will call the global pointer to funciton which holds the address of the specific function that will be executed
 * @param 	none
 * @return 	none
 */
void SPI2_IRQHandler (void)
{
	if (SPI_CallBack[1] != NULL)
	{
		SPI_CallBack[1]();
	}
}

/**
 * @fn 		u16 MSPI2_u16ReadReceivedValue(void)
 * @brief   This funciton used to read the data register asynchronous after the interrupt occurs
 * @param 	none
 * @return 	(u16) the received data through after interrupt occurs
 */
u16 MSPI2_u16ReadReceivedValue(void)
{
	return SPI2->DR;
}

