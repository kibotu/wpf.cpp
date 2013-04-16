
#include <stdio.h>
#include "rationalnumber.h";
#include <assert.h>

using namespace std;

bool rnIsValid(RationalNumber n) {
    return n.denominator != 0;
}

bool rnEqual(RationalNumber a, RationalNumber b) {
    if(!rnIsValid(a) || !rnIsValid(b)) return false;
    a = normalize(a);
    b = normalize(b);
    return a.denominator == b.denominator && a.numerator == b.numerator;
}

bool rnLessThan(RationalNumber a, RationalNumber b) {
    return true;
}

RationalNumber rnAdd(RationalNumber a, RationalNumber b){
    assert(rnIsValid(a) && rnIsValid(b));
    int n = a.numerator*b.denominator+b.numerator*a.denominator;
    int d = a.denominator*b.denominator;
    int gcd = getGCDIterative(n,d);
    RationalNumber result = {n/gcd,d/gcd};
    return result;
}

RationalNumber rnSubtract(RationalNumber a, RationalNumber b) {
    assert(rnIsValid(a) && rnIsValid(b));
    int n = a.numerator*b.denominator-b.numerator*a.denominator;
    int d = a.denominator*b.denominator;
    int gcd = getGCDIterative(n,d);
    RationalNumber result = {n/gcd,d/gcd};
    return result;
}

RationalNumber rnMultiply(RationalNumber a, RationalNumber b) {
    assert(rnIsValid(a) && rnIsValid(b));
    int n = a.numerator*b.numerator;
    int d = a.denominator*b.denominator;
    int gcd = getGCDIterative(n,d);
    RationalNumber result = {n/gcd,d/gcd};
    return result;
}

RationalNumber rnDivide(RationalNumber a, RationalNumber b) {
    assert(rnIsValid(a) && rnIsValid(b));
    int n = a.numerator*b.denominator;
    int d = a.denominator*b.numerator;
    int gcd = getGCDIterative(n,d);
    RationalNumber result = {n/gcd,d/gcd};
    return result;
}

RationalNumber normalize(RationalNumber a) {
    if (!rnIsValid(a)) return a;
    int gcd = getGCDIterative(a);
    a.numerator /= gcd;
    a.denominator /= gcd;
    return a;
}

int getGCDIterative(int a, int b) {
    int c;
    while ( a != 0 ) {
         c = a; a = b%a;  b = c;
    }
    return b;
}

int getGCDIterative(RationalNumber number) {
    return getGCDIterative(number.denominator, number.numerator);
}

int getGCDRecursive(int a, int b) {
  if(a==0) return b;
  return getGCDRecursive(b%a, a);
}

int getGCDRecursive(RationalNumber number) {
    return getGCDRecursive(number.denominator, number.numerator);
}

int leastCommonMultiple(int a, int b) {
    return a / getGCDIterative(a, b) * b;
}
