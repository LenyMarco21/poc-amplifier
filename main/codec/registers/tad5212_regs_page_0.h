/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definition of TAD5212 registers - Page 0 - General configuration
 * 
 * No licence
 */

#ifndef __TAD5212_REGS_PAGE_0_H__
#define __TAD5212_REGS_PAGE_0_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Defines **************************************************************************/

/*** Enumerations *********************************************************************/

/* TAD5212 register map */
typedef enum
{
    REG_PAGE_CFG            = 0x00, /* Device page register */
    REG_SW_RESET            = 0x01, /* Software reset register */
    REG_DEV_MISC_CFG        = 0x02, /* Device miscellaneous configuration register */
    REG_AVDD_IOVDD_STS      = 0x03, /* Supply status register */
    REG_MISC_CFG            = 0x04, /* Miscellaneous configuration register */
    REG_MISC_CFG1           = 0x05, /* Miscellaneous configuration register 1 */
    REG_DAC_CFG_A0          = 0x06, /* DAC de-pop configuration register */
    REG_MISC_CFG0           = 0x07, /* Miscellaneous configuration register 0 */

    REG_GPIO1_CFG0          = 0x0A, /* GPIO1 configuration register 0 */
    REG_GPIO2_CFG0          = 0x0B, /* GPIO2 configuration register 0 */
    REG_GPO1_CFG0           = 0x0C, /* GPO1 configuration register 0 */
    REG_GPI_CFG             = 0x0D, /* GPI1 configuration register */
    REG_GPO_GPI_VAL         = 0x0E, /* GPIO/GPO output value register */

    REG_INTF_CFG0           = 0x0F, /* Interface configuration register 0 */
    REG_INTF_CFG1           = 0x10, /* Interface configuration register 1 */
    REG_INTF_CFG2           = 0x11, /* Interface configuration register 2 */
    REG_INTF_CFG3           = 0x12, /* Interface configuration register 3 */
    REG_INTF_CFG4           = 0x13, /* Interface configuration register 4 */
    REG_INTF_CFG5           = 0x14, /* Interface configuration register 5 */
    REG_INTF_CFG6           = 0x15, /* Interface configuration register 6 */

    REG_ASI_CFG0            = 0x18, /* ASI configuration register 0 */
    REG_ASI_CFG1            = 0x19, /* ASI configuration register 1 */

    REG_PASI_CFG0           = 0x1A, /* Primary ASI configuration register 0 */

    REG_PASI_TX_CFG0        = 0x1B, /* PASI TX configuration register 0 */
    REG_PASI_TX_CFG1        = 0x1C, /* PASI TX configuration register 1 */
    REG_PASI_TX_CFG2        = 0x1D, /* PASI TX configuration register 2 */

    REG_PASI_TX_CH1_CFG     = 0x1E, /* PASI TX Channel 1 configuration register */
    REG_PASI_TX_CH2_CFG     = 0x1F, /* PASI TX Channel 2 configuration register */
    REG_PASI_TX_CH3_CFG     = 0x20, /* PASI TX Channel 3 configuration register */
    REG_PASI_TX_CH4_CFG     = 0x21, /* PASI TX Channel 4 configuration register */
    REG_PASI_TX_CH5_CFG     = 0x22, /* PASI TX Channel 5 configuration register */
    REG_PASI_TX_CH6_CFG     = 0x23, /* PASI TX Channel 6 configuration register */
    REG_PASI_TX_CH7_CFG     = 0x24, /* PASI TX Channel 7 configuration register */
    REG_PASI_TX_CH8_CFG     = 0x25, /* PASI TX Channel 8 configuration register */

    REG_PASI_RX_CFG0        = 0x26, /* PASI RX configuration register 0 */
    REG_PASI_RX_CFG1        = 0x27, /* PASI RX configuration register 1 */

    REG_PASI_RX_CH1_CFG     = 0x28, /* PASI RX Channel 1 configuration register */
    REG_PASI_RX_CH2_CFG     = 0x29, /* PASI RX Channel 2 configuration register */
    REG_PASI_RX_CH3_CFG     = 0x2A, /* PASI RX Channel 3 configuration register */
    REG_PASI_RX_CH4_CFG     = 0x2B, /* PASI RX Channel 4 configuration register */
    REG_PASI_RX_CH5_CFG     = 0x2C, /* PASI RX Channel 5 configuration register */
    REG_PASI_RX_CH6_CFG     = 0x2D, /* PASI RX Channel 6 configuration register */
    REG_PASI_RX_CH7_CFG     = 0x2E, /* PASI RX Channel 7 configuration register */
    REG_PASI_RX_CH8_CFG     = 0x2F, /* PASI RX Channel 8 configuration register */

    REG_CLK_CFG0            = 0x32, /* Clock configuration register 0 */
    REG_CLK_CFG1            = 0x33, /* Clock configuration register 1 */
    REG_CLK_CFG2            = 0x34, /* Clock configuration register 2 */

    REG_CNT_CLK_CFG0        = 0x35, /* Controller mode clock configuration register 0 */
    REG_CNT_CLK_CFG1        = 0x36, /* Controller mode clock configuration register 1 */
    REG_CNT_CLK_CFG2        = 0x37, /* Controller mode clock configuration register 2 */
    REG_CNT_CLK_CFG3        = 0x38, /* Controller mode clock configuration register 3 */
    REG_CNT_CLK_CFG4        = 0x39, /* Controller mode clock configuration register 4 */
    REG_CNT_CLK_CFG5        = 0x3A, /* Controller mode clock configuration register 5 */
    REG_CNT_CLK_CFG6        = 0x3B, /* Controller mode clock configuration register 6 */

    REG_CLK_ERR_STS0        = 0x3C, /* Clock error and status register 0 */
    REG_CLK_ERR_STS1        = 0x3D, /* Clock error and status register 1 */

    REG_CLK_DET_STS0        = 0x3E, /* Clock ratio detection register 0 */
    REG_CLK_DET_STS1        = 0x3F, /* Clock ratio detection register 1 */
    REG_CLK_DET_STS2        = 0x40, /* Clock ratio detection register 2 */
    REG_CLK_DET_STS3        = 0x41, /* Clock ratio detection register 3 */

    REG_INT_CFG             = 0x42, /* Interrupt configuration register */
    REG_DAC_FLT_CFG         = 0x43, /* DAC fault / interrupt configuration register */

    REG_VREF_MICBIAS_CFG    = 0x4D, /* VREF and MICBIAS configuration register */

    REG_PWR_TUNE_CFG0       = 0x4E, /* Power tune configuration register 0 */
    REG_PWR_TUNE_CFG1       = 0x4F, /* Power tune configuration register 1 */

    REG_ADC_CH1_CFG2        = 0x52, /* ADC Channel 1 configuration register 2 */
    REG_ADC_CH1_CFG3        = 0x53, /* ADC Channel 1 configuration register 3 */
    REG_ADC_CH1_CFG4        = 0x54, /* ADC Channel 1 configuration register 4 */

    REG_ADC_CH2_CFG2        = 0x57, /* ADC Channel 2 configuration register 2 */
    REG_ADC_CH2_CFG3        = 0x58, /* ADC Channel 2 configuration register 3 */
    REG_ADC_CH2_CFG4        = 0x59, /* ADC Channel 2 configuration register 4 */

    REG_ADC_CH3_CFG0        = 0x5A, /* ADC Channel 3 configuration register 0 */
    REG_ADC_CH3_CFG2        = 0x5B, /* ADC Channel 3 configuration register 2 */
    REG_ADC_CH3_CFG3        = 0x5C, /* ADC Channel 3 configuration register 3 */
    REG_ADC_CH3_CFG4        = 0x5D, /* ADC Channel 3 configuration register 4 */

    REG_ADC_CH4_CFG0        = 0x5E, /* ADC Channel 4 configuration register 0 */
    REG_ADC_CH4_CFG2        = 0x5F, /* ADC Channel 4 configuration register 2 */
    REG_ADC_CH4_CFG3        = 0x60, /* ADC Channel 4 configuration register 3 */
    REG_ADC_CH4_CFG4        = 0x61, /* ADC Channel 4 configuration register 4 */

    REG_OUT1X_CFG0          = 0x64, /* Channel OUT1x configuration register 0 */
    REG_OUT1X_CFG1          = 0x65, /* Channel OUT1x configuration register 1 */
    REG_OUT1X_CFG2          = 0x66, /* Channel OUT1x configuration register 2 */

    REG_DAC_CH1A_CFG0       = 0x67, /* DAC Channel 1A configuration register 0 */
    REG_DAC_CH1A_CFG1       = 0x68, /* DAC Channel 1A configuration register 1 */
    REG_DAC_CH1B_CFG0       = 0x69, /* DAC Channel 1B configuration register 0 */
    REG_DAC_CH1B_CFG1       = 0x6A, /* DAC Channel 1B configuration register 1 */

    REG_OUT2X_CFG0          = 0x6B,  /* Channel OUT2x configuration register 0 */
    REG_OUT2X_CFG1          = 0x6C, /* Channel OUT2x configuration register 1 */
    REG_OUT2X_CFG2          = 0x6D, /* Channel OUT2x configuration register 2 */

    REG_DAC_CH2A_CFG0       = 0x6E, /* DAC Channel 2A configuration register 0 */
    REG_DAC_CH2A_CFG1       = 0x6F, /* DAC Channel 2A configuration register 1 */
    REG_DAC_CH2B_CFG0       = 0x70, /* DAC Channel 2B configuration register 0 */
    REG_DAC_CH2B_CFG1       = 0x71, /* DAC Channel 2B configuration register 1 */

    REG_DSP_CFG0            = 0x72, /* DSP configuration register 0 */
    REG_DSP_CFG1            = 0x73, /* DSP configuration register 1 */

    REG_CH_EN               = 0x76, /* Channel enable configuration register */

    REG_DYN_PUPD_CFG        = 0x77, /* Dynamic power-up / power-down configuration register */
    REG_PWR_CFG             = 0x78, /* Power configuration register */

    REG_DEV_STS0            = 0x79, /* Device status value register 0 */
    REG_DEV_STS1            = 0x7A, /* Device status value register 1 */

    REG_I2C_CKSUM           = 0x7E  /* I2C checksum register */

}
tad5212_page_0_reg_addr_t;

/*** Structures ***********************************************************************/

/* TAD5212 REG_SW_RESET register (0x1) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reset       : 1;    /* Software reset. This bit is self clearing*/
        uint8_t reserved    : 7;
    };
} 
tad5212_REG_SW_RESET_t;

/* TAD5212 REG_DEV_MISC_CFG register (0x2)*/
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t sleep_enz           : 1;    /* Sleep mode setting */
        uint8_t iovdd_io_mode       : 1;    /* IOVDD mode configuration */
        uint8_t avdd_mode           : 1;    /* AVDD mode configuration */
        uint8_t sleep_exit_vref_en  : 1;    /* Sleep mode exit configuration */
        uint8_t vref_qchg           : 2;    /* The duration of the quick-charge for the VREF external capacitor is set using an internal series impedance of 200Ω*/
        uint8_t reserved            : 2;
    };
}
tad5212_REG_DEV_MISC_CFG_t;

/* TAD5212 REG_AVDD_IOVDD_STS register (0x3)*/
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t brwnout_shdn_exit_sleep : 1;    /* Brownout shutdown sleep exit config */
        uint8_t brwnout_shdn_sts        : 1;    /* Brownout shutdown status */
        uint8_t reserved                : 4;
        uint8_t iovdd_io_mode_sts       : 1;    /* IOVDD mode status flag register */
        uint8_t avdd_mode_sts           : 1;    /* AVDD mode status flag register */
    };
}
tad5212_REG_AVDD_IOVDD_STS_t;

/* TAD5212 MISC_CFG register (0x4)*/
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved_0      : 1;
        uint8_t i2c_brdcast_en  : 1;    /* I2C broadcast addressing setting */
        uint8_t reserved_1      : 4;
        uint8_t ignore_clk_err  : 1;    /* Clock error detection action */
        uint8_t reserved_2      : 1;
    };
}
tad5212_REG_MISC_CFG_t;

/* TAD5212 MISC_CFG1 register (0x5) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved        : 2;
        uint8_t dreg_ka_time    : 2;    /* These bits set how long DREG remains active after IOVDD is deasserted */
        uint8_t shdn_cfg        : 2;    /* Shutdown configuration */
        uint8_t incap_qchg      : 2;    /* The duration of the quick-charge for the external AC-coupling capacitor is set using an internal series impedance of 800Ω */
    };
} 
tad5212_REG_MISC_CFG1_t;

/* TAD5212 REG_DAC_CFG_A0 register (0x6) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t pwr_up_time_de_pop  : 4;    /* HP Amp external cap charging time config */
        uint8_t rseries_de_pop_mid  : 2;    /* HP Amp series resistor select config */
        uint8_t rseries_de_pop_int  : 2;    /* HP Amp series resistor select config*/
    };
} 
tad5212_REG_DAC_CFG_A0_t;

/* TAD5212 MISC_CFG0 register (0x7) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved                    : 4;
        uint8_t hw_reset_on_clk_stop_en     : 1;    /* Assertion of Hard Reset when clock selected by CLK_SRC_SEL is not available for 2ms config */
        uint8_t dac_delayed_pwrup_time      : 1;    /* DAC power up delayed time config */
        uint8_t dac_delayed_pwrup           : 1;    /* DAC power up delayed config */
        uint8_t dac_st_w_cap_dis            : 1;    /* DAC start with dc blocking capacitor discharge sequence */
    };
} 
tad5212_REG_MISC_CFG0_t;

/* TAD5212 GPIO1_CFG0 register (0xA) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t gpio1_drv   : 3;    /* GPIO1 output drive configuration. (Not valid if GPIO1_CFG configured as I2S out) */
        uint8_t reserved    : 1; 
        uint8_t gpio1_cfg   : 4;    /* GPIO1 configuration */
    };
} 
tad5212_REG_GPIO1_CFG0_t;

/* TAD5212 GPIO2_CFG0 register (0xB) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t gpio2_drv   : 3;    /* GPIO2 output drive configuration. (Not valid if GPIO2_CFG configured as I2S out) */
        uint8_t reserved    : 1; 
        uint8_t gpio2_cfg   : 4;    /* GPIO2 configuration */
    };
} 
tad5212_REG_GPIO2_CFG0_t;

/* TAD5212 GPO1_CFG0 register (0xC) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t gpo1_drv    : 3;    /* GPO1 output drive configuration. (Not valid if GPO1_CFG configured as I2S out) (For SPI mode, this pin act as CSZ) */
        uint8_t reserved    : 1; 
        uint8_t gpo1_cfg    : 4;    /* GPO1 configuration. (For SPI mode, this pin act as POCI ) (Always buskeeper en is not supported when used as DOUT) */
    };
} 
tad5212_REG_GPO1_CFG0_t;

/* TAD5212 GPI_CFG register (0xD) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved_0  : 1;
        uint8_t gpi1_cfg    : 1;    /* GPI1 configuration. (For SPI mode, this pin act as CSZ and the below configuration settings are not applicable) */
        uint8_t reserved_1  : 6;
    };
} 
tad5212_REG_GPI_CFG_t;

/* TAD5212 GPO_GPI_VAL register (0xE) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved_0  : 1;
        uint8_t gpi1_mon    : 1;    /* GPI1 monitor value when configured as a GPI */
        uint8_t gpio2_mon   : 1;    /* GPIO2 monitor value when configured as a GPI */
        uint8_t gpio1_mon   : 1;    /* GPIO1 monitor value when configured as a GPI */
        uint8_t reserved_1  : 1;    
        uint8_t gpo1_val    : 1;    /* GPO1 output value when configured as a GPO */
        uint8_t gpio2_val   : 1;    /* GPIO2 output value when configured as a GPO */
        uint8_t gpio1_val   : 1;    /* GPIO1 output value when configured as a GPO */
    };
} 
tad5212_REG_GPO_GPI_VAL_t;

/* TAD5212 INTF_CFG1 register (0x10) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dout_drv : 3;    /* DOUT output drive configuration */
        uint8_t dout_val : 1;    /* DOUT output value when configured as a GPO */
        uint8_t dout_sel : 1;    /* DOUT select configuration */
    };
} 
tad5212_REG_INTF_CFG1_t;

/* TAD5212 REG_ASI_CFG1 register (0x19) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved        : 3;
        uint8_t daisy_dir       : 1;    /* Daisy direction configuration */
        uint8_t asi_din_cfg     : 2;    /* ASI data input configuration */
        uint8_t asin_dout_cfg   : 2;    /* ASI data output configuration */
    };
}
tad5212_REG_ASI_CFG1_t;

/* TAD5212 PASI_CFG0 register (0x1A) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t pasi_bus_err_rcov   : 1;    /* ASI bus error auto resume */
        uint8_t pasi_bus_err        : 1;    /* ASI bus error detection */
        uint8_t pasi_bclk_pol       : 1;    /* ASI BCLK polarity (for PASI protocol only) */
        uint8_t pasi_fsync_pol      : 1;    /* ASI FSYNC polarity (for PASI protocol only) */
        uint8_t pasi_wlen           : 2;    /* Primary ASI word or slot length */
        uint8_t pasi_format         : 2;    /* Primary ASI protocol format */
    };
} 
tad5212_REG_PASI_CFG0_t;

/* TAD5212 REG_PASI_RX_CH1_CFG register (0x28) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t pasi_rx_ch1_slot_num    : 5;    /* Primary ASI input channel 1 slot assignment */
        uint8_t pasi_rx_ch1_cfg         : 1;    /* Primary ASI input channel 1 configuration */
        uint8_t reserved                : 2;
    };
}
tad5212_REG_RX_CH1_CFG_t;

/* TAD5212 REG_PASI_RX_CH2_CFG register (0x29) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t pasi_rx_ch2_slot_num    : 5;    /* Primary ASI input channel 2 slot assignment */
        uint8_t pasi_rx_ch2_cfg         : 1;    /* Primary ASI input channel 2 configuration */
        uint8_t reserved                : 2;
    };
}
tad5212_REG_RX_CH2_CFG_t;

/* TAD5212 CLK_CFG0 register (0x32) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t custom_clk_cfg      : 1;    /* Custom clock configuration enable, all dividers and mux selects need to be manually configured */
        uint8_t pasi_fs_rate_no_lim : 1;    /* Limit sampling rate to standard audio sample rates only */
        uint8_t pasi_samp_rate      : 6;    /* Primary ASI sample rate configuration. -Typical (Allowed Range) */
    };
} 
tad5212_REG_CLK_CFG0_t;

/* TAD5212 CLK_ERR_STS0 register (0x3C) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved_0                  : 1;
        uint8_t reset_on_clk_stop_det_sts   : 1;    /* Flag indicating that audio clock source stopped for at least 1ms */
        uint8_t pdm_clk_err                 : 1;    /* Flag indicating that clock configuration does not allow valid PDM clock generation */
        uint8_t dem_rate_err                : 1;    /* Flag indicating that clock configuration does not allow valid DEM rate */
        uint8_t src_ratio_err               : 1;    /* Flag indicating that SRC m:n ratio is unsupported. (not valid for custom m/n ratio config) */
        uint8_t reserved_1                  : 2;
        uint8_t dsp_clk_err                 : 1;    /* Flag indicating ratio error between FSYNC and selected clock source */
    };
} 
tad5212_REG_CLK_ERR_STS0_t;

/* TAD5212 CLK_ERR_STS1 register (0x3D) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved                : 3;
        uint8_t sasi_fs_err             : 1;    /* Flag indicating SASI FS rate change or halt error */
        uint8_t pasi_fs_err             : 1;    /* Flag indicating PASI FS rate change or halt error*/
        uint8_t cclk_fs_ratio_err       : 1;    /* Flag indicating CCLK fsync ratio error */
        uint8_t sasi_bclk_fs_ratio_err  : 1;    /* Flag indicating SASI bclk fsync ratio error */
        uint8_t pasi_bclk_fs_ratio_err  : 1;    /* Flag indicating PASI bclk fsync ratio error */
    };
} 
tad5212_REG_CLK_ERR_STS1_t;

/* TAD5212 CLK_DET_STS0 register (0x3E) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t pll_mode_sts        : 2;    /* PLL usage status */
        uint8_t pasi_samp_rate_sts  : 6;    /* Primary ASI Sample rate detected status */
    };
} 
tad5212_REG_CLK_DET_STS0_t;

/* TAD5212 CLK_DET_STS1 register (0x3F) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved            : 2;
        uint8_t sasi_samp_rate_sts  : 6;    /* Secondary ASI Sample rate detected status */
    };
} 
tad5212_REG_CLK_DET_STS1_t;

/* TAD5212 CLK_DET_STS2 register (0x40) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t fs_clksrc_ratio_det_msb_sts : 6;    /* MSB bits for primary ASI or secondary ASI FSYNC to clock source ratio detected */
        uint8_t reserved                    : 2;
    };
} 
tad5212_REG_CLK_DET_STS2_t;

/* TAD5212 CLK_DET_STS3 register (0x41) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t fs_clksrc_ratio_det_lsb_sts : 8;    /* LSB bits for primary ASI or secondary ASI FSYNC to clock source ratio detected */
    };
} 
tad5212_REG_CLK_DET_STS3_t;

/* TAD5212 INT_CFG register (0x42) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t ltch_clr_on_read    : 1;    /* Cfgn for clearing LTCH register bits */
        uint8_t pd_on_plt_rcv_cfg   : 1;    /* Configuration for Power down ADC channels on fault */
        uint8_t ltch_read_cfg       : 1;    /* Interrupt latch registers readback configuration */
        uint8_t pd_on_flt_cfg       : 2;    /* Power down configuration during fault for chx and micbias */
        uint8_t int_event           : 2;    /* Interrupt event configuration */
        uint8_t int_pol             : 1;    /* Interrupt polarity */
    };
} 
tad5212_REG_INT_CFG_t;

/* TAD5212 DAC_FLT_CFG register (0x43) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t areg_sc_flag_det_dis    : 1;    /* AREG short circuit detect config */
        uint8_t dac_flt_det_dis         : 1;    /* DAC vg_fault/sc_fault detect config */
        uint8_t dac_dis_pd_w_pu         : 1;    /* Disable power down on DRVR VG fault while powering up DAC */
        uint8_t out_chx_pd_flt_sts      : 1;    /* Status for PD on OUTxx faults */
        uint8_t dac_pd_on_flt_rcv_cfg   : 1;    /* Configuration for Power down DAC channels on fault */
        uint8_t dac_pd_on_flt_cfg       : 2;    /* Power down configuration during fault for DAC */
        uint8_t reserved                : 1;
    };
} 
tad5212_REG_DAC_FLT_CFG_t;

/* TAD5212 PWR_TUNE_CFG1 register (0x4F) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved_0              : 1;
        uint8_t dac_power_scal          : 1;    /* DAC IREF select configuration */
        uint8_t dac_low_pwr_filt        : 1;    /* Low Power Filter configuration for DAC */
        uint8_t reserved_1              : 1;
        uint8_t dac_pd_on_flt_rcv_cfg   : 1;    /* DAC DEM rate override configuration */
        uint8_t reserved_2              : 2;
        uint8_t dac_clk_by2_mode        : 1;    /* DAC MOD CLK select configuration */
    };
} 
tad5212_REG_PWR_TUNE_CFG1_t;

/* TAD5212 OUT1x_CFG0 register (0x64) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved    : 1;
        uint8_t out1x_vcom  : 1;    /* Channel OUT1x VCOM configuration */
        uint8_t out1x_cfg   : 3;    /* OUT1x DAC / Analog Bypass Routing Configuration. (Don't use if OUT1x_SRC configured 4d or 5d) */
        uint8_t out1x_src   : 3;    /* OUT1x Source Configuration */
    };
} 
tad5212_REG_OUT1x_CFG0_t;

/* TAD5212 OUT1x_CFG1 register (0x65) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch1_bw_mode : 1;    /* DAC Channel 1 band-width selection */
        uint8_t ain1x_byp_cfg   : 1;    /* IN1x Analog Bypass input config */
        uint8_t ain1m_byp_imp   : 1;    /* AIN1M Analog Bypass input impedance */
        uint8_t out1p_lvl_ctrl  : 3;    /* Channel OUT1P level control configuration */
        uint8_t out1p_drive     : 2;    /* Channel OUT1P drive configuration */
    };
} 
tad5212_REG_OUT1x_CFG1_t;

/* TAD5212 OUT1x_CFG2 register (0x66) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch1_cm_tol  : 1;    /* DAC Channel 1 input coupling (applicable for the analog input) */
        uint8_t reserved        : 1;
        uint8_t ain1p_byp_imp   : 1;    /* AIN1P Analog Bypass input impedance */
        uint8_t out1m_lvl_ctrl  : 3;    /* Channel OUT1M level control configuration */
        uint8_t out1m_drive     : 2;    /* Channel OUT1M drive configuration */
    };
} 
tad5212_REG_OUT1x_CFG2_t;

/* TAD5212 DAC_CH1A_CFG0 register (0x67) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch1a_dvol   : 8;    /* Channel 1A digital volume control */
    };
} 
tad5212_REG_DAC_CH1A_CFG0_t;

/* TAD5212 DAC_CH1A_CFG1 register (0x68) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved        : 4;
        uint8_t dac_ch1a_fgain  : 4;    /* DAC channel 1A fine gain calibration */
    };
} 
tad5212_REG_DAC_CH1A_CFG1_t;

/* TAD5212 DAC_CH1B_CFG0 register (0x69) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch1b_dvol   : 8;    /* Channel 1B digital volume control */
    };
} 
tad5212_REG_DAC_CH1B_CFG0_t;

/* TAD5212 DAC_CH1B_CFG1 register (0x6A) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved        : 4;
        uint8_t dac_ch1b_fgain  : 4;    /* DAC channel 1B fine gain calibration */
    };
} 
tad5212_REG_DAC_CH1B_CFG1_t;

/* TAD5212 OUT2x_CFG0 register (0x6B) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved    : 1;
        uint8_t out2x_vcom  : 1;    /* Channel OUT2x VCOM configuration */
        uint8_t out2x_cfg   : 3;    /* OUT2x DAC / Analog Bypass Routing Configuration. (Don't use if OUT2x_SRC configured 4d or 5d) */
        uint8_t out2x_src   : 3;    /* OUT2x Source Configuration */
    };
} 
tad5212_REG_OUT2x_CFG0_t;

/* TAD5212 OUT2x_CFG1 register (0x6C) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch2_bw_mode : 1;    /* DAC Channel 2 band-width selection */
        uint8_t ain2x_byp_cfg   : 1;    /* IN2x Analog Bypass input config */
        uint8_t ain2m_byp_imp   : 1;    /* AIN2M Analog Bypass input impedance */
        uint8_t out2p_lvl_ctrl  : 3;    /* Channel OUT2P level control configuration */
        uint8_t out2p_drive     : 2;    /* Channel OUT2P drive configuration */
    };
} 
tad5212_REG_OUT2x_CFG1_t;

/* TAD5212 OUT2x_CFG2 register (0x6D) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch2_cm_tol  : 1;    /* DAC Channel 2 input coupling (applicable for the analog input) */
        uint8_t reserved        : 1;
        uint8_t ain2p_byp_imp   : 1;    /* AIN2P Analog Bypass input impedance */
        uint8_t out2m_lvl_ctrl  : 3;    /* Channel OUT2M level control configuration */
        uint8_t out2m_drive     : 2;    /* Channel OUT2M drive configuration */
    };
} 
tad5212_REG_OUT2x_CFG2_t;

/* TAD5212 DAC_CH2A_CFG0 register (0x6E) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch2a_dvol   : 8;    /* Channel 2A digital volume control */
    };
} 
tad5212_REG_DAC_CH2A_CFG0_t;

/* TAD5212 DAC_CH2A_CFG1 register (0x6F) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved        : 4;
        uint8_t dac_ch2a_fgain  : 4;    /* DAC channel 2A fine gain calibration */
    };
} 
tad5212_REG_DAC_CH2A_CFG1_t;

/* TAD5212 DAC_CH2B_CFG0 register (0x70) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch2b_dvol   : 8;    /* Channel 2B digital volume control */
    };
} 
tad5212_REG_DAC_CH2B_CFG0_t;

/* TAD5212 DAC_CH2B_CFG1 register (0x71) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved        : 4;
        uint8_t dac_ch2b_fgain  : 4;    /* DAC channel 2B fine gain calibration */
    };
} 
tad5212_REG_DAC_CH2B_CFG1_t;

/* TAD5212 DSP_CFG0 register (0x72) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t adc_dsp_dvol_gang           : 1;    /* DVOL control ganged across ADC channels */
        uint8_t adc_dsp_disable_soft_step   : 1;    /* ADC Soft-stepping disable during DVOL change, mute, and unmute */
        uint8_t adc_dsp_bq_cfg              : 2;    /* Number of biquads per ADC channel configuration */
        uint8_t adc_dsp_hpf_sel             : 2;    /* ADC DSP high-pass filter selection */
        uint8_t adc_dsp_deci_filt           : 2;    /* ADC channel decimation filter response */
    };
} 
tad5212_REG_DSP_CFG0_t;

/* TAD5212 DSP_CFG1 register (0x73) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_dsp_dvol_gang           : 1;    /* DVOL control ganged across DAC channels */
        uint8_t dac_dsp_disable_soft_step   : 1;    /* DAC Soft-stepping disable during DVOL change, mute, and unmute */
        uint8_t dac_dsp_bq_cfg              : 2;    /* Number of biquads per DAC channel configuration */
        uint8_t dac_dsp_hpf_sel             : 2;    /* DAC DSP high-pass filter selection */
        uint8_t dac_dsp_deci_filt           : 2;    /* DAC channel decimation filter response */
    };
} 
tad5212_REG_DSP_CFG1_t;

/* TAD5212 CH_EN register (0x76) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t out_ch4_en  : 1;    /* Output channel 4 enable setting */
        uint8_t out_ch3_en  : 1;    /* Output channel 3 enable setting */
        uint8_t out_ch2_en  : 1;    /* Output channel 2 enable setting */
        uint8_t out_ch1_en  : 1;    /* Output channel 1 enable setting */
        uint8_t in_ch4_en  : 1;    /* Input channel 4 enable setting */
        uint8_t in_ch3_en  : 1;    /* Input channel 3 enable setting */
        uint8_t in_ch2_en  : 1;    /* Input channel 2 enable setting */
        uint8_t in_ch1_en  : 1;    /* Input channel 1 enable setting */
    };
} 
tad5212_REG_CH_EN_t;

/* TAD5212 DYN_PUPD_CFG register (0x77) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t dac_ch_swap                 : 1;    /* DAC channel swap */
        uint8_t adc_ch_swap                 : 1;    /* ADC channel swap */
        uint8_t reserved                    : 1;
        uint8_t dyn_pupd_adc_pdm_diff_clk   : 1;    /* Dynamic power-up power-down with different adc mod clock and pdm clock configuration */
        uint8_t dac_dyn_maxch_sel           : 1;    /* Dynamic mode maximum channel select configuration for playback path */
        uint8_t dac_dyn_pupd_en             : 1;    /* Dynamic channel power-up, power-down enable for playback path */
        uint8_t adc_dyn_maxch_sel           : 1;    /* Dynamic mode maximum channel select configuration for record path */
        uint8_t adc_dyn_pupd_en             : 1;    /* Dynamic channel power-up, power-down enable for record path */
    };
} 
tad5212_REG_DYN_PUPD_CFG_t;

/* TAD5212 PWR_CFG register (0x78) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved_0  : 1;
        uint8_t uag_en      : 1;    /* Enable ultrasound activity detection (UAG) algorithm */
        uint8_t vad_en      : 1;    /* Enable voice activity detection (VAD) algorithm */
        uint8_t uad_en      : 1;    /* Enable ultrasound activity detection (UAD) algorithm */
        uint8_t reserved_1  : 1;
        uint8_t micbias_pdz : 1;    /* Power control for MICBIAS */
        uint8_t dac_pdz     : 1;    /* Power control for DAC channels */
        uint8_t adc_pdz     : 1;    /* Power control for ADC and PDM channels */
    };
} 
tad5212_REG_PWR_CFG_t;

/* TAD5212 DEV_STS0 register (0x79) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t out_ch4_status  : 1;    /* DAC channel 4 power status */
        uint8_t out_ch3_status  : 1;    /* DAC channel 3 power status */
        uint8_t out_ch2_status  : 1;    /* DAC channel 2 power status */
        uint8_t out_ch1_status  : 1;    /* DAC channel 1 power status */
        uint8_t in_ch4_status  : 1;    /* ADC channel 4 power status */
        uint8_t in_ch3_status  : 1;    /* ADC channel 3 power status */
        uint8_t in_ch2_status  : 1;    /* ADC channel 2 power status */
        uint8_t in_ch1_status  : 1;    /* ADC channel 1 power status */
    };
} 
tad5212_REG_DEV_STS0_t;

/* TAD5212 DEV_STS1 register (0x7A) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved    : 3;
        uint8_t micbias_sts : 1;    /* MICBIAS status */
        uint8_t pll_sts     : 1;    /* PLL status */
        uint8_t mode_sts    : 3;    /* Device mode status */
    };
}
tad5212_REG_DEV_STS1_t;

/* TAD5212 I2C_CKSUM register (0x7E) */
typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t i2c_cksum   : 8;
    };
}
tad5212_REG_I2C_CKSUM_t;

#endif /* __TAD5212_REGS_PAGE_0_H__ */