#ifndef RATIONALNUMBER_H
#define RATIONALNUMBER_H

#endif // RATIONALNUMBER_H

/**
 * Represents a rational number.
 *
 * Numerator
 * ---------
 * Denominator
 */
struct RationalNumber {

    /**
     * Zähler
     */
    int numerator;

    /**
     * Nenner
     */
    int denominator;
};

/**
 * Validates a RationalNumber against division by zero.
 * (Ignores integer overflow)
 *
 * @param n - RationalNumber to be validated.
 * @return true if is valid.
 */
bool rnIsValid(RationalNumber n);

/**
 * Compares two RationalNumbers in terms of equality. Checks against division by zero and signs.
 *
 * @param a - First RationalNumber.
 * @param b - Second RationalNumber.
 * @return true if both have are equal.
 */
bool rnEqual(RationalNumber a, RationalNumber b);

/**
 * Checks if first RationalNumber is smaller than the second. Checks against divison by zero and signs.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return true if first is smaller than the second.
 */
bool rnLessThan(RationalNumber a, RationalNumber b);

/**
 * Adds two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as new RationalNumber.
 */
RationalNumber rnAdd(RationalNumber a, RationalNumber b);

/**
 * Subtracts two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as new RationalNumber.
 */
RationalNumber rnSubtract(RationalNumber a, RationalNumber b);

/**
 * Multiplies two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as new RationalNumber.
 */
RationalNumber rnMultiply(RationalNumber a, RationalNumber b);

/**
 * Divides two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as new RationalNumber.
 */
RationalNumber rnDivide(RationalNumber a, RationalNumber b);

/**
 * Normalizes RationalNumber.
 *
 * @param a - RationalNumber to be normalized.
 */
RationalNumber normalize(RationalNumber a);

/**
 * Computes greatest common divisor. (Iterative approach)
 *
 * @param a - Rational Number.
 * @return greatest common divisor.
 */
int getGCDIterative(RationalNumber a);

int getGCDIterative(int a, int b);

/**
 * Computes greatest common divisor. (Recursive approach)
 *
 * @param a - Rational Number.
 * @return greatest common divisor.
 */
int getGCDRecursive(RationalNumber number);

int getGCDRecursive(int a, int b);

/**
 * Computes least common multiple.
 *
 * @param a - Denominator.
 * @param b - Numerator.
 * @return
 */
int getLeastCommonMultiple(int a, int b);

int leastCommonMultiple(int a, int b);
