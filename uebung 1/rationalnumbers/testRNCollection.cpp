#include "rationalnumbercollection.h"
#include "rationalnumber.h"
#include <assert.h>
#include <stdio.h>

void runCollectionTests(){
    printf("Performing RationalNumberCollection tests...\n");
    fflush(stdout);

    const unsigned int rncCap = 20;
    RationalNumberCollection* rnc = rncCreate(rncCap);

    // printf("%d",rnc->size); not working due hidden implementation

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
    assert(rncSize(rnc) == rncTotalCount(rnc));

    rncRemove(rnc,0,1);
    assert(rncSize(rnc) == 2);

    assert(rncGet(rnc,0)->numerator == rn2.numerator);
    assert(rncGet(rnc,0)->denominator == rn2.denominator);

    assert(rncGet(rnc,1)->numerator == rn3.numerator);
    assert(rncGet(rnc,1)->denominator == rn3.denominator);

    RationalNumber rn4 = {5, 7};
    rncAdd(rnc, &rn4);
    assert(rnEqual(rnAdd(rnAdd(rn2,rn3),rn4), rncSum(rnc)));
    assert(rnEqual(rnDivide(rnAdd(rnAdd(rn2,rn3),rn4),(RationalNumber) {3,1}) , rncAverage(rnc)));

    assert(rncCount(rnc,&rn4) == 1);
    rncAdd(rnc, &rn4);
    assert(rncCount(rnc,&rn4) == 2);
    assert(rncTotalUniqueCount(rnc) == 3  && rncSize(rnc) == 4);

    printf("successful!\n\n");
}
