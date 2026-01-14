/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definition of TAD5212 registers - Page 17 - Mixer 
 * 
 * No licence
 */


#ifndef __TAD5212_REGS_PAGE_17_H__
#define __TAD5212_REGS_PAGE_17_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Enumerations ***********************************************************************/

/* TAD5212 register map */
typedef enum
{
    /* 2 channels mode */
    /* LDAC  :  DAC1 */
    /* RDAC  :  DAC2 */ 

    /* ASI CH1 Mixer Coefficients */
    REG_ASI_DIN_MIX_ASI_CH1_RDAC_MIX_BYT1   = 0x08, /* ASI DIN MIXER, ASI CH1 to RDAC coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH1_RDAC_MIX_BYT2   = 0x09, /* ASI DIN MIXER, ASI CH1 to RDAC coefficient byte[7:0] */
    REG_ASI_DIN_MIX_ASI_CH1_LDAC_MIX_BYT1   = 0x0A, /* ASI DIN MIXER, ASI CH1 to LDAC coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH1_LDAC_MIX_BYT2   = 0x0B, /* ASI DIN MIXER, ASI CH1 to LDAC coefficient byte[7:0] */
    REG_ASI_DIN_MIX_ASI_CH1_RDAC2_MIX_BYT1  = 0x0C, /* ASI DIN MIXER, ASI CH1 to RDAC2 coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH1_RDAC2_MIX_BYT2  = 0x0D, /* ASI DIN MIXER, ASI CH1 to RDAC2 coefficient byte[7:0] */
    REG_ASI_DIN_MIX_ASI_CH1_LDAC2_MIX_BYT1  = 0x0E, /* ASI DIN MIXER, ASI CH1 to LDAC2 coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH1_LDAC2_MIX_BYT2  = 0x0F, /* ASI DIN MIXER, ASI CH1 to LDAC2 coefficient byte[7:0] */

    /* ASI CH2 Mixer Coefficients */
    REG_ASI_DIN_MIX_ASI_CH2_RDAC_MIX_BYT1   = 0x10, /* ASI DIN MIXER, ASI CH2 to RDAC coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH2_RDAC_MIX_BYT2   = 0x11, /* ASI DIN MIXER, ASI CH2 to RDAC coefficient byte[7:0] */
    REG_ASI_DIN_MIX_ASI_CH2_LDAC_MIX_BYT1   = 0x12, /* ASI DIN MIXER, ASI CH2 to LDAC coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH2_LDAC_MIX_BYT2   = 0x13, /* ASI DIN MIXER, ASI CH2 to LDAC coefficient byte[7:0] */
    REG_ASI_DIN_MIX_ASI_CH2_RDAC2_MIX_BYT1  = 0x14, /* ASI DIN MIXER, ASI CH2 to RDAC2 coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH2_RDAC2_MIX_BYT2  = 0x15, /* ASI DIN MIXER, ASI CH2 to RDAC2 coefficient byte[7:0] */
    REG_ASI_DIN_MIX_ASI_CH2_LDAC2_MIX_BYT1  = 0x16, /* ASI DIN MIXER, ASI CH2 to LDAC2 coefficient byte[15:8] */
    REG_ASI_DIN_MIX_ASI_CH2_LDAC2_MIX_BYT2  = 0x17, /* ASI DIN MIXER, ASI CH2 to LDAC2 coefficient byte[7:0] */
}
tad5212_page_17_reg_addr_t;

#endif /* __TAD5212_REGS_PAGE_17_H__ */