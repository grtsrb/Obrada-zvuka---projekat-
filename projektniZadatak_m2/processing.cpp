#include "common.h"
#include "processing.h"

/*double saturation(double in, double threshold)
{
	// Simple limiter since we know that pre-Gain adds 6dB
	if (in > threshold)
	{
		return fmin(in, threshold);
	}
	else if (in < -threshold)
	{
		return fmax(in, -threshold);
	}

	return in;
}*/
static DSPfract tremoloBuffer[TREMOLO_NUM_CHANNELS][BLOCK_SIZE];
DSPfract input_gain = fract(0);
DSPfract headroom_gain = fract(0);
DSPint mode;
tremolo_struct_t tremolo;
tremolo_struct_t* tremolo_ptr = &tremolo;

void initialize(DSPfract input_gain_func, DSPfract headroom_gain_func, DSPint mode_func)
{
	input_gain = input_gain_func;
	headroom_gain = headroom_gain_func;
	mode = mode_func;
}


void gainProcessing(DSPfract pIn[][BLOCK_SIZE], DSPfract pOut[][BLOCK_SIZE])
{
	DSPfract sum;

	init(tremolo_ptr);

	DSPfract* p_in_left = *(pIn + LEFT_CH);
	DSPfract* p_in_right = *(pIn + RIGHT_CH);

	DSPfract* p_in_tempL = *(tremoloBuffer + LEFT_CH);
	DSPfract* p_in_tempR = *(tremoloBuffer + RIGHT_CH);

	DSPfract* p_out_left = *(pOut + LEFT_CH);
	DSPfract* p_out_right = *(pOut + RIGHT_CH);
	DSPfract* p_out_center = *(pOut + CENTER_CH);
	DSPfract* p_out_LS = *(pOut + LEFTS_CH);
	DSPfract* p_out_RS = *(pOut + RIGHTS_CH);

	for (DSPint i = 0; i < BLOCK_SIZE; i++)
	{	

		// Multiply with -6db
		*p_in_left = *p_in_left * input_gain;
		*p_in_right = *p_in_right * input_gain;

		*p_in_tempL = *p_in_left;
		*p_in_tempR = *p_in_right;

		if (mode != OM0_2_0)
		{
			// Sum of left and right channel and multiply the sum with -3db
			sum = (*p_in_left + *p_in_right) * headroom_gain;

			// Output for left, right and center channel

			*p_out_left = sum * fract(MINUS_6DB);
			*p_out_right = sum * fract(MINUS_6DB);
		}

		if (mode == OM3_2_0)
		{
			*p_out_center = sum;
			p_out_center++;
		}
		p_in_left++;
		p_in_right++;
		p_in_tempL++;
		p_in_tempR++;
		p_out_left++;
		p_out_right++;
	}

	// Tremolo processing for Ls and Rs
	// void processBlock(double* input, double* output, tremolo_struct_t* data, int numSamples);

	if (mode != OM2_0_0)
	{
		p_in_tempL = *(tremoloBuffer + LEFT_CH);
		p_in_tempR = *(tremoloBuffer + RIGHT_CH);

		processBlock(p_in_tempL, p_in_tempL, tremolo_ptr);
		init(tremolo_ptr);
		processBlock(p_in_tempR, p_in_tempR, tremolo_ptr);


		for (int i = 0; i < BLOCK_SIZE; i++)
		{
			*p_out_LS = *p_in_tempL * FRACT_NUM(MINUS_2DB);
			*p_out_RS = *p_in_tempR * FRACT_NUM(MINUS_2DB);


			p_in_tempL++;
			p_in_tempR++;
			p_out_LS++;
			p_out_RS++;
		}
	}
}