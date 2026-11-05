/*
 * f1958.h
 *
 *  Created on: 03.02.2025
 *      Author: griesmaier
 */

#ifndef F1958_H_
#define F1958_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TESTINGWOHW
#define F1958_SPI_TIMEOUT			1000

/* f1958 chip and driver status                                    */
/* ================================================================ */
#define F1958_IS_INITIALIZED		1
#define F1958_NOT_INITIALIZED		0

#define F1958_MAXDAMP				((float) 31.75)
#define F1958_MINDAMP				((float) 0)
#define F1958_STEPdB				((float) 0.25)

typedef enum f1958_err {F1958_NOERR, F1958_ERR, F1958_ERR_PARAM_OUTOFRANGE} f1958_err_t;
typedef unsigned char f1958_reg_value_t;
typedef struct	f1958_spi_conf {
	uint16_t 					cs_pin;
	uint32_t 					cs_port;
	char						hspi[5];
} f1958_spi_conf_t;

typedef struct f1958_device {
	uint8_t 					is_initialized;
	f1958_spi_conf_t 			spi_if;
	uint8_t						current_value;
	float 						maxdamp;
	float						mindamp;
	float 						step;
} f1958_device_t;

f1958_device_t f1958_device_default;

f1958_err_t f1958_init(f1958_device_t *thisDevice, f1958_spi_conf_t f1958_spi_conf);
f1958_err_t si5391_deinit(f1958_device_t *thisDevice);

f1958_err_t f1958_spi_run(f1958_device_t *this_device, f1958_reg_value_t spi_send_data);

f1958_err_t f1958_write_spi(f1958_device_t *this_device, f1958_reg_value_t value);
f1958_err_t f1958_damp_dB(f1958_device_t *this_device,float damping);
#endif /* F1958_H_ */
