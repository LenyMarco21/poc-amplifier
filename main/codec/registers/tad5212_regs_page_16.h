/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definition of TAD5212 registers - Page 16 - Biquad filters 7 - 12
 * 
 * No licence
 */

#ifndef __TAD5212_REGS_PAGE_16_H__
#define __TAD5212_REGS_PAGE_16_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Enumerations ***********************************************************************/

/* TAD5212 register map */
typedef enum
{
    /* DAC Biquad 9 registers */

    REG_DAC_BQ9_N0_B1   = 0x30, /* DAC Biquad 9 Numerator Coefficient 0 MSB */
    REG_DAC_BQ9_N0_B2   = 0x31, /* DAC Biquad 9 Numerator Coefficient 0 */
    REG_DAC_BQ9_N0_B3   = 0x32, /* DAC Biquad 9 Numerator Coefficient 0 */
    REG_DAC_BQ9_N0_B4   = 0x33, /* DAC Biquad 9 Numerator Coefficient 0 LSB */

    REG_DAC_BQ9_N1_B1   = 0x34, /* DAC Biquad 9 Numerator Coefficient 1 MSB */
    REG_DAC_BQ9_N1_B2   = 0x35, /* DAC Biquad 9 Numerator Coefficient 1 */
    REG_DAC_BQ9_N1_B3   = 0x36, /* DAC Biquad 9 Numerator Coefficient 1 */
    REG_DAC_BQ9_N1_B4   = 0x37, /* DAC Biquad 9 Numerator Coefficient 1 LSB */

    REG_DAC_BQ9_N2_B1   = 0x38, /* DAC Biquad 9 Numerator Coefficient 2 MSB */
    REG_DAC_BQ9_N2_B2   = 0x39, /* DAC Biquad 9 Numerator Coefficient 2 */
    REG_DAC_BQ9_N2_B3   = 0x3A, /* DAC Biquad 9 Numerator Coefficient 2 */
    REG_DAC_BQ9_N2_B4   = 0x3B, /* DAC Biquad 9 Numerator Coefficient 2 LSB */

    REG_DAC_BQ9_D1_B1   = 0x3C, /* DAC Biquad 9 Denominator Coefficient 1 MSB */
    REG_DAC_BQ9_D1_B2   = 0x3D, /* DAC Biquad 9 Denominator Coefficient 1 */
    REG_DAC_BQ9_D1_B3   = 0x3E, /* DAC Biquad 9 Denominator Coefficient 1 */
    REG_DAC_BQ9_D1_B4   = 0x3F, /* DAC Biquad 9 Denominator Coefficient 1 LSB */

    REG_DAC_BQ9_D2_B1   = 0x40, /* DAC Biquad 9 Denominator Coefficient 2 MSB */
    REG_DAC_BQ9_D2_B2   = 0x41, /* DAC Biquad 9 Denominator Coefficient 2 */
    REG_DAC_BQ9_D2_B3   = 0x42, /* DAC Biquad 9 Denominator Coefficient 2 */
    REG_DAC_BQ9_D2_B4	= 0x43,	/* DAC Biquad 9 Denominator Coefficient 2 LSB */

    /* DAC Biquad 10 registers */

    REG_DAC_BQ10_N0_B1   = 0x44, /* DAC Biquad 10 Numerator Coefficient 0 MSB */
    REG_DAC_BQ10_N0_B2   = 0x45, /* DAC Biquad 10 Numerator Coefficient 0 */
    REG_DAC_BQ10_N0_B3   = 0x46, /* DAC Biquad 10 Numerator Coefficient 0 */
    REG_DAC_BQ10_N0_B4   = 0x47, /* DAC Biquad 10 Numerator Coefficient 0 LSB */

    REG_DAC_BQ10_N1_B1   = 0x48, /* DAC Biquad 10 Numerator Coefficient 1 MSB */
    REG_DAC_BQ10_N1_B2   = 0x49, /* DAC Biquad 10 Numerator Coefficient 1 */
    REG_DAC_BQ10_N1_B3   = 0x4A, /* DAC Biquad 10 Numerator Coefficient 1 */
    REG_DAC_BQ10_N1_B4   = 0x4B, /* DAC Biquad 10 Numerator Coefficient 1 LSB */

    REG_DAC_BQ10_N2_B1   = 0x4C, /* DAC Biquad 10 Numerator Coefficient 2 MSB */
    REG_DAC_BQ10_N2_B2   = 0x4D, /* DAC Biquad 10 Numerator Coefficient 2 */
    REG_DAC_BQ10_N2_B3   = 0x4E, /* DAC Biquad 10 Numerator Coefficient 2 */
    REG_DAC_BQ10_N2_B4   = 0x4F, /* DAC Biquad 10 Numerator Coefficient 2 LSB */

    REG_DAC_BQ10_D1_B1   = 0x50, /* DAC Biquad 10 Denominator Coefficient 1 MSB */
    REG_DAC_BQ10_D1_B2   = 0x51, /* DAC Biquad 10 Denominator Coefficient 1 */
    REG_DAC_BQ10_D1_B3   = 0x52, /* DAC Biquad 10 Denominator Coefficient 1 */
    REG_DAC_BQ10_D1_B4   = 0x53, /* DAC Biquad 10 Denominator Coefficient 1 LSB */

    REG_DAC_BQ10_D2_B1   = 0x54, /* DAC Biquad 10 Denominator Coefficient 2 MSB */
    REG_DAC_BQ10_D2_B2   = 0x55, /* DAC Biquad 10 Denominator Coefficient 2 */
    REG_DAC_BQ10_D2_B3   = 0x56, /* DAC Biquad 10 Denominator Coefficient 2 */
    REG_DAC_BQ10_D2_B4   = 0x57, /* DAC Biquad 10 Denominator Coefficient 2 LSB */
}
tad5212_page_16_reg_addr_t;

#endif /* __TAD5212_REGS_PAGE_16_H__ */