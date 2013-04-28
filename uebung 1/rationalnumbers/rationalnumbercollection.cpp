#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rationalnumber.h"
#include "rationalnumbercollection.h"

inline bool isValidIndex(const RationalNumberCollection* rnc, const unsigned int i) {
    return rnc && i < rnc->size;
}

inline unsigned int computeNewCapacity(const unsigned int current, const unsigned int next) {
    const unsigned int tmp = (current * 3 + 1) / 2;
    return next > tmp || tmp > RNC_MAX_SIZE ? next : tmp;
}

bool rncEnsureCapacity(RationalNumberCollection* rnc, const unsigned int capacity) {
    if (!rnc) return false;
    if (rnc->capacity < capacity) {
        rncResize(rnc, computeNewCapacity(rnc->capacity, capacity));
    }
    return rnc->capacity >= capacity;
}

RationalNumberCollection* rncInit(unsigned int capacity){
    if (capacity > RNC_MAX_SIZE) capacity = RNC_MAX_SIZE;
    RationalNumberCollection* rnc = (RationalNumberCollection*) malloc(sizeof(RationalNumberCollection));
    if (!rnc) return NULL;
    rnc->size = 0;
    rnc->capacity = 0;
    rnc->data = NULL;
    rncResize(rnc, capacity);
    return rnc;
}

void rncResize(RationalNumberCollection* rnc, const unsigned int capacity){
    if(!rnc) return;
    RationalNumber* newNrs = (RationalNumber*) realloc(rnc->data, sizeof(RationalNumber)*capacity);
    rnc->data = newNrs;
    rnc->capacity = capacity;
}

unsigned int rncSize(const RationalNumberCollection* rnc){
    if (!rnc) return 0;
    return rnc->size;
}

unsigned int rncCapacity(const RationalNumberCollection* rnc){
    return (!rnc) ? 0 : rnc->capacity;
}

void rncAdd(RationalNumberCollection* rnc, const RationalNumber* rn) {
    if (!rnc) return;
    rncSet(rnc, rnc->size, rn);
}

void rncSet(RationalNumberCollection* rnc, const unsigned int index, const RationalNumber* rn) {
    const unsigned int sizeNeeded = index + 1;
    if (!rnc || !rncEnsureCapacity(rnc, sizeNeeded))  return;
    rnc->data[index] = *rn;
    if (sizeNeeded > rnc->size) {
        for (unsigned int i = rnc->size; i < index; i++) {
            rnc->data[i] = RN_ZERO;
        }
        rnc->size = sizeNeeded;
    }
}

void rncRemove(RationalNumberCollection* rnc, const unsigned int startIndex, const unsigned int endIndex) {
    if (!rnc || startIndex >= rnc->size || endIndex < startIndex || endIndex > rnc->size) return;
    const unsigned int delSize = endIndex - startIndex;
    const unsigned int movSize = rnc->size - endIndex;
    if (delSize && movSize) memmove(rnc->data + startIndex, rnc->data + endIndex, sizeof(RationalNumber) * movSize);
    rnc->size -= delSize;
}

RationalNumber* rncGet(RationalNumberCollection* rnc, const unsigned int index) {
    return (!rnc || !isValidIndex(rnc, index)) ? NULL : rnc->data + index;
}

RationalNumber rncSum(RationalNumberCollection* rnc) {
    RationalNumber rn = RN_ZERO;
    for (unsigned int i = 0; i < rnc->size; i++) rn = rnAdd(rn,rnc->data[i]);
    return rn;
}

RationalNumber rncAverage(RationalNumberCollection* rnc) {
    return rnDivide(rncSum(rnc),(RationalNumber){(int)rnc->size,1});
}

unsigned int rncCount(const RationalNumberCollection* rnc, const RationalNumber* rn) {
   int count = 0;
   for (unsigned int i = 0; i < rnc->size; i++) if(rnEqual(rnc->data[i],*rn)) count++;
   return count;
}

unsigned int rncTotalCount(const RationalNumberCollection* rnc) {
    return rnc->size;
}

unsigned int rncTotalUniqueCount(const RationalNumberCollection* rnc) {
    int count = 1;
    for (unsigned int i = 0; i < rnc->size; i++) if(rncCount(rnc, &rnc->data[i]) < 2) count++;
    return count;
}

void rncPrint(RationalNumberCollection* rnc) {
    printf("RationalNumberCollection: \n");
    printf("size: %d\n", rnc->size);
    printf("capacity: %d\n", rnc->capacity);
    for (unsigned int i = 0; i < rnc->size; i++) rnPrint(rnc->data[i]);
    printf("\n");
}
