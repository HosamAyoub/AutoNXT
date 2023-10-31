/*******************************************************************************************/
/*******************************************************************************************/
/***********************            Author  : Hosam Ayoub            ***********************/
/***********************            Layer   : MCAL                   ***********************/
/***********************            SWC     : STK                    ***********************/
/***********************            Version : 2.0                    ***********************/
/***********************            Date    : 05 Oct 2023            ***********************/
/*******************************************************************************************/
/*******************************************************************************************/
#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_

#define CTRL                                  	(* (volatile u32 *) 0xE000E010)
#define CTRL_ENABLE								0
#define CTRL_TICKINT							1
#define CTRL_CLKSOURCE							2
#define CTRL_COUNTFLAG							16

#define LOAD                                  	(* (volatile u32 *) 0xE000E014)
#define VAL	                                  	(* (volatile u32 *) 0xE000E018)
#define CALIB                                 	(* (volatile u32 *) 0xE000E01C)

#define DIV_BY_8								8

#define SINGLE_INTERVAL							0
#define PERIODIC_INTERVAL						1

#endif