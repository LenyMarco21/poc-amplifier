/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Default configuration for TAD5212 codec registers (common to 2-way speakers and subwoofer configurations)
 * 
 * No licence
 */

#ifndef __TAD5212_COMMON_CONFIG_H__
#define __TAD5212_COMMON_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Includes ************************************************************************************/

/* Common defines */
#include "../tad5212_defines.h"

/* Biquad filters definitions */
#include "../tad5212_biquad_filters.h"

/* Mixer definitions */
#include "../tad5212_mixer.h"

/* Main configuration registers */
#include "../registers/tad5212_regs_page_0.h"

/* Main configuration 2 registers */
#include "../registers/tad5212_regs_page_1.h"

/* Biquad Filters 1 - 6 registers */
#include "../registers/tad5212_regs_page_15.h"

/* Biquad Filters 7 - 12 registers */
#include "../registers/tad5212_regs_page_16.h"

/* Mixer registers */
#include "../registers/tad5212_regs_page_17.h"

/*** Defines **************************************************************************************/

#define TAD5212_PAGE_0    0x00
#define TAD5212_PAGE_1    0x01
#define TAD5212_PAGE_15   0x0F
#define TAD5212_PAGE_16   0x10
#define TAD5212_PAGE_17   0x11

/*** Constant Structures **************************************************************************/

const static tad5212_REG_SW_RESET_t COMMON_CFG_SW_RESET = 
{
    .reset = 0x1,  /* Software reset */
};

const static tad5212_REG_DEV_MISC_CFG_t COMMON_CFG_DEV_MISC_CFG_P0 = 
{
    .sleep_enz                  = 0x1,  /* Device is not in sleep mode */
    .iovdd_io_mode              = 0x0,  /* IOVDD at 3.3V / 1.8V / 1.2V (speed limitation applicable for 1.8V and 1.2V Operation) */
    .avdd_mode                  = 0x0,  /* Internal AREG regulator is used (Should be used for AVDD 3.3V Operation) */
    .sleep_exit_vref_en         = 0x1,  /* DREG and VREF enabled */
    .vref_qchg                  = 0x2,  /* VREF quick-charge duration of 50 ms (typical) */
};


const static tad5212_REG_DAC_CFG_A0_t COMMON_CFG_DAC_CFG_A0 = 
{
    .pwr_up_time_de_pop         = 0x06,  /* DAC power-up time of 250 ms (not typical) */
    .rseries_de_pop_mid         = 0x00,  /* De-pop resistor series mid value (1K) */
    .rseries_de_pop_int         = 0x00,  /* De-pop resistor series internal value (1K) */
};

const static tad5212_REG_MISC_CFG0_t COMMON_CFG_MISC_CFG0 =
{
    .hw_reset_on_clk_stop_en    = 0x0,  /* No Hard Reset when clock selected by CLK_SRC_SEL is not available for 2ms config */
    .dac_delayed_pwrup_time     = 0x0,  /* DAC delayed power up time of 64-128 ms */
    .dac_delayed_pwrup          = 0x1,  /* DAC power up delayed config */
    .dac_st_w_cap_dis           = 0x1,  /* DAC start with dc blocking capacitor discharge sequence */
};
    
const static tad5212_REG_INTF_CFG1_t COMMON_CFG_INTF_CFG1 = 
{
    .dout_drv                   = 0x0,  /* Hi-Z output */
    .dout_val                   = 0x0,  /* Drive the output with a value of 0 */
    .dout_sel                   = 0x0,  /* DOUT is disabled */
};

const static tad5212_REG_ASI_CFG1_t COMMON_CFG_ASI_CFG1 = 
{
    .daisy_dir                  = 0x0,  /* ASI DOUT daisy */
    .asi_din_cfg                = 0x1,  /* 2 data inputs for Primary ASI */
    .asin_dout_cfg              = 0x0,  /* 1 data output for Primary ASI and 1 data output for Secondary ASI */
};

const static tad5212_REG_PASI_CFG0_t COMMON_CFG_PASI_CFG0 = 
{
    .pasi_bus_err_rcov          = 0x0,  /* Enable auto resume after bus error recovery */
    .pasi_bus_err               = 0x0,  /* Enable bus error detection */
    .pasi_bclk_pol              = 0x0,  /* Default polarity as per standard protocol */
    .pasi_fsync_pol             = 0x0,  /* Default polarity as per standard protocol */
    .pasi_wlen                  = 0x0,  /* Primary ASI word or slot length of 16 bits */
    .pasi_format                = 0x2,  /* Primary ASI protocol format I2S LJ */
};

const static tad5212_REG_RX_CH1_CFG_t COMMON_CFG_PASI_RX_CH1_CFG = 
{
    .pasi_rx_ch1_slot_num       = 0x0,  /* Primary ASI input channel 1 left slot 0 */
    .pasi_rx_ch1_cfg            = 0x1,  /* Primary ASI input channel 1 on DAC 1 */
    .reserved                   = 0x0,
};

const static tad5212_REG_RX_CH2_CFG_t COMMON_CFG_PASI_RX_CH2_CFG = 
{
    .pasi_rx_ch2_slot_num       = 0x10, /* Primary ASI input channel 2 right slot 0 */
    .pasi_rx_ch2_cfg            = 0x1,  /* Primary ASI input channel 2 on DAC 2 */
    .reserved                   = 0x0,
};

const static tad5212_REG_OUT1x_CFG0_t COMMON_CFG_OUT1X_CFG0 = 
{
    .out1x_vcom                 = 0x0,  /* 0.6 * Vref (for 1.375V VREF mode alone as 0.654*Vref) */
    .out1x_cfg                  = 0x0,  /* Differential (DAC1AP + DAC1BP / IN1M -> OUT1P ; DAC1AM + DAC1BM / IN1P -> OUT1M) */
    .out1x_src                  = 0x1,  /* Input from DAC signal chain */
};

const static tad5212_REG_OUT1x_CFG1_t COMMON_CFG_OUT1X_CFG1 = 
{
    .dac_ch1_bw_mode            = 0x0,  /* audio band-width (24 kHz mode) */
    .ain1x_byp_cfg              = 0x0,  /* FD / Pseudo Diff */
    .ain1m_byp_imp              = 0x0,  /* 4.4kΩ */
    .out1p_lvl_ctrl             = 0x4,  /* 0 dB */
    .out1p_drive                = 0x3,  /* Line out driver with minimum 300Ω single ended impedance */
};

const static tad5212_REG_OUT1x_CFG2_t COMMON_CFG_OUT1X_CFG2 = 
{
    .dac_ch1_cm_tol             = 0x0,  /* AC-coupled input */
    .ain1p_byp_imp              = 0x0,  /* 4.4kΩ */
    .out1m_lvl_ctrl             = 0x4,  /* 0 dB */
    .out1m_drive                = 0x3,  /* Line out driver with minimum 300Ω single ended impedance */
};

const static tad5212_REG_DAC_CH1A_CFG0_t COMMON_CFG_DAC_CH1A_CFG0 = 
{
    .dac_ch1a_dvol              = TAD5212_DAC_MIN_VOLUME,  /* Channel 1A digital volume control */
};

const static tad5212_REG_OUT2x_CFG0_t COMMON_CFG_OUT2X_CFG0 = 
{
    .out2x_vcom                 = 0x0,  /* 0.6 * Vref (for 1.375V VREF mode alone as 0.654*Vref) */
    .out2x_cfg                  = 0x0,  /* Differential (DAC2AP + DAC2BP / IN2M -> OUT2P ; DAC2AM + DAC2BM / IN2P -> OUT2M) */
    .out2x_src                  = 0x1,  /* Input from DAC signal chain */
};

const static tad5212_REG_OUT2x_CFG1_t COMMON_CFG_OUT2X_CFG1 = 
{
    .dac_ch2_bw_mode            = 0x0,  /* audio band-width (24 kHz mode) */
    .ain2x_byp_cfg              = 0x0,  /* FD / Pseudo Diff */
    .ain2m_byp_imp              = 0x0,  /* 4.4kΩ */
    .out2p_lvl_ctrl             = 0x4,  /* 0 dB */
    .out2p_drive                = 0x3,  /* Line out driver with minimum 300Ω single ended impedance */
};

const static tad5212_REG_OUT2x_CFG2_t COMMON_CFG_OUT2X_CFG2 = 
{
    .dac_ch2_cm_tol             = 0x0,  /* AC-coupled input */
    .ain2p_byp_imp              = 0x0,  /* 4.4kΩ */
    .out2m_lvl_ctrl             = 0x4,  /* 0 dB */
    .out2m_drive                = 0x3,  /* Line out driver with minimum 300Ω single ended impedance */
};

const static tad5212_REG_DAC_CH2A_CFG0_t COMMON_CFG_DAC_CH2A_CFG0 = 
{
    .dac_ch2a_dvol              = TAD5212_DAC_MIN_VOLUME,  /* Channel 2A digital volume control */
};

const static tad5212_REG_CH_EN_t COMMON_CFG_CH_EN = 
{
    .in_ch1_en                 = 0x0,  /* ADC Channel 1 disabled */
    .in_ch2_en                 = 0x0,  /* ADC Channel 2 disabled */
    .in_ch3_en                 = 0x0,  /* ADC Channel 3 disabled */
    .in_ch4_en                 = 0x0,  /* ADC Channel 4 disabled */
    .out_ch1_en                 = 0x1,  /* DAC Channel 1 enabled */
    .out_ch2_en                 = 0x1,  /* DAC Channel 2 enabled */
    .out_ch3_en                 = 0x0,  /* DAC Channel 3 disabled */
    .out_ch4_en                 = 0x0,  /* DAC Channel 4 disabled */
};

const static tad5212_REG_PWR_CFG_t COMMON_CFG_PWR_CFG = 
{
    .uag_en                     = 0x0,  /* Disable UAG */
    .vad_en                     = 0x0,  /* Disable VAD */
    .uad_en                     = 0x0,  /* Disable UAD */
    .micbias_pdz                = 0x0,  /* Power down MICBIAS */
    .dac_pdz                    = 0x1,  /* Power up all DACs */
    .adc_pdz                    = 0x0,  /* Power down all ADCs */
};

#endif /* __TAD5212_COMMON_CONFIG_H__ */