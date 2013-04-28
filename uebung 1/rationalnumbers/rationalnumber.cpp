#include <limits.h>
#include "rationalnumber.h"


RationalNumber rnNormalize(RationalNumber rn) {
    if (rnIsNaN(rn)) {  // avoid division by zero for {0,0}
        return rn;
    }
    int _gcd = gcd(rn.nominator, rn.denominator);
    return (RationalNumber) {rn.nominator / _gcd, rn.denominator / _gcd};
}

RationalNumber rnInvert(RationalNumber rn) {
    if (rnIsNaN(rn)) {  // don't produce a ZERO from NAN
        return rn;
    }
    return (RationalNumber) {rn.denominator, rn.nominator};
}

bool rnIsValid(RationalNumber n){
    return n.denominator != 0;
}

bool rnIsNaN(RationalNumber n){
    return !rnIsValid(n);
}

bool rnEqual(RationalNumber n1, RationalNumber n2){
    if (rnIsNaN(n1) || rnIsNaN(n2)) {
        return false;
    }
    n1 = rnNormalize(n1);
    n2 = rnNormalize(n2);
    return n1.nominator == n2.nominator && n1.denominator == n2.denominator;
}

bool rnLessThan(RationalNumber n1, RationalNumber n2){
    if (rnIsNaN(n1) || rnIsNaN(n2)) {
        return false;
    }
    return rnIsNegative(rnSubtract(n1,n2));
}

RationalNumber rnAdd(RationalNumber n1, RationalNumber n2){
    int n1denominator = n1.denominator;
    n1.denominator = n1.denominator*n2.denominator;
    n1.nominator = n1.nominator*n2.denominator;
    n2.denominator = n2.denominator*n1denominator;
    n2.nominator = n2.nominator*n1denominator;

    n1.nominator += n2.nominator;
    return rnNormalize(n1);
}

RationalNumber rnSubtract(RationalNumber n1, RationalNumber n2){
    n2.nominator *= -1;
    return rnAdd(n1,n2);
}

RationalNumber rnMultiply(RationalNumber factor1, RationalNumber factor2) {
    RationalNumber product = {factor1.nominator * factor2.nominator, factor1.denominator * factor2.denominator};
    return rnNormalize(product);
}

RationalNumber rnDivide(RationalNumber divident, RationalNumber divisor) {
    return rnMultiply(divident, rnInvert(divisor));
}
