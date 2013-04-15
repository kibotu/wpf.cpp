#ifndef RATIONALNUMBER_H
#define RATIONALNUMBER_H

#endif // RATIONALNUMBER_H

/**
 * @brief Represents a rational number.
 *
 * Numerator
 * ---------
 * Denominator
 */
struct RationalNumber {

    /**
     * @brief Zähler
     */
    int numerator;

    /**
     * @brief Nenner
     */
    int denominator;
};

/**
 * @brief Validates a RationalNumber against division by zero.
 * (Ignores integer overflow)
 *
 * @param n - RationalNumber to be validated.
 * @return true if is valid.
 */
bool rnIsValid(RationalNumber n);
