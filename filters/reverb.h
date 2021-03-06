// Created by Oliver Lea - 02/02/2014

// THIS FILE IS PART OF OLIVER LEA'S INDIVIDUAL SECTION

#ifndef __REVERB_H__
#define __REVERB_H__

uint32_t reverbF(uint32_t sample, SFilter *filter);

void printReverbF(SFilter *filter);

Filter *createReverbF(float mixingRatio, float delay);

#endif
