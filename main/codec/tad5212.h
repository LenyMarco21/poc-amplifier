/**
 * Written by Leny Marcolini
 *
 * Driver of TAD5212 audio CODEC
 * 
 * No licence
 */

#ifndef __TAD5212_H__
#define __TAD5212_H__

/*** Includes **************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "driver/i2c_master.h"
#include "esp_check.h"
#include "esp_log.h"

/*** Defines **************************************************************************/

/* log tag */
#define TAD5212_TAG    "TAD5212"

/* Debug mode */
#define TAD5212_DEBUG

/*** Enumerations *********************************************************************/

/* TAD5212 configuration types */
typedef enum
{
    TAD5212_CONFIG_STEREO = 0,
    TAD5212_CONFIG_SUBWOOFER,
}
tad5212_config_select_t;

/* TAD5212 channels selection */
typedef enum
{
    TAD5212_CHANNEL_BOTH = 0,
    TAD5212_CHANNEL_LEFT,
    TAD5212_CHANNEL_RIGHT,
}
tad5212_channel_t;

/* TAD5212 addresses */
typedef enum
{
    TAD5212_I2C_ADDR_SHORT      = 0x50,
    TAD5212_I2C_ADDR_PD_4_7K    = 0x51,
    TAD5212_I2C_ADDR_PU_22K     = 0x52,
    TAD5212_I2C_ADDR_PU_4_7K    = 0x53,
}
tad5212_i2c_addr_t;

/*** Structures ***********************************************************************/

typedef struct 
{
    i2c_master_bus_handle_t bus;
    i2c_master_dev_handle_t dev;
    tad5212_i2c_addr_t      addr;
    _lock_t                 lock;
    bool                    initialized;
} 
tad5212_handle_t;

/*** Extern functions *****************************************************************/

/**
 *  \brief Initialize the TAD5212 codec
 *  \param device TAD5212 device
 *  \param i2c_bus_handle I2C bus handler
 *  \param i2c_addr I2C address of the TAD5212 device
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_init(tad5212_handle_t* device, i2c_master_bus_handle_t i2c_bus_handle, tad5212_i2c_addr_t i2c_addr, tad5212_config_select_t cfg);


/**
  *  \brief Get the status of the TAD5212 DAC channels
  *  \param device TAD5212 device
  *  \return ESP_OK on success, error code otherwise.
  */
esp_err_t tad5212_dac_status(tad5212_handle_t* device);


/**
 *  \brief Set the volume of the TAD5212 codec
 *  \param channel Channel to set volume
 *  \param volume Volume level (0-100)
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_set_volume(tad5212_handle_t* device, tad5212_channel_t channel, uint8_t volume);


/**
 *  \brief Swap OUT1 & OUT2 channels of the TAD5212 codec
 *  \param device TAD5212 device
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_swap_channels(tad5212_handle_t* device);


/**
 *  \brief Deinitialize the TAD5212 codec
 *  \param device TAD5212 device
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_deinit(tad5212_handle_t* device);

#endif /* __TAD5212_H__ */
