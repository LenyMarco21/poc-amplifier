/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Driver of TPA3255 audio amplifier
 * 
 * No licence
 */

#ifndef __TPA3255_H__
#define __TPA3255_H__

/*** Includes ********************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "esp_check.h"
#include "esp_log.h"

/* log tag */
#define TPA3255_TAG    "TPA3255"

/*** Enumerations ****************************************************************/

typedef enum
{
    OTE_OLP_UVP_FAULT   = 0b00,
    OLP_UVP_FAULT       = 0b01,
    OTW_WARNING         = 0b10,
    NORMAL_OPERATION    = 0b11,
}
tpa3255_fault_flags_t;

/*** Structures ******************************************************************/

typedef struct
{
    uint8_t reset_gpio;
    uint8_t fault_gpio;
    uint8_t otw_clip_gpio;
    bool initialized;
}
tpa3255_device_t;

/*** Extern functions ************************************************************/

/**
 * \brief Initialize GPIOs for TPA3255 amplifier control.
 * \param device Pointer to the TPA3255 device structure.
 * \param reset GPIO number for the reset pin.
 * \param fault GPIO number for the fault pin.
 * \param otw_clip GPIO number for the over-temperature/warning clip pin.
 * \return ESP_OK if successful, otherwise an error code.
 */
esp_err_t tpa3255_gpio_init(tpa3255_device_t* device, uint8_t reset, uint8_t fault, uint8_t otw_clip);

/**
 * \brief Set the reset state of the TPA3255 amplifier.
 * \param device Pointer to the TPA3255 device structure.
 * \param reset Boolean value indicating whether to reset the amplifier.
 * \return ESP_OK if successful, otherwise an error code.
 */
esp_err_t tpa3255_gpio_set_reset(tpa3255_device_t* device, bool reset);

/**
 * \brief Get the status of the TPA3255 amplifier.
 * \param device Pointer to the TPA3255 device structure.
 * \return Fault status as tpa3255_fault_flags_t enumeration.
 */
tpa3255_fault_flags_t tpa3255_gpio_get_status(tpa3255_device_t* device);

#endif /* __TPA3255_H__ */