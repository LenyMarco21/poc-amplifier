/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Subwoofer configuration for TAD5212 codec registers
 * In this configuration, I2S stereo samples are mixed such as : 0.5 * L + 0.5 * R = DAC_1
 * A 4th order IIR crossover filter is applied to cut frequencies above 150Hz on the subwoofer output.
 * 
 * No licence
 */

#ifndef __TAD5212_SUBWOOFER_CONFIG_H__
#define __TAD5212_SUBWOOFER_CONFIG_H__

/*** Includes *************************************************************************/

/* Main configuration registers */
#include "tad5212_common_config.h"

/*** Constants ***********************************************************************/

const static tad5212_REG_MIXER_CFG0_t SUBWOOFER_CFG_MIXER_CFG0 = 
{
    .reserved                   = 0x0,
    .en_loopback_mixer          = 0x0,  /* Disable Loopback Mixer */
    .en_adc_channel_mixer       = 0x0,  /* Disable ADC Channel Mixer */
    .en_side_chain_mixer        = 0x0,  /* Disable Side Chain Mixer */
    .en_dac_asi_mixer           = 0x1,  /* Enable DAC ASI Mixer */
};

const static tad5212_REG_CH_EN_t SUBWOOFER_CFG_CH_EN = 
{
    .out_ch4_en                 = 0x0,  /* Disable output channel 4 */
    .out_ch3_en                 = 0x0,  /* Disable output channel 3 */
    .out_ch2_en                 = 0x1,  /* Enable output channel 2 */
    .out_ch1_en                 = 0x0,  /* Disable output channel 1 */
    .in_ch4_en                  = 0x0,  /* Disable input channel 4 */
    .in_ch3_en                  = 0x0,  /* Disable input channel 3 */
    .in_ch2_en                  = 0x0,  /* Disable input channel 2 */
    .in_ch1_en                  = 0x0,  /* Disable input channel 1 */
};

#endif /* __TAD5212_SUBWOOFER_CONFIG_H__ */