#include "lpc_types.h"

#include <stdlib.h>
#include <math.h>

#include "../filter.h"
#include "overDrive.h"
#include "../global.h"
#include "../debug.h"

//#define DRIVE filter->scratch[0]
#define GAIN filter->scratch[0]

uint32_t overdriveF(uint32_t sample, SFilter *filter) {

	uint32_t output;

	//Drive much be between 0 and 100
	//X Should be between 0 and 1
	
	output = GAIN;

	//printfToTerminal("Output is: %d", output);
	
	return output;
}

void printOverdriveF(SFilter *filter) {

	printfToTerminal("Overdrive: \n\r\t\tGain: %f\n\r\t\t",
			filter->parameters[0]);
}

Filter *createOverdriveF(float boost) {
	
	Filter *overdriveFilter = createFilterS(&overdriveF, &printOverdriveF,
			boost, UNUSED, UNUSED, UNUSED, UNUSED);

	//float a = sin(((inputDrive+1)/101)*(3.14/2));
	//float k = (2*a) / (1-a);
	//float drive = ((1+k)*(x)) / (1+k*abs(x)); //Main equation for drive, needs a & k above
	//float gain = ((boost/100)*100)+1; // Main equation for gain
	float gain = (2*sample) +(1-(2-(3*sample))*(2-(3*sample)) /3) //Boost between 0.33 and 0.66
	printfToTerminal("Gain: %f\n\r", gain);

	//(overdriveFilter->sfilter)->scratch[0] = drive;
	(overdriveFilter->sfilter)->scratch[0] = gain;

	return overdriveFilter;
}
