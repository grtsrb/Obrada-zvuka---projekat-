/*
 * This file is automatically generated by CLIDE
 *
 * MCV (Module Control Vector)
 */

#include <dsplib/platform_support.h>
#include <dsplib/cl_os.h> 
#include <dsplib/meter.h>
#include <dsplib/response.h>
#include <example_composer_module_common.h>

#define	M70_PI_simple_gain_db_6_default_gain 	 1.0
#define	M70_PI_simple_gain_db_6_gain_max 	 2.0


typedef struct {
	fract Gain;	 //fract(9.23)
	bool signal_invert;	 //bool
} M70_PI_simple_gain_db_6_PUBLIC_DATA_t;

typedef struct {
} M70_PI_simple_gain_db_6_PRIVATE_DATA_2_t;

typedef struct {
	int __memX* bypass;	 //int __memX*
	fract __memY* __memY* input_ptr;	 //fract(1.31) __memY* __memY*
	fract __memY* __memY* output_ptr;	 //fract(1.31) __memY* __memY*
} M70_PI_simple_gain_db_6_PRIVATE_DATA_1_t;




