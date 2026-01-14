/*
 * SPDX-FileCopyrightText: 2021-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

 /*** Includes *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"

#include "esp_bt.h"
#include "bt_app_core.h"
#include "bt_app_av.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "esp_avrc_api.h"

#include "driver/gpio.h"
#include "codec/tad5212.h"
#include "amplifier/tpa3255.h"

/*** Defines *******************************************************************/

#define MAIN_TAG    "MAIN"
#define A2DP_TAG    "A2DP"
#define AVRCP_TAG   "AVRCP"

#define MAIN_TICK_DELAY_MS              10
#define DEBUG_PRINT_DELAY_MS            500

/* Pins definition */
#define SUBWOOFER_AMP_RESET_GPIO        GPIO_NUM_33
#define SUBWOOFER_AMP_FAULT_GPIO        GPIO_NUM_34
#define SUBWOOFER_AMP_OTW_CLIP_GPIO     GPIO_NUM_35

#define SPEAKER_AMP_RESET_GPIO          GPIO_NUM_33
#define SPEAKER_AMP_FAULT_GPIO          GPIO_NUM_34
#define SPEAKER_AMP_OTW_CLIP_GPIO       GPIO_NUM_35

#define I2C0_SDA_GPIO                   GPIO_NUM_21     /* GPIO number for I2C SDA */
#define I2C0_SCL_GPIO                   GPIO_NUM_22     /* GPIO number for I2C SCL */

/* I2C configuration */
#define I2C0_FREQUENCY                  100000          /* 100kHz I2C frequency */
#define I2C0_PORT                       I2C_NUM_0       /* I2C port number */

/* Codec I2C addresses */
#define TAD5212_I2C_ADDRESS_SUBWOOFER   TAD5212_I2C_ADDR_SHORT
#define TAD5212_I2C_ADDRESS_SPEAKERS    TAD5212_I2C_ADDR_PD_4_7K

/*** Static variables *******************************************************************/

/* device name */
static const char local_device_name[] = "Symphony 2.1";

/* I2C0 bus handle */
static i2c_master_bus_handle_t I2C0_bus_handle;

/* TAD5212 for subwoofer */
static tad5212_handle_t subwoofer_codec;

/* TAD5212 for 2-way speakers */
static tad5212_handle_t speakers_codec;

/* TPA3255 for subwoofer */
static tpa3255_device_t subwoofer_amplifier;

/* TPA3255 for speakers */
static tpa3255_device_t speaker_amplifier;

/*** Enumerations *********************************************************************/

/* event for stack up */
enum 
{
    BT_APP_EVT_STACK_UP = 0,
};

/*** Static prototypes *******************************************************************/

/* Device callback function */
static void bt_app_dev_cb(esp_bt_dev_cb_event_t event, esp_bt_dev_cb_param_t *param);

/* GAP callback function */
static void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

/* handler for bluetooth stack enabled events */
static void bt_av_hdl_stack_evt(uint16_t event, void *p_param);

/*** Static functions *******************************************************************/

static char *bda2str(uint8_t * bda, char *str, size_t size)
{
    if (bda == NULL || str == NULL || size < 18) {
        return NULL;
    }

    uint8_t *p = bda;
    sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
            p[0], p[1], p[2], p[3], p[4], p[5]);
    return str;
}

static void bt_app_dev_cb(esp_bt_dev_cb_event_t event, esp_bt_dev_cb_param_t *param)
{
    switch (event) {
    case ESP_BT_DEV_NAME_RES_EVT: {
        if (param->name_res.status == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(BT_AV_TAG, "Get local device name success: %s", param->name_res.name);
        } else {
            ESP_LOGE(BT_AV_TAG, "Get local device name failed, status: %d", param->name_res.status);
        }
        break;
    }
    default: {
        ESP_LOGI(BT_AV_TAG, "event: %d", event);
        break;
    }
    }
}


static void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    uint8_t *bda = NULL;

    switch (event) {
    /* when authentication completed, this event comes */
    case ESP_BT_GAP_AUTH_CMPL_EVT: {
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(BT_AV_TAG, "authentication success: %s", param->auth_cmpl.device_name);
            ESP_LOG_BUFFER_HEX(BT_AV_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
        } else {
            ESP_LOGE(BT_AV_TAG, "authentication failed, status: %d", param->auth_cmpl.stat);
        }
        ESP_LOGI(BT_AV_TAG, "link key type of current link is: %d", param->auth_cmpl.lk_type);
        break;
    }
    case ESP_BT_GAP_ENC_CHG_EVT: {
        char *str_enc[3] = {"OFF", "E0", "AES"};
        bda = (uint8_t *)param->enc_chg.bda;
        ESP_LOGI(BT_AV_TAG, "Encryption mode to [%02x:%02x:%02x:%02x:%02x:%02x] changed to %s",
                 bda[0], bda[1], bda[2], bda[3], bda[4], bda[5], str_enc[param->enc_chg.enc_mode]);
        break;
    }

#if (CONFIG_EXAMPLE_A2DP_SINK_SSP_ENABLED == true)
    /* when Security Simple Pairing user confirmation requested, this event comes */
    case ESP_BT_GAP_CFM_REQ_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %06"PRIu32, param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    /* when Security Simple Pairing passkey notified, this event comes */
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey: %06"PRIu32, param->key_notif.passkey);
        break;
    /* when Security Simple Pairing passkey requested, this event comes */
    case ESP_BT_GAP_KEY_REQ_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
        break;
#endif

    /* when GAP mode changed, this event comes */
    case ESP_BT_GAP_MODE_CHG_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_MODE_CHG_EVT mode: %d, interval: %.2f ms",
                 param->mode_chg.mode, param->mode_chg.interval * 0.625);
        break;
    /* when ACL connection completed, this event comes */
    case ESP_BT_GAP_ACL_CONN_CMPL_STAT_EVT:
        bda = (uint8_t *)param->acl_conn_cmpl_stat.bda;
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_ACL_CONN_CMPL_STAT_EVT Connected to [%02x:%02x:%02x:%02x:%02x:%02x], status: 0x%x",
                 bda[0], bda[1], bda[2], bda[3], bda[4], bda[5], param->acl_conn_cmpl_stat.stat);
        break;
    /* when ACL disconnection completed, this event comes */
    case ESP_BT_GAP_ACL_DISCONN_CMPL_STAT_EVT:
        bda = (uint8_t *)param->acl_disconn_cmpl_stat.bda;
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_ACL_DISC_CMPL_STAT_EVT Disconnected from [%02x:%02x:%02x:%02x:%02x:%02x], reason: 0x%x",
                 bda[0], bda[1], bda[2], bda[3], bda[4], bda[5], param->acl_disconn_cmpl_stat.reason);
        break;
    /* others */
    default: {
        ESP_LOGI(BT_AV_TAG, "event: %d", event);
        break;
    }
    }
}

static void bt_av_hdl_stack_evt(uint16_t event, void *p_param)
{
    ESP_LOGD(BT_AV_TAG, "%s event: %d", __func__, event);

    switch (event) {
    /* when do the stack up, this event comes */
    case BT_APP_EVT_STACK_UP: {
        esp_bt_gap_set_device_name(local_device_name);
        esp_bt_dev_register_callback(bt_app_dev_cb);
        esp_bt_gap_register_callback(bt_app_gap_cb);

        esp_avrc_ct_register_callback(bt_app_rc_ct_cb);
        assert(esp_avrc_ct_init() == ESP_OK);
        esp_avrc_tg_register_callback(bt_app_rc_tg_cb);
        assert(esp_avrc_tg_init() == ESP_OK);

        esp_avrc_rn_evt_cap_mask_t evt_set = {0};
        esp_avrc_rn_evt_bit_mask_operation(ESP_AVRC_BIT_MASK_OP_SET, &evt_set, ESP_AVRC_RN_VOLUME_CHANGE);
        assert(esp_avrc_tg_set_rn_evt_cap(&evt_set) == ESP_OK);

        esp_a2d_register_callback(&bt_app_a2d_cb);
        assert(esp_a2d_sink_init() == ESP_OK);

#if CONFIG_EXAMPLE_A2DP_SINK_USE_EXTERNAL_CODEC == FALSE
        esp_a2d_sink_register_data_callback(bt_app_a2d_data_cb);
#else
        esp_a2d_mcc_t mcc = {0};
        mcc.type = ESP_A2D_MCT_SBC;
        mcc.cie.sbc_info.samp_freq = 0xf;
        mcc.cie.sbc_info.ch_mode = 0xf;
        mcc.cie.sbc_info.block_len = 0xf;
        mcc.cie.sbc_info.num_subbands = 0x3;
        mcc.cie.sbc_info.alloc_mthd = 0x3;
        mcc.cie.sbc_info.max_bitpool = 250;
        mcc.cie.sbc_info.min_bitpool = 2;
        /* register stream end point, only support mSBC currently */
        esp_a2d_sink_register_stream_endpoint(0, &mcc);
        esp_a2d_sink_register_audio_data_callback(bt_app_a2d_audio_data_cb);
#endif
        /* Get the default value of the delay value */
        esp_a2d_sink_get_delay_value();
        /* Get local device name */
        esp_bt_gap_get_device_name();

        /* set discoverable and connectable mode, wait to be connected */
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        break;
    }
    /* others */
    default:
        ESP_LOGE(BT_AV_TAG, "%s unhandled event: %d", __func__, event);
        break;
    }
}

/*******************************
 * MAIN ENTRY POINT
 ******************************/

void app_main(void)
{
    char bda_str[18] = {0};
    /* initialize NVS — it is used to store PHY calibration data */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    bt_app_av_init();

    /*
     * This example only uses the functions of Classical Bluetooth.
     * So release the controller memory for Bluetooth Low Energy.
     */
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((err = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(BT_AV_TAG, "%s initialize controller failed: %s", __func__, esp_err_to_name(err));
        return;
    }
    if ((err = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
        ESP_LOGE(BT_AV_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    esp_bluedroid_config_t bluedroid_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
#if (CONFIG_EXAMPLE_A2DP_SINK_SSP_ENABLED == false)
    bluedroid_cfg.ssp_en = false;
#endif
    if ((err = esp_bluedroid_init_with_cfg(&bluedroid_cfg)) != ESP_OK) {
        ESP_LOGE(BT_AV_TAG, "%s initialize bluedroid failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    if ((err = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(BT_AV_TAG, "%s enable bluedroid failed: %s", __func__, esp_err_to_name(err));
        return;
    }

#if (CONFIG_EXAMPLE_A2DP_SINK_SSP_ENABLED == true)
    /* set default parameters for Secure Simple Pairing */
    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IO;
    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));
#endif

    /* set default parameters for Legacy Pairing (use fixed pin code 1234) */
    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_FIXED;
    esp_bt_pin_code_t pin_code;
    pin_code[0] = '1';
    pin_code[1] = '2';
    pin_code[2] = '3';
    pin_code[3] = '4';
    esp_bt_gap_set_pin(pin_type, 4, pin_code);

    ESP_LOGI(BT_AV_TAG, "Own address:[%s]", bda2str((uint8_t *)esp_bt_dev_get_address(), bda_str, sizeof(bda_str)));
    bt_app_task_start_up();

    /* bluetooth device name, connection mode and profile set up */
    bt_app_work_dispatch(bt_av_hdl_stack_evt, BT_APP_EVT_STACK_UP, NULL, 0, NULL);

    /* Initialize subwoofer amplifier */
    if (tpa3255_gpio_init(&subwoofer_amplifier, SUBWOOFER_AMP_RESET_GPIO, SUBWOOFER_AMP_FAULT_GPIO, SUBWOOFER_AMP_OTW_CLIP_GPIO) != ESP_OK)
    {
        ESP_LOGE(BT_AV_TAG, "Failed to initialize audio amplifiers");
    }
    else
    {
        ESP_LOGI(BT_AV_TAG, "Audio amplifiers initialized successfully");
    }

    /* Initialize speaker amplifier */
    if (tpa3255_gpio_init(&speaker_amplifier, SPEAKER_AMP_RESET_GPIO, SPEAKER_AMP_FAULT_GPIO, SPEAKER_AMP_OTW_CLIP_GPIO) != ESP_OK) 
    {
        ESP_LOGE(BT_AV_TAG, "Failed to initialize Speaker amplifier GPIOs");
    }
    else
    {
        ESP_LOGI(BT_AV_TAG, "Speaker amplifier GPIOs initialized successfully");
    }

    /* Delay of 200 ms after power-up before accessing the device */
    esp_rom_delay_us(200000); 

    /* Initialize I2C0 bus */
    //I2C0_bus_handle = i2c_master_bus_create(I2C_NUM_0, I2C0_FREQUENCY, I2C0_SDA, I2C0_SCL);

    /* Initialize TAD5212 Subwoofer codec */


    tad5212_i2c_addr_t subwoofer_i2c_addr = TAD5212_I2C_ADDRESS_SUBWOOFER;

    if (tad5212_init(I2C0_PORT, I2C0_SDA_GPIO, I2C0_SCL_GPIO, I2C0_FREQUENCY, subwoofer_i2c_addr) != ESP_OK) 
    {
        ESP_LOGE(BT_AV_TAG, "Failed to initialize Subwoofer codec");
    }
    else
    {
        ESP_LOGI(BT_AV_TAG, "Subwoofer codec initialized successfully");
    }

    /* Initialize TAD5212 Speakers codec */
    /*
    tad5212_i2c_addr_t speakers_i2c_addr = TAD5212_I2C_ADDRESS_SPEAKERS;

    if (tad5212_init(I2C0_PORT, I2C0_SDA_GPIO, I2C0_SCL_GPIO, I2C0_FREQUENCY, speakers_i2c_addr) != ESP_OK) 
    {
        ESP_LOGE(BT_AV_TAG, "Failed to initialize Speakers codec");
    }
    else
    {
        ESP_LOGI(BT_AV_TAG, "Speakers codec initialized successfully");
    }
*/
    while(1) 
    {
        static uint8_t previous_volume = 0;
        static bt_audio_state_t previous_audio_state = BT_AUDIO_STOPPED;

        #ifdef TAD5212_DEBUG
        static uint32_t debug_tick_count = 0;
        if (debug_tick_count < DEBUG_PRINT_DELAY_MS / MAIN_TICK_DELAY_MS)
            debug_tick_count++;
        else
        {
            debug_tick_count = 0;
            tad5212_dac_status();
        }
        #endif

        // Check amplifiers status
        tpa3255_fault_flags_t fault_status = tpa3255_gpio_get_status(&subwoofer_amplifier);

        switch (fault_status)
        {
            case OTE_OLP_UVP_FAULT:
                ESP_LOGE(TPA3255_TAG, "SUBWOOFER AMP Fault: Over Temperature/Over Load/Under Voltage Protection");
                break; 

            case OLP_UVP_FAULT:
                ESP_LOGE(TPA3255_TAG, "SUBWOOFER AMP Fault: Over Load/Under Voltage Protection");
                break;

            case OTW_WARNING:
                bt_volume_set_by_local_host(0x3F); // Reduce volume to 50%
                previous_volume = 0x3F; 
                ESP_LOGW(TPA3255_TAG, "SUBWOOFER AMP Warning: Over Temperature/Clipping - Volume Reduced to 50%%");
                break;

            default:
                break;

        }

        fault_status = tpa3255_gpio_get_status(&speaker_amplifier);

        switch (fault_status)
        {
            case OTE_OLP_UVP_FAULT:
                ESP_LOGE(TPA3255_TAG, "SPEAKER AMP Fault: Over Temperature/Over Load/Under Voltage Protection");
                break; 

            case OLP_UVP_FAULT:
                ESP_LOGE(TPA3255_TAG, "SPEAKER AMP Fault: Over Load/Under Voltage Protection");
                break;

            case OTW_WARNING:
                bt_volume_set_by_local_host(0x3F); // Reduce volume to 50%
                previous_volume = 0x3F; 
                ESP_LOGW(TPA3255_TAG, "SPEAKER AMP Warning: Over Temperature/Clipping - Volume Reduced to 50%%");
                break;

            default:
                break;

        }

        /* Polling on volume change */
        uint8_t volume = bt_app_get_volume();

        /* Polling on audio state change */
        bt_audio_state_t audio_state = bt_app_get_audio_state();

        if (audio_state == BT_AUDIO_PLAYING)
        {
            if (volume != previous_volume)
            {
                uint16_t normalized_vol = volume * 100 / 0x7f;
                tad5212_set_volume(TAD5212_CHANNEL_BOTH, normalized_vol);
                previous_volume = volume;
            }
        }

        /* De-pop mechanism */
        if (audio_state != previous_audio_state)
        {
            if (audio_state == BT_AUDIO_PLAYING) 
            {
                uint16_t normalized_vol = volume * 100 / 0x7f;
                tad5212_set_volume(TAD5212_CHANNEL_BOTH, 0);
                vTaskDelay(pdMS_TO_TICKS(50));
                tpa3255_gpio_set_reset(&subwoofer_amplifier, false);
                tpa3255_gpio_set_reset(&speaker_amplifier, false);
                vTaskDelay(pdMS_TO_TICKS(50));
                tad5212_set_volume(TAD5212_CHANNEL_BOTH, normalized_vol);
            }
            previous_audio_state = audio_state;
        }
        vTaskDelay(pdMS_TO_TICKS(MAIN_TICK_DELAY_MS));
    }
}
