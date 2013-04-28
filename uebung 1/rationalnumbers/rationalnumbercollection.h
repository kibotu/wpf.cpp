#include <limits.h>
#include "rationalnumber.h"

#ifndef RATIONALNUMBERCOLLECTION_H
#define RATIONALNUMBERCOLLECTION_H

const unsigned int RNC_MAX_SIZE = UINT_MAX >> (sizeof(RationalNumber) - 1);

struct RationalNumberCollection {
    unsigned int capacity;
    unsigned int size;
    RationalNumber* data;
};

RationalNumberCollection* rncInit(const unsigned int capacity = 10u);

void rncAdd(RationalNumberCollection* rnc, const RationalNumber* rn);

void rncRemove();

void rncSum();

void rncAverage();

void rncCount();

void rncTotalCount();

void rncTotalUniqueCount();

unsigned int rncSize(const RationalNumberCollection* rnc);

void rncResize(RationalNumberCollection* rnc, const unsigned int toCapacity);

unsigned int rncCapacity(const RationalNumberCollection* rnc);

void rncSet(RationalNumberCollection* rnc, const unsigned int index, const RationalNumber* rn);

RationalNumber* rncGet(RationalNumberCollection* rnc, const unsigned int index);

void rncRemove(RationalNumberCollection* rnc, const unsigned int startIndex, const unsigned int endIndex);

#endif // RATIONALNUMBERCOLLECTION_H
