#ifndef RATIONALNUMBER_H
#define RATIONALNUMBER_H

/**
 * Represents a rational number.
 *
 * Numerator
 * ---------
 * Denominator
 */
struct RationalNumber {
    /* zähler */
    int numerator;
    /* nenner */
    int denominator;
};

/* Not a Number. */
const RationalNumber RN_NAN = {0,0};

/* Rational 1 */
const RationalNumber RN_ONE = {1,1};

/* Rational 0 */
const RationalNumber RN_ZERO = {0,1};

/**
 * Returns the normalized RationalNumber.
 *
 * @param rn - RationalNumber.
 * @return rn - Normalized Rationalnumber. Or NaN.
 */
RationalNumber rnNormalize(RationalNumber rn);

/**
 * Returns the inverse.
 *
 * @param rn - RationalNumber.
 * @return rn - Inversed RationalNumber. Or NaN.
 */
RationalNumber rnInvert(RationalNumber rn);


/**
 * Validates a RationalNumber against division by zero.
 *
 * @param n - RationalNumber to be validated.
 * @return true if is valid.
 */
bool rnIsValid(RationalNumber rn);

/**
 * Checks the denominator against 0.
 *
 * @param rn - RationalNumber.
 * @return true if the denominator is 0.
 */
bool rnIsNaN(RationalNumber rn);

/**
 * Compares two RationalNumbers in terms of equality. Checks against division by zero and signs.
 *
 * @param a - First RationalNumber.
 * @param b - Second RationalNumber.
 * @return true if both have are equal. False if one of them is NaN.
 */
bool rnEqual(RationalNumber rn1, RationalNumber rn2);

/**
 * Checks if first RationalNumber is smaller than the second. Checks against divison by zero and signs.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return if rn1 < rn2, false if rn1 or rn2 is NaN
 */
bool rnLessThan(RationalNumber rn1, RationalNumber rn2);

/**
 * Adds two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as normalized new RationalNumber.
 */
RationalNumber rnAdd(RationalNumber, RationalNumber);

/**
 * Subtracts two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as normalized new RationalNumber.
 */
RationalNumber rnSubtract(RationalNumber, RationalNumber);

/**
 * Multiplies two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as normalized new RationalNumber.
 */
RationalNumber rnMultiply(RationalNumber, RationalNumber);

/**
 * Divides two RationalNumbers.
 *
 * @param a - First Rational Number.
 * @param b - Second RationalNumber.
 * @return result as normalized new RationalNumber.
 */
RationalNumber rnDivide(RationalNumber divident, RationalNumber divisor);

void rnPrint(RationalNumber n);

#endif // RATIONALNUMBER_H
