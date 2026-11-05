/*
 * main .c
 *
 *  Created on: 03.02.2025
 *      Author: griesmaier
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../inc/main.h"
#include "../inc/f1958.h"

// this is only to illustrate how the driver works.
int main(void)
{
	f1958_device_t F1958 = f1958_device_default;
	// The structure of si5391_spi_conf_t and the handle and pin definitions below below are for an STM32 project. 
	// This has to be adapted if other microcontrollers are used to control the F1958.
	printf("\n=> Initialize the device.\n");
	f1958_init(&F1958, (f1958_spi_conf_t) {.cs_pin = CSb_Pin, .cs_port = CSb_GPIO_Port, .hspi = "hspi4"});
	for (int i =0;i<128;i++) {
		printf("=> send%d ",i);
		f1958_write_spi(&F1958, i);
		float damping = F1958.current_value * 0.25;
		printf("   damping: -%f dB\n", damping);
	}

	for (float i=F1958.mindamp;i<F1958.maxdamp+2;i+=F1958.step/4) {
		f1958_damp_dB(&F1958, i);
		printf("=> requesting %f dB and get ", i);
		float damping = F1958.current_value * 0.25;
		printf("   damping: -%f dB\n", damping);
	}

}
