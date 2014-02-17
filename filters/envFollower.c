#include "lpc_types.h"

#include <math.h>

#include "../filter.h"
#include "envFollower.h"
#include "../debug.h"
#include "../global.h"

#define WINDOW_SIZE 30

#define ATTACK_COEFF filter->scratch[0]
#define RELEASE_COEFF filter->scratch[1]

//static uint32_t envWindow[WINDOW_SIZE];
//static uint8_t oldestElem;

uint32_t envelope = 0;

// See and reference:
// http://www.kvraudio.com/forum/viewtopic.php?p=5178628
//http://www.musicdsp.org/archive.php?classid=2

// ONLY ONE ENVELOPE FOLLOWER CAN BE IN THE FILTER CHAIN AT ANY
// ONE TIME
uint32_t envFollowerF(uint32_t sample, SFilter *filter) {

  //attack, follow rising wave
  if (sample > envelope) {
    envelope = ATTACK_COEFF * (envelope - sample) + sample;
  } else {
  //release, follow falling wave
    envelope = RELEASE_COEFF  * (envelope - sample) + sample;
  }
  
  return envelope;

}
/*
  //envWindow[oldestElem] = sample;
	if (oldestElem == (WINDOW_SIZE - 1)) {
		oldestElem = 0;
	} else {
		oldestElem++;
	}

	uint32_t max = 0;
	
	int i;
	for (i = 0; i < WINDOW_SIZE; i++) {

		if (envWindow[i] > max) {
			max = envWindow[i];
		}
	}

	// Implements attack
	if (sample > max) {
		//max = max * ATTACK_MULT;
		max = ATTACK_COEFF * (max - sample) + sample;
	} else { // Implements release
		//max = max * RELEASE_MULT;
		max = RELEASE_COEFF * (max - sample) + sample;
	}

	envWindow[oldestElem] = sample;

//	printfToTerminal("Intial: %d, final: %d\n\r", sample, max);

	return max;
*/

void printEnvFollowerF(SFilter *filter) {

	printfToTerminal("Envelope Follower:\n\r\t\tAttack (ms): %f\n\r\t\tRelease (ms): %f\n\r\r",
			filter->parameters[0], filter->parameters[1]);
}

// Initalises the necessary coefficients for implementing attack and
// release
Filter *createEnvFollowerF(float attack_ms, float release_ms) {
	
	Filter *envFollow = createFilterS(&envFollowerF, &printEnvFollowerF, attack_ms, release_ms,
			UNUSED, UNUSED, UNUSED);

	(envFollow->sfilter)->scratch[0] = exp(log(0.01) / (attack_ms * ADC_SAMPLE_RATE * 0.001));
	(envFollow->sfilter)->scratch[1] = exp(0.01 / (release_ms * ADC_SAMPLE_RATE * 0.001));

	return envFollow;
}
