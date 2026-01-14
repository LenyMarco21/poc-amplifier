/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definition of TAD5212 registers - Page 1 -  
 * 
 * No licence
 */

#ifndef __TAD5212_REGS_PAGE_1_H__
#define __TAD5212_REGS_PAGE_1_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Enumerations ***********************************************************************/

/* TAD5212 register map */
typedef enum
{
    /* Mixers registers */
    REG_MIXER_CFG0          = 0x2C, /* Mixer configuration register 0 */
    
}
tad5212_page_1_reg_addr_t;

/*** Structures ***********************************************************************/

typedef union 
{
    uint8_t data;

    struct 
    {
        uint8_t reserved                : 4;
        uint8_t en_loopback_mixer       : 1;    /* Enable Loopback Mixer */
        uint8_t en_adc_channel_mixer    : 1;    /* Enable ADC Channel Mixer */
        uint8_t en_side_chain_mixer     : 1;    /* Enable Side Chain Mixer */
        uint8_t en_dac_asi_mixer        : 1;    /* Enable DAC ASI Mixer */
    };
} 
tad5212_REG_MIXER_CFG0_t;

#endif /* __TAD5212_REGS_PAGE_1_H__ */