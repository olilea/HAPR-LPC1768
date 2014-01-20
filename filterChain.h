// Created by Oliver Lea 17/01/2014

#ifndef __FILTERCHAIN_H__
#define __FILTERCHAIN_H__

typedef struct FilterNode {
	Filter *filter;
	struct FilterNode *next;
} FilterNode;

int enqueue(Filter *newFilter);

int dequeue(Filter *targetFilter);

void incrementCurrentNode(void);

uint16_t applyFilters(uint16_t sample);

int chain_init(void);

#endif