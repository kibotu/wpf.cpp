#ifndef RATIONALNUMBERCOLLECTION_H
#define RATIONALNUMBERCOLLECTION_H

#endif // RATIONALNUMBERCOLLECTION_H

struct RationalNumberCollection {
    int maxLength;
    RationalNumber rationalNumbers;
    int amount;
    int curSize;
};

void rncInit(RationalNumberCollection &c);

void rncAdd(RationalNumberCollection &c, RationalNumber n);

void rncRemove();

void rncSum();

void rncAverage();

void rncCount();

void rncTotalCount();

void rncTotalUniqueCount();
