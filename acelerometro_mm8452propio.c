/**
 * @file    mma_8451propio.c
 * @author  maria alejandra pabon
 * @version V0.2
 * @brief   Application entry point.
 */
/*  SDK Included Files */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"

/*  SDK HAL Files */
#include "sdk_hal_gpio.h"
#include "sdk_hal_uart0.h"
#include "sdk_hal_i2c0.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MMA8451_I2C_DEVICE_ADDRESS	0x1D
#define MMA851_I2C_DEVICE_ADDRESS	0x1D

#define MMA8451_WHO_AM_I_MEMORY_ADDRESS		0x0D
#define MMA8451_OUT_X_MSB	0x01
#define MMA8451_OUT_X_LSB	0x02
#define MMA8451_OUT_Y_MSB	0x03
#define MMA8451_OUT_Y_LSB	0x04
#define MMA8451_OUT_Z_MSB	0x05
#define MMA8451_OUT_Z_LSB	0x06



/*
 * @brief   Application entry point.
 */
int main(void) {

	status_t status;
    uint8_t nuevo_byte_uart;
	uint8_t	nuevo_dato_i2c;
	uint8_t X_MSB;
	uint8_t X_LSB;
	uint16_t dato_x;
	uint8_t Y_MSB;
	uint8_t Y_LSB;
	uint16_t dato_y;
	uint8_t Z_MSB;
	uint8_t Z_LSB;
	uint16_t dato_z;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    (void)uart0Inicializar(115200U);	//115200bps
    (void)i2c0MasterInit(100000U);	//100kbps

    PRINTF("Usar teclado para visualizar coordenadas (x, y, z) X, Y, Z \r\n");
        PRINTF("usar teclado para encender y apagar LEDS V-v, A-a, R-r\r\n");
        PRINTF("\r\n");


    while(1) {

    	if(uart0CuantosDatosHayEnBuffer()>0){
    		status=uart0LeerByteDesdeBuffer(&nuevo_byte_uart);
    		i2c0MasterWriteByte(MMA8451_I2C_DEVICE_ADDRESS, CTRL_REG1, 0x01);
    		if(status==kStatus_Success){
    			printf("dato:%c\r\n",nuevo_byte_uart);
    			switch (nuevo_byte_uart) {
				case 'a':
				case 'A':
					gpioPutToggle(KPTB10);
					break;

				case 'v':
					gpioPutHigh(KPTB7);
					break;
				case 'V':
					gpioPutLow(KPTB7);
					break;

				case 'r':
					gpioPutValue(KPTB6,1);
					break;
				case 'R':
					gpioPutValue(KPTB6,0);
					break;

				case 'm':
				case 'M':
				i2c0MasterReadByte(&nuevo_dato_i2c, MMA8451_I2C_DEVICE_ADDRESS, WHO_AM_I);


				if(nuevo_dato_i2c==0x1A)
			     	printf("MMA8451 encontrado!!\r\n");
					else
					printf("MMA8451 error\r\n");

					break;

				case 'x':
				case 'X':
				i2c0MasterReadByte(&X_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_X_MSB);
				i2c0MasterReadByte(&X_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_X_LSB);
				dato_x=(uint16_t)(X_MSB << 6 | X_LSB >> 2);
				printf("Valor en X: %i \r\n", dato_x);
				break;

				case 'y':
				case 'Y':
				i2c0MasterReadByte(&Y_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Y_MSB);
				i2c0MasterReadByte(&Y_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Y_LSB);
				dato_y=(uint16_t)(Y_MSB << 6 | Y_LSB >> 2);
				printf("Valor en Y: %i \r\n", dato_y);
				break;

				case 'z':
				case 'Z':
				i2c0MasterReadByte(&Z_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Z_MSB);
				i2c0MasterReadByte(&Z_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Z_LSB);
				dato_z=(uint16_t)(Z_MSB << 6 | Z_LSB >> 2);
				printf("Valor en Z: %i \r\n", dato_z);
				break;


								}
				    		}else{
				    			printf("error\r\n");
				    		}
				    	}
				    }

				    return 0 ;
				}

