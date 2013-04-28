#include "rationalnumbercollection.h"
#include "rationalnumber.h"
#include <assert.h>
#include <stdio.h>

void runCollectionTests(){
    printf("Performing RationalNumberCollection tests... ");
    fflush(stdout);

    const unsigned int rncCap = 20;
    RationalNumberCollection* rnc = rncInit(rncCap);
    assert(rnc);
    assert(rncSize(rnc) == 0);
    assert(rncCapacity(rnc) == rncCap);

    RationalNumber rn1 = {7, 3};
    rncAdd(rnc, &rn1);
    assert(rncSize(rnc) == 1);

    rncResize(rnc,rncCap/2);
    assert(rncCapacity(rnc) == rncCap/2);

    RationalNumber rn2 = {19, 7};
    RationalNumber rn3 = {31, 11};
    rncAdd(rnc, &rn2);
    rncAdd(rnc, &rn3);

    assert(rncSize(rnc) == 3);

    rncRemove(rnc,0,1);
    assert(rncSize(rnc) == 2);

    assert(rncGet(rnc,0)->numerator == rn2.numerator);
    assert(rncGet(rnc,0)->denominator == rn2.denominator);

    assert(rncGet(rnc,1)->numerator == rn3.numerator);
    assert(rncGet(rnc,1)->denominator == rn3.denominator);

    printf("successful!\n");
}
