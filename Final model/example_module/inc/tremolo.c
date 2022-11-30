#include "common.h"
#ifndef TREMOLO_H
#define TREMOLO_H

#include <dsplib\dsp_math.h>

typedef enum

{
	kWaveformSine = 1,
	kWaveformTriangle,
} wave_forms_t;

typedef struct {
	DSPint numChannels;

	DSPfract LFO_frequency;  // LFO frequency (Hz)

	DSPfract depth;      // Depth of effect (0-1)

	wave_forms_t   waveform;      // What shape should be used for the LFO

	DSPfract lfoPhase;

	DSPfract inverseSampleRate;
} tremolo_struct_t;

DSPfract lfo(DSPfract phase, wave_forms_t waveform)

{

	switch (waveform)

	{

	case kWaveformTriangle:

		if (phase < FRACT_NUM(0.25))

			return FRACT_NUM(0.5) + (fract)((long)2 * phase);

		else if (phase < FRACT_NUM(0.75))

			return FRACT_NUM(1.0) - (fract)((long)2 * (phase - FRACT_NUM(0.25)));

		else

			return FRACT_NUM(2.0) * (phase - FRACT_NUM(0.75));

	case kWaveformSine:

	default:

		return FRACT_NUM(0.5) + FRACT_NUM(0.5) * cl_sin(phase << 1);

	}

}


#endif // !TREMOLO_H
