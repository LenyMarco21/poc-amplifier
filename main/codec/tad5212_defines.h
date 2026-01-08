/**
 * Written by Leny Marcolini - ESEO - 2026
 *
 * Definitions of TAD5212 driver
 * 
 * No licence
 */

#ifndef __TAD5212_DEFINES_H__
#define __TAD5212_DEFINES_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*** Defines ***********************************************************************/

/* Minimum DAC volume (-60dB) */
#define TAD5212_DAC_MIN_VOLUME          81

/* Maximum DAC volume (0dB) */
#define TAD5212_DAC_MAX_VOLUME          201

/* Volume step */
#define TAD5212_DAC_VOLUME_STEP         ((TAD5212_DAC_MAX_VOLUME - TAD5212_DAC_MIN_VOLUME) / 100.0)

#endif /* __TAD5212_DEFINES_H__ */