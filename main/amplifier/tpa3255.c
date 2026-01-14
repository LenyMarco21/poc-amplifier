/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Driver of TPA3255 audio amplifier
 * 
 * No licence
 */

#include "tpa3255.h"
#include "driver/gpio.h"

/*** Enumerations ****************************************************************/

/*** Structures ******************************************************************/

/*** Extern functions ************************************************************/

/**
 * \brief Initialize GPIOs for TPA3255 amplifier control.
 * \param device Pointer to the TPA3255 device structure.
 * \param reset GPIO number for the reset pin.
 * \param fault GPIO number for the fault pin.
 * \param otw_clip GPIO number for the over-temperature/warning clip pin.
 * \return ESP_OK if successful, otherwise an error code.
 */
esp_err_t tpa3255_gpio_init(tpa3255_device_t* device, uint8_t reset, uint8_t fault, uint8_t otw_clip)
{
    if (device == NULL) 
    {
        return ESP_ERR_INVALID_ARG;
    }

    device->reset_gpio = reset;
    device->fault_gpio = fault;
    device->otw_clip_gpio = otw_clip;

    if (gpio_reset_pin(reset) != ESP_OK)
    {
        ESP_LOGE(TPA3255_TAG, "GPIO reset failed");
        return ESP_ERR_INVALID_STATE;
    }

    if (gpio_set_direction(reset, GPIO_MODE_OUTPUT) != ESP_OK ||
        gpio_set_direction(fault, GPIO_MODE_INPUT) != ESP_OK ||
        gpio_set_direction(otw_clip, GPIO_MODE_INPUT) != ESP_OK)
    {
        ESP_LOGE(TPA3255_TAG, "GPIO set direction failed");
        return ESP_ERR_INVALID_STATE;
    }

    /* Initialize reset pin to low */
    gpio_set_level(reset, 0);

    device->initialized = true;

    return ESP_OK;
}

/**
 * \brief Set the reset state of the TPA3255 amplifier.
 * \param device Pointer to the TPA3255 device structure.
 * \param reset Boolean value indicating whether to reset the amplifier.
 * \return ESP_OK if successful, otherwise an error code.
 */
esp_err_t tpa3255_gpio_set_reset(tpa3255_device_t* device, bool reset)
{
    if ( device == NULL || device->initialized == false ) 
    {
        return ESP_ERR_INVALID_ARG;
    }

    gpio_set_level(device->reset_gpio, reset ? 0 : 1);

    return ESP_OK;
}

/**
 * \brief Get the status of the TPA3255 amplifier.
 * \param device Pointer to the TPA3255 device structure.
 * \return Fault status as tpa3255_fault_flags_t enumeration.
 */
tpa3255_fault_flags_t tpa3255_gpio_get_status(tpa3255_device_t* device)
{
    if ( device == NULL || device->initialized == false ) 
    {
        ESP_LOGE(TPA3255_TAG, "Device not initialized");
        return NORMAL_OPERATION;
    }

    bool fault_state = gpio_get_level(device->fault_gpio);
    bool otw_clip_state = gpio_get_level(device->otw_clip_gpio);

    if (!fault_state && !otw_clip_state) 
    {
        return OTE_OLP_UVP_FAULT;
    } 
    else if (!fault_state && otw_clip_state) 
    {
        return OLP_UVP_FAULT;
    } 
    else if (fault_state && !otw_clip_state) 
    {
        return OTW_WARNING;
    } 
    else 
    {
        return NORMAL_OPERATION;
        
    }
}