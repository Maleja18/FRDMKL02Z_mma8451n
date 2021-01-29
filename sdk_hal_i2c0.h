/*! @file : sdk_hal_i2c0.c
 * @author  maria alejandra pabon
 * @version v0.2
 * @date    28/01/2021
 * @brief   Driver for I2C0
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#ifndef SDK_HAL_I2C0_H_
#define SDK_HAL_I2C0_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"


/*!
 * @addtogroup HAL
 * @{
 */
/*!
 * @addtogroup I2C
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
enum _i2c0_reg_address {

	STATUS_F_STATUS = 0x00,
	// DIRECCIÓN DE REGISTRO X, Y, Z /
	OUT_X_MSB,				//8 MSB de muestra de 14 bits
	OUT_X_LSB,				//6 LSB de muestra de 14 bits
	OUT_Y_MSB,				//8 MSB de muestra de 14 bits
	OUT_Y_LSB,				//6 LSB de muestra de 14 bits
	OUT_Z_MSB,				//8 MSB de muestra de 14 bits
	OUT_Z_LSB,				//6 LSB de muestra de 14 bits
	F_SETUP = 0x09,
	TRIG_CFG,
	SYSMOD,
	INT_SOURCE,
	WHO_AM_I,
	XYZ_DATA_CFG,
	HP_FILTER_CUTOFF,
	ASLP_COUNT,		 		//Configuración del contador para suspensión automática
	CTRL_REG1,		 		//ODR = 800 Hz, modo de espera.
	CTRL_REG2,		 		//Habilitación de suspensión, modos OS, RST, ST
	CTRL_REG3,		 		//Despertar de la suspensión, IPOL, PP_OD
	CTRL_REG4,		 		//Registro de habilitación de interrupciones
	CTRL_REG5,		 		//Mapa de pin de interrupción (INT1 / INT2)
	OFF_X,		 			//ajuste de eje X
	OFF_Y,		 			//Ajuste de eje Y
	OFF_Z,		 			//ajuste de eje Z




};

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
/*--------------------------------------------*/
/*!
 * @brief Inicializa I2C0 al baudrate especificado
 *
 * @param baud_rate   baudrate (bps) que se quiere configurado en I2C0
 * @return            resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t i2c0MasterInit(uint32_t baud_rate);

/*!
 * @brief Lee 1 byte usando puerto I2C0
 *
 * @param data   			apuntador a memoria donde almacenar dato obtenido
 * @param device_address	direccion en bus I2C de dispositivo remoto a leer
 * @param memory_address	posicion de memoria en el dispositivo remoto que se quiere leer
 * @return            		resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t i2c0MasterReadByte(uint8_t *data, uint8_t device_address, int8_t memory_address);

status_t i2c0MasterWriteByte(uint8_t device_address, int8_t memory_address, uint8_t data);




/** @} */ // end of I2C0 group
/** @} */ // end of HAL group

#endif /* SDK_HAL_I2C0_H_ */
