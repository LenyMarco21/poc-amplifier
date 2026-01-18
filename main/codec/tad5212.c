/**
 * Written by Leny Marcolini
 *
 * Driver of TAD5212 audio CODEC
 * 
 * No licence
 */

/*** Includes ***********************************************************************/

#include "tad5212.h"
#include "sys/lock.h"

#include "configurations/tad5212_common_config.h"
#include "configurations/tad5212_subwoofer_config.h"

/*** Defines ***********************************************************************/

/* I2C configuration */
#define TAD5212_I2C_READ_TIMEOUT_MS     100         /* 100ms read timeout */
#define TAD5212_I2C_WRITE_TIMEOUT_MS    -1          /* Infinite write timeout */

/*** Enumerations ***************************************************************************/

/*** Unions *********************************************************************************/

/*** Structures *****************************************************************************/

/*** Static variables ***********************************************************************/

/*** Prototypes *****************************************************************************/

/**
 * \brief Write a 1 byte value to a register of the TAD5212 device.
 * \param device Pointer to TAD5212 handle
 * \param reg Register address to write.
 * \param value Value to write to the register.
 * \return ESP_OK on success, error code otherwise.
 */
static esp_err_t write_1b_register(tad5212_handle_t* device, uint8_t reg, uint8_t value);


/**
 * \brief Write a 4 byte value to a register of the TAD5212 device.
 * \param device Pointer to TAD5212 handle
 * \param reg Register address to write.
 * \param value Value to write to the register.
 * \return ESP_OK on success, error code otherwise.
 */
static esp_err_t write_4b_register(tad5212_handle_t* device, uint8_t reg, uint32_t value);


/** 
 *  \brief Read a 1 byte register from the TAD5212 device.
 *  \param device Pointer to TAD5212 handle
 *  \param reg Register address to read.
 *  \param value Pointer to store the value read from the register.
 *  \return ESP_OK on success, error code otherwise.
 */
static esp_err_t read_1b_register(tad5212_handle_t* device, uint8_t reg, uint8_t *value);


/** 
 *  \brief Select the register page.
 *  \param device Pointer to TAD5212 handle
 *  \param page Page number to select.
 */
inline static esp_err_t select_page(tad5212_handle_t* device, uint8_t page);


/** \brief Check if a command requires a delay after execution.
 *
 *  \param reg Register address of the command.
 *  \return true if the command requires a delay, false otherwise.
 */
inline static bool cmd_requires_wait(uint8_t reg);


/** \brief Check if a page requires a 4-byte transaction.
 *
 *  \param page Page number to check.
 *  \return true if the page requires a 4-byte transaction, false otherwise.
 */
inline static bool page_requires_4bytes_transaction(uint8_t page);


/** \brief Set biquad filter coefficients
 *  \param channel Channel to set the biquad filter coefficients
 *  \param filter Biquad filter to set the coefficients
 *  \param coeffs Biquad filter coefficients
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_set_biquad_coeff(tad5212_handle_t* device, tad5212_biquad_filter_t filter, tad5212_biquad_coeffs_t coeffs);


/**
 *  \brief Set mixer coefficients
 *  \param channel Channel to set the mixer coefficients
 *  \param mixer Mixer to set the coefficients
 *  \param coeffs Mixer coefficients
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_set_mixer_coeff(tad5212_handle_t* device, tad5212_mixer_t mixer, tad5212_mixer_coeffs_t coeffs);


/*** Static functions ***********************************************************************/

/**
 * \brief Write a 1 byte value to a register of the TAD5212 device.
 * \param device Pointer to TAD5212 handle
 * \param reg Register address to write.
 * \param value Value to write to the register.
 * \return ESP_OK on success, error code otherwise.
 */
static esp_err_t write_1b_register(tad5212_handle_t* device, uint8_t reg, uint8_t value)
{
    /* Check I2C device handler pointer address */
    if (device == NULL || device->bus == NULL || device->dev == NULL)
    {
        ESP_LOGE(TAD5212_TAG, "TAD5212 device handler not initialized");
        return ESP_ERR_INVALID_ARG;
    }

    /* Write operation*/
    const uint8_t out[] = { reg, value };

    _lock_acquire(&device->lock);
    esp_err_t ret = i2c_master_transmit(device->dev, out, sizeof(out), TAD5212_I2C_WRITE_TIMEOUT_MS);
    _lock_release(&device->lock);

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "I2C write error: %s", esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}


/**
 * \brief Write a 4 byte value to a register of the TAD5212 device.
 * \param device Pointer to TAD5212 handle
 * \param reg Register address to write.
 * \param value Value to write to the register.
 * \return ESP_OK on success, error code otherwise.
 */
static esp_err_t write_4b_register(tad5212_handle_t* device, uint8_t reg, uint32_t value)
{
    /* Check I2C device handler pointer address */
    if (device == NULL || device->bus == NULL || device->dev == NULL)
    {
        ESP_LOGE(TAD5212_TAG, "TAD5212 device handler not initialized");
        return ESP_ERR_INVALID_ARG;
    }

    /* Build write sequence */
    const uint8_t out[] = 
    { 
        reg, 
        (uint8_t)(value >> 24), 
        (uint8_t)(value >> 16), 
        (uint8_t)(value >> 8), 
        (uint8_t)(value) 
    };

    /* Write operation*/
    _lock_acquire(&device->lock);
    esp_err_t ret = i2c_master_transmit(device->dev, out, sizeof(out), TAD5212_I2C_WRITE_TIMEOUT_MS);
    _lock_release(&device->lock);

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "I2C write error: %s", esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}


/** \brief Read a 1 byte register from the TAD5212 device.
 *  \param device Pointer to TAD5212 handle
 *  \param reg Register address to read.
 *  \param value Pointer to store the value read from the register.
 *  \return ESP_OK on success, error code otherwise.
 */
static esp_err_t read_1b_register(tad5212_handle_t* device, uint8_t reg, uint8_t *value)
{
    /* Check I2C device handler pointer address */
    if (device == NULL || device->bus == NULL || device->dev == NULL)
    {
        ESP_LOGE(TAD5212_TAG, "TAD5212 device handler not initialized");
        return ESP_ERR_INVALID_ARG;
    }

    /* Check value pointer address */
    if (value == NULL)
    {
        ESP_LOGE(TAD5212_TAG, "Invalid argument: value pointer is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    /* Read operation */
    const uint8_t out[] = { reg };

    _lock_acquire(&device->lock);
    esp_err_t ret = i2c_master_transmit_receive(device->dev, out, sizeof(out), value, 1, TAD5212_I2C_READ_TIMEOUT_MS);
    _lock_release(&device->lock);

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "I2C write error: %s", esp_err_to_name(ret));
        return ret;
    }

    return ret;
}


/** 
 *  \brief Select the register page.
 *  \param device Pointer to TAD5212 handle
 *  \param page Page number to select.
 */
inline static esp_err_t select_page(tad5212_handle_t* device, uint8_t page)
{
    return write_1b_register(device, REG_PAGE_CFG, page);
}


/** \brief Check if a command requires a delay after execution.
 *
 *  \param reg Register address of the command.
 *  \return true if the command requires a delay, false otherwise.
 */
inline static bool cmd_requires_wait(uint8_t reg)
{
    return (REG_SW_RESET == reg || REG_DEV_MISC_CFG == reg);
}


/** \brief Check if a page requires a 4-byte transaction.
 *
 *  \param page Page number to check.
 *  \return true if the page requires a 4-byte transaction, false otherwise.
 */
inline static bool page_requires_4bytes_transaction(uint8_t page)
{
    return (page >= TAD5212_PAGE_15);
}

/*** Public functions ***********************************************************************/


/**
 *  \brief Initialize the TAD5212 codec
 *  \param device TAD5212 device
 *  \param i2c_bus_handle I2C bus handler
 *  \param i2c_addr I2C address of the TAD5212 device
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_init(tad5212_handle_t* device, i2c_master_bus_handle_t i2c_bus_handle, tad5212_i2c_addr_t i2c_addr, tad5212_config_select_t cfg)
{
    esp_err_t status;
    
    if (device == NULL)
    {
        ESP_LOGE(TAD5212_TAG, "Device handler NULL");
        return ESP_ERR_INVALID_STATE;
    }

    /* Check device initialization state */
    if (device->initialized == true) 
    {
        ESP_LOGE(TAD5212_TAG, "Device already initialized");
        return ESP_ERR_INVALID_STATE;
    }

    _lock_init(&device->lock);

    /* Initialize I2C interface */
    if (i2c_bus_handle == NULL)
    {
        ESP_LOGE(TAD5212_TAG, "I2C bus handle NULL");
        return ESP_ERR_INVALID_ARG;
    }
    else
    {
        device->bus = i2c_bus_handle;
    }

    if (i2c_addr != TAD5212_I2C_ADDR_SHORT && 
        i2c_addr != TAD5212_I2C_ADDR_PD_4_7K &&
        i2c_addr != TAD5212_I2C_ADDR_PU_4_7K && 
        i2c_addr != TAD5212_I2C_ADDR_PU_22K)
    {
        ESP_LOGE(TAD5212_TAG, "TAD5212 I2C address unknown");
        return ESP_ERR_INVALID_ARG;
    }
    else
    {
        device->addr = i2c_addr;
    }

    /* Create device only once */
    i2c_device_config_t device_config = 
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = i2c_addr,
        .scl_speed_hz = 100000,
    };

    status = i2c_master_bus_add_device(device->bus, &device_config, &device->dev);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "I2C device init failed: %s", esp_err_to_name(status));
        return status;
    }

    /* Selects page 0 for registers adressing */
    status = select_page(device, TAD5212_PAGE_0);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to select register page 0: %s", esp_err_to_name(status));
        return status;
    }

    /* Performs software reset */
    status = write_1b_register(device, REG_SW_RESET, COMMON_CFG_SW_RESET.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write SW_RESET register: %s", esp_err_to_name(status));
        return status;
    }

    /* Delay of 10ms after reset */
    esp_rom_delay_us(10000);  

    /* Selects page 0 for registers adressing */
    status = select_page(device, TAD5212_PAGE_0);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to select register page 0: %s", esp_err_to_name(status));
        return status;
    }
    
    /* Configuration of device miscellaneous settings */
    status = write_1b_register(device, REG_DEV_MISC_CFG, COMMON_CFG_DEV_MISC_CFG_P0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write DEV_MISC_CFG register: %s", esp_err_to_name(status));
        return status;
    }

    /* Delay of 10 ms for AREG and VREF to stabilize */
    esp_rom_delay_us(10000);  

    /* Configuration of the device DAC de-pop */
    status = write_1b_register(device, REG_DAC_CFG_A0, COMMON_CFG_DAC_CFG_A0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write DAC_CFG_A0 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of the device DAC de-pop 2 */
    status = write_1b_register(device, REG_MISC_CFG0, COMMON_CFG_MISC_CFG0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write MISC_CFGG0 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of DOUT output */
    status = write_1b_register(device, REG_INTF_CFG1, COMMON_CFG_INTF_CFG1.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write INTF_CFG1 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of data inputs MUX ASI */
    status = write_1b_register(device, REG_ASI_CFG1, COMMON_CFG_ASI_CFG1.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write ASI_CFG1 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of Primary Audio Serial Interface */
    status = write_1b_register(device, REG_PASI_CFG0, COMMON_CFG_PASI_CFG0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write PASI_CFG0 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of Primary Audio Serial Interface RX Channel 1 */
    status = write_1b_register(device, REG_PASI_RX_CH1_CFG, COMMON_CFG_PASI_RX_CH1_CFG.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write PASI_RX_CH1_CFG register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of Primary Audio Serial Interface RX Channel 2 */
    status = write_1b_register(device, REG_PASI_RX_CH2_CFG, COMMON_CFG_PASI_RX_CH2_CFG.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write PASI_RX_CH2_CFG register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of DAC Channel 1 */
    status = write_1b_register(device, REG_OUT1X_CFG0, COMMON_CFG_OUT1X_CFG0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write OUT1X_CFG0 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of DAC Channel 1 OUT1P as line out driver */
    status = write_1b_register(device, REG_OUT1X_CFG1, COMMON_CFG_OUT1X_CFG1.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write OUT1X_CFG1 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of DAC Channel 1 OUT1M as line out driver */
    status = write_1b_register(device, REG_OUT1X_CFG2, COMMON_CFG_OUT1X_CFG2.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write OUT1X_CFG2 register: %s", esp_err_to_name(status));
        return status;
    }

    /* DAC 1 Volume configuration set to mute */
    status = write_1b_register(device, REG_DAC_CH1A_CFG0, COMMON_CFG_DAC_CH1A_CFG0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write DAC_CH1A_CFG0 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of DAC Channel 2 */
    status = write_1b_register(device, REG_OUT2X_CFG0, COMMON_CFG_OUT2X_CFG0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write OUT2X_CFG0 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of DAC Channel 2 OUT2P as line out driver */
    status = write_1b_register(device, REG_OUT2X_CFG1, COMMON_CFG_OUT2X_CFG1.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write OUT2X_CFG1 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Configuration of DAC Channel 2 OUT2M as line out driver */
    status = write_1b_register(device, REG_OUT2X_CFG2, COMMON_CFG_OUT2X_CFG2.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write OUT2X_CFG2 register: %s", esp_err_to_name(status));
        return status;
    }

    /* DAC 2 Volume configuration set to mute */
    status = write_1b_register(device, REG_DAC_CH2A_CFG0, COMMON_CFG_DAC_CH2A_CFG0.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write DAC_CH2A_CFG0 register: %s", esp_err_to_name(status));
        return status;
    }

    /* Subwoofer configuration settings load */
    if (cfg == TAD5212_CONFIG_SUBWOOFER) 
    {
        /* Selects page 1 for registers adressing */
        status = select_page(device, TAD5212_PAGE_1);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to select register page 1: %s", esp_err_to_name(status));
            return status;
        }

        /* DSP configuration */
        status = write_1b_register(device, REG_MIXER_CFG0, SUBWOOFER_CFG_MIXER_CFG0.data);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to write SUBWOOFER_CFG_MIXER_CFG0 register: %s", esp_err_to_name(status));
            return status;
        }

        /* Mixer configuration */
        status = tad5212_set_mixer_coeff(device, TAD5212_ASI_DIN_MIX_ASI_CH1, TAD5212_MIXER_RDAC_DIV_2);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load mixer L channel gain settings: %s", esp_err_to_name(status));
            return status;
        }

        status = tad5212_set_mixer_coeff(device, TAD5212_ASI_DIN_MIX_ASI_CH2, TAD5212_MIXER_RDAC_DIV_2);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load mixer R channel gain settings: %s", esp_err_to_name(status));
            return status;
        }

        /* Biquad filters configuration */
        status = tad5212_set_biquad_coeff(device, TAD5212_DAC2_BIQUAD_FILTER_1, TAD5212_BIQUAD_LOWPASS_150_HZ);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load biquad filter settings: %s", esp_err_to_name(status));
            return status;
        }

        status = tad5212_set_biquad_coeff(device, TAD5212_DAC2_BIQUAD_FILTER_2, TAD5212_BIQUAD_LOWPASS_150_HZ);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load biquad filter settings: %s", esp_err_to_name(status));
            return status;
        }

        /* Selects page 0 for registers adressing */
        status = select_page(device, TAD5212_PAGE_0);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to select register page 0: %s", esp_err_to_name(status));
            return status;
        }

        /* Enable DAC2 channel */
        status = write_1b_register(device, REG_CH_EN, SUBWOOFER_CFG_CH_EN.data);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to write CH_EN register: %s", esp_err_to_name(status));
            return status;
        }

        ESP_LOGE(TAD5212_TAG, "Subwoofer config done: %s", esp_err_to_name(status));
    }

    /* Basic configuration settings load (2x 2-way speakers) */
    else
    {
        /* Biquad filters configuration */

        status = tad5212_set_biquad_coeff(device, TAD5212_DAC1_BIQUAD_FILTER_1, TAD5212_BIQUAD_HIGHPASS_150_HZ);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load biquad filter settings: %s", esp_err_to_name(status));
            return status;
        }

        status = tad5212_set_biquad_coeff(device, TAD5212_DAC1_BIQUAD_FILTER_1, TAD5212_BIQUAD_LOWPASS_16000_HZ);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load biquad filter settings: %s", esp_err_to_name(status));
            return status;
        }

        status = tad5212_set_biquad_coeff(device, TAD5212_DAC2_BIQUAD_FILTER_1, TAD5212_BIQUAD_HIGHPASS_150_HZ);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load biquad filter settings: %s", esp_err_to_name(status));
            return status;
        }

        status = tad5212_set_biquad_coeff(device, TAD5212_DAC2_BIQUAD_FILTER_1, TAD5212_BIQUAD_LOWPASS_16000_HZ);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to load biquad filter settings: %s", esp_err_to_name(status));
            return status;
        }

        /* Selects page 0 for registers adressing */
        status = select_page(device, TAD5212_PAGE_0);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to select register page 0: %s", esp_err_to_name(status));
            return status;
        }

        /* Enable DAC1 & DAC2 channels */
        status = write_1b_register(device, REG_CH_EN, COMMON_CFG_CH_EN.data);
        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to write CH_EN register: %s", esp_err_to_name(status));
            return status;
        }
    }

    /* Power up the device */
    status = write_1b_register(device, REG_PWR_CFG, COMMON_CFG_PWR_CFG.data);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write PWR_CFG register: %s", esp_err_to_name(status));
        return status;
    }

    /* End of initialization */
    device->initialized = true;

    return ESP_OK;
}


 /**
  *  \brief Deinitialize the TAD5212 codec
  *  \param device TAD5212 device
  *  \return ESP_OK on success, error code otherwise.
  */
esp_err_t tad5212_deinit(tad5212_handle_t* device)
{
    /* Check I2C bus initialization state */
    if (device == NULL || device->initialized == false) 
    {
        ESP_LOGE(TAD5212_TAG, "Device already deinitialized");
        return ESP_ERR_INVALID_STATE;
    }

    /* Check I2C bus initialization state */
    if (device->dev != NULL && device->bus != NULL)
    {
        i2c_master_bus_rm_device(device->dev);
        device->dev = NULL;
        i2c_del_master_bus(device->bus);
        device->bus = NULL;
    }
    else
    {
        ESP_LOGW(TAD5212_TAG, "Device or bus handle is NULL");
        return ESP_ERR_INVALID_STATE;
    }

    /* End of deinitialization */
    device->initialized = false;

    return ESP_OK;
}


/** \brief Set biquad filter coefficients
 *  \param device TAD5212 device
 *  \param filter Biquad filter to set the coefficients
 *  \param coeffs Biquad filter coefficients
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_set_biquad_coeff(tad5212_handle_t* device, tad5212_biquad_filter_t filter, tad5212_biquad_coeffs_t coeffs)
{
    esp_err_t status;
    uint8_t reg_addr;
    uint8_t page;

    /* Check device handler */
    if (device == NULL) 
    {
        ESP_LOGE(TAD5212_TAG, "Device already deinitialized");
        return ESP_ERR_INVALID_STATE;
    }

    /* Select register address depending on channel */
    switch (filter)
    {
        case TAD5212_DAC1_BIQUAD_FILTER_1:
            page = TAD5212_PAGE_15;
            reg_addr = REG_DAC_BQ1_N0_B1;
            break;

        case TAD5212_DAC2_BIQUAD_FILTER_1:
            page = TAD5212_PAGE_15;
            reg_addr = REG_DAC_BQ2_N0_B1;
            break;

        case TAD5212_DAC1_BIQUAD_FILTER_2:
            page = TAD5212_PAGE_15;
            reg_addr = REG_DAC_BQ5_N0_B1;
            break;

        case TAD5212_DAC2_BIQUAD_FILTER_2:
            page = TAD5212_PAGE_15;
            reg_addr = REG_DAC_BQ6_N0_B1;
            break;

        case TAD5212_DAC1_BIQUAD_FILTER_3:
            page = TAD5212_PAGE_16;
            reg_addr = REG_DAC_BQ9_N0_B1;
            break;

        case TAD5212_DAC2_BIQUAD_FILTER_3:
            page = TAD5212_PAGE_16;
            reg_addr = REG_DAC_BQ10_N0_B1;
            break;

        default:
            return ESP_ERR_INVALID_ARG;
    }

    /* Selects page for registers addressing */
    status = select_page(device, page);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to select register page %d: %s", page, esp_err_to_name(status));
        return status;
    }

    /* Write biquad coefficients */
    status = write_4b_register(device, reg_addr, coeffs.n0.value);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write biquad coefficient N0: %s", esp_err_to_name(status));
        return status;
    }

    status = write_4b_register(device, reg_addr + 4, coeffs.n1.value);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write biquad coefficients N1: %s", esp_err_to_name(status));
        return status;
    }

    status = write_4b_register(device, reg_addr + 8, coeffs.n2.value);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write biquad coefficients N2: %s", esp_err_to_name(status));
        return status;
    }

    status = write_4b_register(device, reg_addr + 12, coeffs.d1.value);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write biquad coefficients D1: %s", esp_err_to_name(status));
        return status;
    }

    status = write_4b_register(device, reg_addr + 16, coeffs.d2.value);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write biquad coefficients D2: %s", esp_err_to_name(status));
        return status;
    }

    return ESP_OK;
}

/**
 *  \brief Set mixer coefficients
 *  \param device TAD5212 device
 *  \param mixer Mixer to set the coefficients
 *  \param coeffs Mixer coefficients
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_set_mixer_coeff(tad5212_handle_t* device, tad5212_mixer_t mixer, tad5212_mixer_coeffs_t coeffs)
{
    esp_err_t status;
    uint8_t reg_addr;

    /* Check device handler */
    if (device == NULL) 
    {
        ESP_LOGE(TAD5212_TAG, "Device already deinitialized");
        return ESP_ERR_INVALID_STATE;
    }

    /* Select register address depending on channel */
    switch (mixer)
    {
        case TAD5212_ASI_DIN_MIX_ASI_CH1:
            reg_addr = REG_ASI_DIN_MIX_ASI_CH1_RDAC_MIX_BYT1;
            break;

        case TAD5212_ASI_DIN_MIX_ASI_CH2:
            reg_addr = REG_ASI_DIN_MIX_ASI_CH2_RDAC_MIX_BYT1;
            break;

        default:
            return ESP_ERR_INVALID_ARG;
    }

    /* Selects page for registers addressing */
    status = select_page(device, TAD5212_PAGE_17);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to select register page %d: %s", TAD5212_PAGE_17, esp_err_to_name(status));
        return status;
    }

    /* Write mixer coefficients */
    status = write_4b_register(device, reg_addr, (uint32_t)(coeffs.a2.value << 16) + coeffs.a1.value);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write mixer coefficient A2 + A1: %s", esp_err_to_name(status));
        return status;
    }

    status = write_4b_register(device, reg_addr + 4, (uint32_t)(coeffs.a4.value << 16) + coeffs.a3.value);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write mixer coefficient A4 + A3: %s", esp_err_to_name(status));
        return status;
    }

    return ESP_OK;
}

/**
 *  \brief Set the volume of the TAD5212 codec
 *  \param device TAD5212 device
 *  \param channel Channel to set volume
 *  \param volume Volume level (0-100)
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_set_volume(tad5212_handle_t* device, tad5212_channel_t channel, uint8_t volume)
{
    /* Check device handler */
    if (device == NULL || device->initialized == false) 
    {
        ESP_LOGE(TAD5212_TAG, "Device already deinitialized");
        return ESP_ERR_INVALID_STATE;
    }

    // Clamping volume to valid range
    if (volume > 100) volume = 100;

    // Converting volume from percentage (0-100) to register value with respect to step and min volume
    uint8_t dvol_value = 0;
    
    // If volume is 0 then the device is muted
    if (volume != 0)
    {
        dvol_value = TAD5212_DAC_MIN_VOLUME + (uint8_t)(TAD5212_DAC_VOLUME_STEP * volume);
    }

    // Write volume to the selected channel(s)
    esp_err_t status;

    if (channel == TAD5212_CHANNEL_LEFT || channel == TAD5212_CHANNEL_BOTH) 
    {
        /* DAC 1 Volume configuration set to mute */
        tad5212_REG_DAC_CH1A_CFG0_t dac_ch1a_cfg0 = 
        {
            .dac_ch1a_dvol = dvol_value,  /* Channel 1A digital volume control */
        };

        status = write_1b_register(device, REG_DAC_CH1A_CFG0, dac_ch1a_cfg0.data);

        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to write DAC_CH1A_CFG0 register: %s", esp_err_to_name(status));
            return status;
        }
    }

    if (channel == TAD5212_CHANNEL_RIGHT || channel == TAD5212_CHANNEL_BOTH) 
    {
        /* DAC 2 Volume configuration set to mute */
        tad5212_REG_DAC_CH2A_CFG0_t dac_ch2a_cfg0 = 
        {
            .dac_ch2a_dvol = dvol_value,  /* Channel 2A digital volume control */
        };

        status = write_1b_register(device, REG_DAC_CH2A_CFG0, dac_ch2a_cfg0.data);

        if (status != ESP_OK)
        {
            ESP_LOGE(TAD5212_TAG, "Failed to write DAC_CH2A_CFG0 register: %s", esp_err_to_name(status));
            return status;
        }
    }

    return ESP_OK;
}

/**
 *  \brief Swap OUT1 & OUT2 channels of the TAD5212 codec
 *  \param device TAD5212 device
 *  \return ESP_OK on success, error code otherwise.
 */
esp_err_t tad5212_swap_channels(tad5212_handle_t* device)
{
    /* Check device handler */
    if (device == NULL || device->initialized == false) 
    {
        ESP_LOGE(TAD5212_TAG, "Device already deinitialized");
        return ESP_ERR_INVALID_STATE;
    }

    /* Reading of current register value */
    uint8_t reg_value = 0;
    esp_err_t status = read_1b_register(device, REG_DYN_PUPD_CFG, &reg_value);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read DYN_PUPD_CFG register: %s", esp_err_to_name(status));
        return status;
    }

    /* Invert dac_ch_swap bit */
    ((tad5212_REG_DYN_PUPD_CFG_t*)&reg_value)->dac_ch_swap ^= 0x1;

    /* Write the modified register value back */
    status = write_1b_register(device, REG_DYN_PUPD_CFG, reg_value);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to write DYN_PUPD_CFG register: %s", esp_err_to_name(status));
        return status;
    }

    return ESP_OK;
}

#ifdef TAD5212_DEBUG

/**
  *  \brief Get the status of the TAD5212 DAC channels
  *  \param device TAD5212 device
  *  \return ESP_OK on success, error code otherwise.
  */
esp_err_t tad5212_dac_status(tad5212_handle_t* device)
{
    /* Check device handler */
    if (device == NULL || device->initialized == false) 
    {
        ESP_LOGE(TAD5212_TAG, "Device already deinitialized");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAD5212_TAG, "=====================================");
    ESP_LOGI(TAD5212_TAG, "TAD5212 : 0x%02x - LOG", device->addr);
    ESP_LOGI(TAD5212_TAG, "=====================================");

    uint8_t reg_value_1;

    esp_err_t status = read_1b_register(device, REG_DEV_STS0, &reg_value_1);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read DEV_STS0 register: %s", esp_err_to_name(status));
        return status;
    }

    ESP_LOGI(TAD5212_TAG, "DAC Channel 1 : %s", (((tad5212_REG_DEV_STS0_t)reg_value_1).out_ch2_status ? "ON" : "OFF"));
    ESP_LOGI(TAD5212_TAG, "DAC Channel 2 : %s", (((tad5212_REG_DEV_STS0_t)reg_value_1).out_ch1_status ? "ON" : "OFF"));

    uint8_t reg_value_2;

    status = read_1b_register(device, REG_DEV_STS1, &reg_value_2);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read DEV_STS1 register: %s", esp_err_to_name(status));
        return status;
    }

    switch(((tad5212_REG_DEV_STS1_t)reg_value_2).mode_sts)
    {
        case 4:
            ESP_LOGI(TAD5212_TAG, "Device Mode : IDLE");
            break;

        case 6:
            ESP_LOGI(TAD5212_TAG, "Device Mode : WAITING FOR AUDIO");
            break;

        case 7:
            ESP_LOGI(TAD5212_TAG, "Device Mode : PLAYING SOUND");
            break;

        default:
            ESP_LOGI(TAD5212_TAG, "Device Mode : UNKNOWN");
            break;
    }

    ESP_LOGI(TAD5212_TAG, "PLL Status: %s", (((tad5212_REG_DEV_STS1_t)reg_value_2).pll_sts ? "LOCKED" : "NOT LOCKED"));

    uint8_t reg_value_3;

    status = read_1b_register(device, REG_CLK_ERR_STS0, &reg_value_3);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read CLK_ERR_STS0 register: %s", esp_err_to_name(status));
        return status;
    }

    ESP_LOGI(TAD5212_TAG, "RESET_ON_CLK_STOP_DET_STS: %s", (((tad5212_REG_CLK_ERR_STS0_t)reg_value_3).reset_on_clk_stop_det_sts ? "ERROR" : "NO ERROR"));
    ESP_LOGI(TAD5212_TAG, "PDM_CLK_ERR: %s",
                (((tad5212_REG_CLK_ERR_STS0_t)reg_value_3).pdm_clk_err ? "ERROR" : "NO ERROR"));
    ESP_LOGI(TAD5212_TAG, "DEM_RATE_ERR: %s",
                (((tad5212_REG_CLK_ERR_STS0_t)reg_value_3).dem_rate_err ? "ERROR" : "NO ERROR"));
    ESP_LOGI(TAD5212_TAG, "SRC_RATIO_ERR: %s",
                (((tad5212_REG_CLK_ERR_STS0_t)reg_value_3).src_ratio_err ? "ERROR" : "NO ERROR"));
    ESP_LOGI(TAD5212_TAG, "DSP_CLK_ERROR: %s",
                (((tad5212_REG_CLK_ERR_STS0_t)reg_value_3).dsp_clk_err ? "ERROR" : "NO ERROR"));

    uint8_t reg_value_4;

    status = read_1b_register(device, REG_CLK_ERR_STS1, &reg_value_4);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read CLK_ERR_STS1 register: %s", esp_err_to_name(status));
        return status;
    }

    ESP_LOGI(TAD5212_TAG, "Clock Error Status 1: %d", reg_value_4);
    ESP_LOGI(TAD5212_TAG, "PASI_FS_ERR: %s",
                (((tad5212_REG_CLK_ERR_STS1_t)reg_value_4).pasi_fs_err ? "ERROR" : "NO ERROR"));
    ESP_LOGI(TAD5212_TAG, "CCLK_FS_RATIO_ERR: %s",
                (((tad5212_REG_CLK_ERR_STS1_t)reg_value_4).cclk_fs_ratio_err ? "ERROR" : "NO ERROR"));
    ESP_LOGI(TAD5212_TAG, "PASI_BCLK_FS_RATIO_ERR: %s",
                (((tad5212_REG_CLK_ERR_STS1_t)reg_value_4).pasi_bclk_fs_ratio_err ? "ERROR" : "NO ERROR"));


    uint8_t reg_value_5;

    status = read_1b_register(device, REG_CLK_DET_STS0, &reg_value_5);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read CLK_DET_STS0 register: %s", esp_err_to_name(status));
        return status;
    }

    ESP_LOGI(TAD5212_TAG, "PASI_SAMP_RATE_STS: %d", ((tad5212_REG_CLK_DET_STS0_t)reg_value_5).pasi_samp_rate_sts);

    uint8_t reg_value_6;

    status = read_1b_register(device, REG_CLK_DET_STS2, &reg_value_6);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read CLK_DET_STS2 register: %s", esp_err_to_name(status));
        return status;
    }

    uint8_t reg_value_7;

    status = read_1b_register(device, REG_CLK_DET_STS3, &reg_value_7);

    if (status != ESP_OK)
    {
        ESP_LOGE(TAD5212_TAG, "Failed to read CLK_DET_STS3 register: %s", esp_err_to_name(status));
        return status;
    }

    ESP_LOGI(TAD5212_TAG, "CLK RATIO : %d", ((reg_value_6 & 0x3F << 8) | reg_value_7));

    return ESP_OK;
}

#endif
