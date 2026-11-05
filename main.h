/*
 * main.h
 *
 *  Created on: 03.02.2025
 *      Author: griesmaier
 */

#ifndef MAIN_H_
#define MAIN_H_


//only for testing
#define PERIPH_BASE               	0x40000000
#define D3_AHB1PERIPH_BASE       	(PERIPH_BASE + 0x18020000)
#define GPIOF_BASE            		(D3_AHB1PERIPH_BASE + 0x1400)
#define GPIOF               		GPIOF_BASE
#define GPIO_PIN_13                	(uint16_t) 0x2000

#define CSb_Pin 					GPIO_PIN_13
#define CSb_GPIO_Port				GPIOF

#endif /* MAIN_H_ */



