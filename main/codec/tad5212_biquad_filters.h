/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definitions of TAD5212 biquad filters
 * 
 * No licence
 */

#ifndef __TAD5212_BIQUAD_FILTERS_H__
#define __TAD5212_BIQUAD_FILTERS_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Enumerations ****************************************************************/

typedef enum
{
    TAD5212_DAC1_BIQUAD_FILTER_1 = 1,
    TAD5212_DAC2_BIQUAD_FILTER_1 = 2,
    TAD5212_DAC3_BIQUAD_FILTER_1 = 3,
    TAD5212_DAC4_BIQUAD_FILTER_1 = 4,
    TAD5212_DAC1_BIQUAD_FILTER_2 = 5,
    TAD5212_DAC2_BIQUAD_FILTER_2 = 6,
    TAD5212_DAC3_BIQUAD_FILTER_2 = 7,
    TAD5212_DAC4_BIQUAD_FILTER_2 = 8,
    TAD5212_DAC1_BIQUAD_FILTER_3 = 9,
    TAD5212_DAC2_BIQUAD_FILTER_3 = 10,
    TAD5212_DAC3_BIQUAD_FILTER_3 = 11,
    TAD5212_DAC4_BIQUAD_FILTER_3 = 12,
}
tad5212_biquad_filter_t;

/*** Structures ******************************************************************/

typedef union
{
    uint32_t value;

    struct
    {
        uint8_t byte4;
        uint8_t byte3;
        uint8_t byte2;
        uint8_t byte1;
    };
}
tad5212_biquad_word_t;

/* Biquad filter structure */
typedef struct
{
    tad5212_biquad_word_t n0;   /* Numerator Coefficient 0 */
    tad5212_biquad_word_t n1;   /* Numerator Coefficient 1 */
    tad5212_biquad_word_t n2;   /* Numerator Coefficient 2 */
    tad5212_biquad_word_t d1;   /* Denominator Coefficient 1 */
    tad5212_biquad_word_t d2;   /* Denominator Coefficient 2 */
} 
tad5212_biquad_coeffs_t;

/*** Filters ******************************************************************/

const static tad5212_biquad_coeffs_t TAD5212_BIQUAD_LOWPASS_150_HZ =
{
    .n0 = { .value = 0x0003B0BC },
    .n1 = { .value = 0x0003B0BC },
    .n2 = { .value = 0x0003B0BC },
    .d1 = { .value = 0x7E50E7E4 },
    .d2 = { .value = 0x834B2D38 },
};

const static tad5212_biquad_coeffs_t TAD5212_BIQUAD_HIGHPASS_150_HZ =
{
    .n0 = { .value = 0x7E1F4D68 },
    .n1 = { .value = 0x81E0B298 },
    .n2 = { .value = 0x7E1F4D68 },
    .d1 = { .value = 0x7E1B2C9F },
    .d2 = { .value = 0x8395C7A2 },
};

const static tad5212_biquad_coeffs_t TAD5212_BIQUAD_LOWPASS_16000_HZ =
{
    .n0 = { .value = 0x40A9C9E2 },
    .n1 = { .value = 0x40A9C9E2 },
    .n2 = { .value = 0x40A9C9E2 },
    .d1 = { .value = 0xD2E41E84 },
    .d2 = { .value = 0xD7DEEB24 },
};

#endif /* __TAD5212_BIQUAD_FILTERS_H__ */