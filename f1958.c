/*
 * f1958.c
 *
 *  Created on: 03.02.2025
 *      Author: griesmaier
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "../inc/f1958.h"
f1958_device_t f1958_device_default ={
		.is_initialized = F1958_NOT_INITIALIZED,
		.mindamp = F1958_MINDAMP,
		.maxdamp = F1958_MAXDAMP,
		.step = F1958_STEPdB
};


f1958_err_t f1958_init(f1958_device_t *thisDevice, f1958_spi_conf_t f1958_spi_conf) {
	if(thisDevice->is_initialized == F1958_NOT_INITIALIZED)
		{
			thisDevice->spi_if 			= 	f1958_spi_conf;
			thisDevice->is_initialized	= 	F1958_IS_INITIALIZED;
			return F1958_NOERR;
		}
	return F1958_ERR;
}

f1958_err_t f1958_deinit(f1958_device_t *thisDevice) {
	// For the time being this is a pretty useless function. Should be filled with meaning in the end.
	f1958_err_t	status = F1958_ERR;
	if(thisDevice->is_initialized == F1958_IS_INITIALIZED)
	{
		thisDevice->is_initialized = F1958_NOT_INITIALIZED;
	}
	status =  F1958_NOERR; //should in the end really be a status!
	return status;
}

f1958_err_t f1958_spi_run(f1958_device_t *this_device, f1958_reg_value_t spi_send_data) {

	#ifndef TESTINGWOHW
	HAL_GPIO_WritePin((GPIO_TypeDef*) (this_device->spi_if.cs_port), (uint16_t) (this_device->spi_if.cs_pin), GPIO_PIN_RESET); //CS LOW
	HAL_SPI_TransmitReceive(this_device->spi_if.hspi, &spi_send_data, &spi_read_data, 1, F1958_SPI_TIMEOUT);
	HAL_GPIO_WritePin((GPIO_TypeDef*) (this_device->spi_if.cs_port), (uint16_t) (this_device->spi_if.cs_pin), GPIO_PIN_SET);  //CS HIGH
	#else
	// if testing w/o hardware print instead of writing to bus
	printf(" v DATA 0x%02x ^\n",spi_send_data);
	#endif
	return F1958_NOERR;
}

f1958_err_t f1958_write_spi(f1958_device_t *this_device, f1958_reg_value_t value) {

	value = value &0b01111111;
	f1958_err_t err = f1958_spi_run(this_device, value);
	if (F1958_NOERR==err) {
		this_device->current_value = value;
	}
	return err;
}


f1958_err_t f1958_damp_dB(f1958_device_t *this_device,float damping) {
	if ((damping>F1958_MAXDAMP)|(damping<F1958_MINDAMP)) {return F1958_ERR_PARAM_OUTOFRANGE;}
	uint8_t value = (uint8_t) floor(damping/F1958_STEPdB);
	return f1958_write_spi(this_device,value);
}


