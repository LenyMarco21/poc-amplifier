/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definition of TAD5212 registers - Page 15 - Biquad filters 1 - 6
 * 
 * No licence
 */

#ifndef __TAD5212_REGS_PAGE_15_H__
#define __TAD5212_REGS_PAGE_15_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Enumerations ***********************************************************************/

/* TAD5212 register map */
typedef enum
{
    /* DAC Biquad 1 registers */

    REG_DAC_BQ1_N0_B1   = 0x08, /* DAC Biquad 1 Numerator Coefficient 0 MSB */
    REG_DAC_BQ1_N0_B2   = 0x09, /* DAC Biquad 1 Numerator Coefficient 0 */
    REG_DAC_BQ1_N0_B3   = 0x0A, /* DAC Biquad 1 Numerator Coefficient 0 */
    REG_DAC_BQ1_N0_B4   = 0x0B, /* DAC Biquad 1 Numerator Coefficient 0 LSB */

    REG_DAC_BQ1_N1_B1   = 0x0C, /* DAC Biquad 1 Numerator Coefficient 1 MSB */
    REG_DAC_BQ1_N1_B2   = 0x0D, /* DAC Biquad 1 Numerator Coefficient 1 */
    REG_DAC_BQ1_N1_B3   = 0x0E, /* DAC Biquad 1 Numerator Coefficient 1 */
    REG_DAC_BQ1_N1_B4   = 0x0F, /* DAC Biquad 1 Numerator Coefficient 1 LSB */

    REG_DAC_BQ1_N2_B1   = 0x10, /* DAC Biquad 1 Numerator Coefficient 2 MSB */
    REG_DAC_BQ1_N2_B2   = 0x11, /* DAC Biquad 1 Numerator Coefficient 2 */
    REG_DAC_BQ1_N2_B3   = 0x12, /* DAC Biquad 1 Numerator Coefficient 2 */
    REG_DAC_BQ1_N2_B4   = 0x13, /* DAC Biquad 1 Numerator Coefficient 2 LSB */

    REG_DAC_BQ1_D1_B1   = 0x14, /* DAC Biquad 1 Denominator Coefficient 1 MSB */
    REG_DAC_BQ1_D1_B2   = 0x15, /* DAC Biquad 1 Denominator Coefficient 1 */
    REG_DAC_BQ1_D1_B3   = 0x16, /* DAC Biquad 1 Denominator Coefficient 1 */
    REG_DAC_BQ1_D1_B4   = 0x17, /* DAC Biquad 1 Denominator Coefficient 1 LSB */

    REG_DAC_BQ1_D2_B1   = 0x18, /* DAC Biquad 1 Denominator Coefficient 2 MSB */
    REG_DAC_BQ1_D2_B2   = 0x19, /* DAC Biquad 1 Denominator Coefficient 2 */
    REG_DAC_BQ1_D2_B3   = 0x1A, /* DAC Biquad 1 Denominator Coefficient 2 */
    REG_DAC_BQ1_D2_B4   = 0x1B, /* DAC Biquad 1 Denominator Coefficient 2 LSB */

    /* DAC Biquad 2 registers */

    REG_DAC_BQ2_N0_B1   = 0x1C, /* DAC Biquad 2 Numerator Coefficient 0 MSB */
    REG_DAC_BQ2_N0_B2   = 0x1D, /* DAC Biquad 2 Numerator Coefficient 0 */
    REG_DAC_BQ2_N0_B3   = 0x1E, /* DAC Biquad 2 Numerator Coefficient 0 */
    REG_DAC_BQ2_N0_B4   = 0x1F, /* DAC Biquad 2 Numerator Coefficient 0 LSB */

    REG_DAC_BQ2_N1_B1   = 0x20, /* DAC Biquad 2 Numerator Coefficient 1 MSB */
    REG_DAC_BQ2_N1_B2   = 0x21, /* DAC Biquad 2 Numerator Coefficient 1 */
    REG_DAC_BQ2_N1_B3   = 0x22, /* DAC Biquad 2 Numerator Coefficient 1 */
    REG_DAC_BQ2_N1_B4   = 0x23, /* DAC Biquad 2 Numerator Coefficient 1 LSB */

    REG_DAC_BQ2_N2_B1   = 0x24, /* DAC Biquad 2 Numerator Coefficient 2 MSB */
    REG_DAC_BQ2_N2_B2   = 0x25, /* DAC Biquad 2 Numerator Coefficient 2 */
    REG_DAC_BQ2_N2_B3   = 0x26, /* DAC Biquad 2 Numerator Coefficient 2 */
    REG_DAC_BQ2_N2_B4   = 0x27, /* DAC Biquad 2 Numerator Coefficient 2 LSB */

    REG_DAC_BQ2_D1_B1   = 0x28, /* DAC Biquad 2 Denominator Coefficient 1 MSB */
    REG_DAC_BQ2_D1_B2   = 0x29, /* DAC Biquad 2 Denominator Coefficient 1 */
    REG_DAC_BQ2_D1_B3   = 0x2A, /* DAC Biquad 2 Denominator Coefficient 1 */
    REG_DAC_BQ2_D1_B4   = 0x2B, /* DAC Biquad 2 Denominator Coefficient 1 LSB */

    REG_DAC_BQ2_D2_B1   = 0x2C, /* DAC Biquad 2 Denominator Coefficient 2 MSB */
    REG_DAC_BQ2_D2_B2   = 0x2D, /* DAC Biquad 2 Denominator Coefficient 2 */
    REG_DAC_BQ2_D2_B3   = 0x2E, /* DAC Biquad 2 Denominator Coefficient 2 */
    REG_DAC_BQ2_D2_B4   = 0x2F, /* DAC Biquad 2 Denominator Coefficient 2 LSB */

    /* DAC Biquad 5 registers */

    REG_DAC_BQ5_N0_B1   = 0x58, /* DAC Biquad 5 Numerator Coefficient 0 MSB */
    REG_DAC_BQ5_N0_B2   = 0x59, /* DAC Biquad 5 Numerator Coefficient 0 */
    REG_DAC_BQ5_N0_B3   = 0x5A, /* DAC Biquad 5 Numerator Coefficient 0 */
    REG_DAC_BQ5_N0_B4   = 0x5B, /* DAC Biquad 5 Numerator Coefficient 0 LSB */

    REG_DAC_BQ5_N1_B1   = 0x5C, /* DAC Biquad 5 Numerator Coefficient 1 MSB */
    REG_DAC_BQ5_N1_B2   = 0x5D, /* DAC Biquad 5 Numerator Coefficient 1 */
    REG_DAC_BQ5_N1_B3   = 0x5E, /* DAC Biquad 5 Numerator Coefficient 1 */
    REG_DAC_BQ5_N1_B4   = 0x5F, /* DAC Biquad 5 Numerator Coefficient 1 LSB */

    REG_DAC_BQ5_N2_B1   = 0x60, /* DAC Biquad 5 Numerator Coefficient 2 MSB */
    REG_DAC_BQ5_N2_B2   = 0x61, /* DAC Biquad 5 Numerator Coefficient 2 */
    REG_DAC_BQ5_N2_B3   = 0x62, /* DAC Biquad 5 Numerator Coefficient 2 */
    REG_DAC_BQ5_N2_B4   = 0x63, /* DAC Biquad 5 Numerator Coefficient 2 LSB */

    REG_DAC_BQ5_D1_B1   = 0x64, /* DAC Biquad 5 Denominator Coefficient 1 MSB */
    REG_DAC_BQ5_D1_B2   = 0x65, /* DAC Biquad 5 Denominator Coefficient 1 */
    REG_DAC_BQ5_D1_B3   = 0x66, /* DAC Biquad 5 Denominator Coefficient 1 */
    REG_DAC_BQ5_D1_B4   = 0x67, /* DAC Biquad 5 Denominator Coefficient 1 LSB */

    REG_DAC_BQ5_D2_B1   = 0x68, /* DAC Biquad 5 Denominator Coefficient 2 MSB */
    REG_DAC_BQ5_D2_B2   = 0x69, /* DAC Biquad 5 Denominator Coefficient 2 */
    REG_DAC_BQ5_D2_B3   = 0x6A, /* DAC Biquad 5 Denominator Coefficient 2 */
    REG_DAC_BQ5_D2_B4   = 0x6B, /* DAC Biquad 5 Denominator Coefficient 2 LSB */

    /* DAC Biquad 6 registers */

    REG_DAC_BQ6_N0_B1   = 0x6C, /* DAC Biquad 6 Numerator Coefficient 0 MSB */
    REG_DAC_BQ6_N0_B2   = 0x6D, /* DAC Biquad 6 Numerator Coefficient 0 */
    REG_DAC_BQ6_N0_B3   = 0x6E, /* DAC Biquad 6 Numerator Coefficient 0 */
    REG_DAC_BQ6_N0_B4   = 0x6F, /* DAC Biquad 6 Numerator Coefficient 0 LSB */

    REG_DAC_BQ6_N1_B1   = 0x70, /* DAC Biquad 6 Numerator Coefficient 1 MSB */
    REG_DAC_BQ6_N1_B2   = 0x71, /* DAC Biquad 6 Numerator Coefficient 1 */
    REG_DAC_BQ6_N1_B3   = 0x72, /* DAC Biquad 6 Numerator Coefficient 1 */
    REG_DAC_BQ6_N1_B4   = 0x73, /* DAC Biquad 6 Numerator Coefficient 1 LSB */

    REG_DAC_BQ6_N2_B1   = 0x74, /* DAC Biquad 6 Numerator Coefficient 2 MSB */
    REG_DAC_BQ6_N2_B2   = 0x75, /* DAC Biquad 6 Numerator Coefficient 2 */
    REG_DAC_BQ6_N2_B3   = 0x76, /* DAC Biquad 6 Numerator Coefficient 2 */
    REG_DAC_BQ6_N2_B4   = 0x77, /* DAC Biquad 6 Numerator Coefficient 2 LSB */

    REG_DAC_BQ6_D1_B1   = 0x78, /* DAC Biquad 6 Denominator Coefficient 1 MSB */
    REG_DAC_BQ6_D1_B2   = 0x79, /* DAC Biquad 6 Denominator Coefficient 1 */
    REG_DAC_BQ6_D1_B3   = 0x7A, /* DAC Biquad 6 Denominator Coefficient 1 */
    REG_DAC_BQ6_D1_B4   = 0x7B, /* DAC Biquad 6 Denominator Coefficient 1 LSB */

    REG_DAC_BQ6_D2_B1   = 0x7C, /* DAC Biquad 6 Denominator Coefficient 2 MSB */
    REG_DAC_BQ6_D2_B2   = 0x7D, /* DAC Biquad 6 Denominator Coefficient 2 */
    REG_DAC_BQ6_D2_B3   = 0x7E, /* DAC Biquad 6 Denominator Coefficient 2 */
    REG_DAC_BQ6_D2_B4   = 0x7F, /* DAC Biquad 6 Denominator Coefficient 2 LSB */
}
tad5212_page_15_reg_addr_t;

#endif /* __TAD5212_REGS_PAGE_15_H__ */