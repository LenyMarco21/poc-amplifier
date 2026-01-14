/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definitions of TAD5212 mixer
 * 
 * No licence
 */

#ifndef __TAD5212_MIXER_H__
#define __TAD5212_MIXER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Enumerations ****************************************************************/

typedef enum
{
    TAD5212_ASI_DIN_MIX_ASI_CH1 = 1,
    TAD5212_ASI_DIN_MIX_ASI_CH2 = 2,
    TAD5212_ASI_DIN_MIX_ASI_CH3 = 3,
    TAD5212_ASI_DIN_MIX_ASI_CH4 = 4,
    TAD5212_ASI_DIN_MIX_ASI_CH5 = 5,
    TAD5212_ASI_DIN_MIX_ASI_CH6 = 6,
    TAD5212_ASI_DIN_MIX_ASI_CH7 = 7,
    TAD5212_ASI_DIN_MIX_ASI_CH8 = 8,
}
tad5212_mixer_t;

typedef union
{
    uint16_t value;

    struct
    {
        uint8_t byte2;
        uint8_t byte1;
    };
}
tad5212_mixer_word_t;

/*** Structures ******************************************************************/

/* Biquad filter structure */
typedef struct
{
    tad5212_mixer_word_t a2;   /* Coefficient a2 */
    tad5212_mixer_word_t a1;   /* Coefficient a1 */
    tad5212_mixer_word_t a4;   /* Coefficient a4 */
    tad5212_mixer_word_t a3;   /* Coefficient a3 */
} 
tad5212_mixer_coeffs_t;

/*** Constantes ******************************************************************/

const static tad5212_mixer_coeffs_t TAD5212_MIXER_LDAC_DIV_2 =
{
    .a2 = { .value = 0x0000 },
    .a1 = { .value = 0x2000 },
    .a4 = { .value = 0x0000 },
    .a3 = { .value = 0x0000 },
};

const static tad5212_mixer_coeffs_t TAD5212_MIXER_RDAC_DIV_2 =
{
    .a2 = { .value = 0x2000 },
    .a1 = { .value = 0x0000 },
    .a4 = { .value = 0x0000 },
    .a3 = { .value = 0x0000 },
};

#endif /* __TAD5212_MIXER_H__ */