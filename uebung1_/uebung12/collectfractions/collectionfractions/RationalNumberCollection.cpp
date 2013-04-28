#include <stdio.h>
#include "RationalNumberCollection.h";
#include <assert.h>

using namespace std;

void rncInit(RationalNumberCollection &c) {
    c.maxLength = 1000;
    c.rationalNumbers = rationalNumbers[maxLength];
    c.amount = new int[maxLength];
    c.curSize = 0;
}

void rncAdd(RationalNumberCollection &c, RationalNumber n);

void rncRemove();

void rncSum();

void rncAverage();

void rncCount();

void rncTotalCount();

void rncTotalUniqueCount();


