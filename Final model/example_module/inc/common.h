
#ifndef _COMMON_H
#define _COMMON_H

#include <stdfix.h>
#include "stdfix_emu.h"
// potrebno prekopirati sa pocetka stdfix_emu.h ili ukljuciti ceo stdfix_emu.h!
#if defined(__CCC)

#include <stdfix.h>

#define FRACT_NUM(x) (x##r)
#define LONG_FRACT_NUM(x) (x##lr)
#define ACCUM_NUM(x) (x##lk)

#define FRACT_NUM_HEX(x) (x##r)

#define FRACT_TO_INT_BIT_CONV(x) (bitsr(x))
#define INT_TO_FRACT_BIT_CONV(x) (rbits(x))

#define long_accum long accum
#define long_fract long fract

#endif

#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 8

#define INPUT_NUM_CHANNELS 2
// Defined tremolo num channels
#define TREMOLO_NUM_CHANNELS 2



#define LEFT_CH 0
#define RIGHT_CH 1
#define CENTER_CH 2
#define LEFTS_CH 3
#define RIGHTS_CH 4

#define MINUS_6DB 0.50118
#define MINUS_2DB 0.794328
#define MINUS_3DB 0.707946

// Tremolo
#define SAMPLE_RATE 48000
#define PI 3.14159265358979323846

#define limiterThreshold = 0.999;

#define GAINPROC_ASM

enum OUTPUT_MODES
{
	OM2_0_0 = 0, //l & R
	OM0_2_0 = 1, // Ls & Rs
	OM3_2_0 = 2, // L & R & C & Ls & Rs
};
/* DSP type definitions */
typedef short DSPshort;					/* DSP integer */
typedef unsigned short DSPushort;		/* DSP unsigned integer */
typedef int DSPint;						/* native integer */
typedef fract DSPfract;					/* DSP fixed-point fractional, data reg, memory word format s.31 */
typedef long_accum DSPaccum;					/* DSP fixed-point fractional, accum reg format s8.63 */

#endif //_COMMON_H
