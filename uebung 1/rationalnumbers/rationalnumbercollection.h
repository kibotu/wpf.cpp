#include <limits.h>
#include "rationalnumber.h"

#ifndef RATIONALNUMBERCOLLECTION_H
#define RATIONALNUMBERCOLLECTION_H

const unsigned int RNC_MAX_SIZE = UINT_MAX >> (sizeof(RationalNumber) - 1);

struct RationalNumberCollection;

RationalNumberCollection* rncCreate(const unsigned int capacity = 10u);

void rncDelete(RationalNumberCollection** rnc);

void rncAdd(RationalNumberCollection* rnc, const RationalNumber* rn);

void rncRemove(RationalNumberCollection* rnc, const unsigned int startIndex, const unsigned int endIndex);

RationalNumber rncSum(RationalNumberCollection* rnc);

RationalNumber rncAverage(RationalNumberCollection* rnc);

unsigned int rncCount(const RationalNumberCollection* rnc, const RationalNumber* rn);

unsigned int rncTotalCount(const RationalNumberCollection* rnc);

unsigned int rncTotalUniqueCount(const RationalNumberCollection* rnc);

unsigned int rncSize(const RationalNumberCollection* rnc);

void rncResize(RationalNumberCollection* rnc, const unsigned int toCapacity);

unsigned int rncCapacity(const RationalNumberCollection* rnc);

void rncSet(RationalNumberCollection* rnc, const unsigned int index, const RationalNumber* rn);

RationalNumber* rncGet(RationalNumberCollection* rnc, const unsigned int index);

void rncPrint(RationalNumberCollection* rnc);

#endif // RATIONALNUMBERCOLLECTION_H
