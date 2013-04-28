#include <limits.h>
#include "rationalnumber.h"

int gcd(int a, int b) {
    int tmp;
    while (b != 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

inline unsigned int absUnsigned(int i) {
    return i < 0 ? -i : i;
}

inline bool rnIsNegative(RationalNumber rn) {
    if (rnIsNaN(rn)) return false;
    return (rn.numerator < 0) ^ (rn.denominator < 0);
}

RationalNumber rnNormalize(RationalNumber rn) {
    if (rnIsNaN(rn)) return rn;
    int _gcd = gcd(rn.numerator, rn.denominator);
    return (RationalNumber) {rn.numerator / _gcd, rn.denominator / _gcd};
}

RationalNumber rnInvert(RationalNumber rn) {
    if (rnIsNaN(rn)) return rn;
    return (RationalNumber) {rn.denominator, rn.numerator};
}

bool rnIsValid(RationalNumber n){
    return n.denominator != 0;
}

bool rnIsNaN(RationalNumber n){
    return !rnIsValid(n);
}

bool rnEqual(RationalNumber n1, RationalNumber n2){
    if (rnIsNaN(n1) || rnIsNaN(n2)) return false;
    n1 = rnNormalize(n1);
    n2 = rnNormalize(n2);
    return n1.numerator == n2.numerator && n1.denominator == n2.denominator;
}

bool rnLessThan(RationalNumber n1, RationalNumber n2){
    return rnIsNaN(n1) || rnIsNaN(n2) ? false : rnIsNegative(rnSubtract(n1,n2));
}

RationalNumber rnAdd(RationalNumber n1, RationalNumber n2){
    int n1denominator = n1.denominator;
    n1.denominator = n1.denominator*n2.denominator;
    n1.numerator = n1.numerator*n2.denominator;
    n2.denominator = n2.denominator*n1denominator;
    n2.numerator = n2.numerator*n1denominator;
    n1.numerator += n2.numerator;
    return rnNormalize(n1);
}

RationalNumber rnSubtract(RationalNumber n1, RationalNumber n2){
    n2.numerator *= -1;
    return rnAdd(n1,n2);
}

RationalNumber rnMultiply(RationalNumber factor1, RationalNumber factor2) {
    RationalNumber product = {factor1.numerator * factor2.numerator, factor1.denominator * factor2.denominator};
    return rnNormalize(product);
}

RationalNumber rnDivide(RationalNumber divident, RationalNumber divisor) {
    return rnMultiply(divident, rnInvert(divisor));
}
