#include <limits.h>
#include "rationalnumber.h"

#ifndef RATIONALNUMBERCOLLECTION_H
#define RATIONALNUMBERCOLLECTION_H

/**
 * limit to head off segmentation faults during collection operations
 */
const unsigned int RNC_MAX_SIZE = UINT_MAX >> (sizeof(RationalNumber) - 1);

/**
 * access only through rncFunctions
 */
struct RationalNumberCollection;

/**
 * Creates an RNC with the given capacity and returns a pointer to it.
 *
 * @param capacity - Initial amount of the collection.
 * @return collection - Pointer to the collection.
 */
RationalNumberCollection* rncCreate(const unsigned int capacity = 10u);

/**
 * Frees the memory.
 *
 * @param rnc - Collection to be freed.
 */
void rncDelete(RationalNumberCollection** rnc);

/**
 * Appends a copy of rn to the end of rnc, also increasing its size and when required its capacity.
 *
 * @param rnc - RationalNumberCollection which the RationalNumber gets appended to.
 * @param rn - RationalNumber which gets appended.
 */
void rncAdd(RationalNumberCollection* rnc, const RationalNumber* rn);

/**
 * Removes the array elements between startIndex and endIndex.
 *
 * @param rnc - RationalNumberCollection.
 * @param startIndex - inclusive start index
 * @param endIndex - exclusive end index
 */
void rncRemove(RationalNumberCollection* rnc, const unsigned int startIndex, const unsigned int endIndex);

/**
 * Returns the sum of all elements within the collection.
 *
 * @param rnc - RationalNumberCollection.
 * @return sum of RationalNumber within the collection.
 */
RationalNumber rncSum(RationalNumberCollection* rnc);

/**
 * Returns the average of all elements within the collection.
 *
 * @param rnc - RationalNumberCollection
 * @return average RationalNumber
 */
RationalNumber rncAverage(RationalNumberCollection* rnc);

/**
 * Returns the amount of occurancies of a certain RationalNumber.
 *
 * @param rnc - RationalNumberCollection.
 * @param rn - RationalNumber.
 * @return how often a RationalNumber occurs in a RationalNumberCollection.
 */
unsigned int rncCount(const RationalNumberCollection* rnc, const RationalNumber* rn);

/**
 * Returns how many RationalNumber are in the RationalNumberCollection.
 *
 * @param rnc - RationalNumberCollection.
 * @return size of RationalNumberCollection.
 */
unsigned int rncTotalCount(const RationalNumberCollection* rnc);

/**
 * Returns the amount of unique RationalNumber are within the RationalNumberCollection.
 *
 * @param rnc - RationalNumberCollection.
 * @return unqiue RationalNumber occurancies.
 */
unsigned int rncTotalUniqueCount(const RationalNumberCollection* rnc);

/**
 * Returns the size of the rnc.
 *
 * @param rnc - RationalNumberCollection.
 * @return size of the collection.
 */
unsigned int rncSize(const RationalNumberCollection* rnc);

/**
 * Adjusts the capacity of rnc such that the new capacity is at least newCapacity.
 * @param rnc - RationalNumberCollection.
 * @param newCapacity - Targeted capacity.
 */
void rncResize(RationalNumberCollection* rnc, const unsigned int newCapacity);

/**
 * Currently allocated memory.
 *
 * @param rnc - RationalNumberCollection.
 * @return capacity
 */
unsigned int rncCapacity(const RationalNumberCollection* rnc);

/**
 * Places a copy of rn into rnc at index, increasing size and/or capacity if required.
 *
 * @param rnc - RationalNumberCollection.
 * @param index - index at which the RationalNumber will be placed.
 * @param rn - RationalNumber.
 */
void rncSet(RationalNumberCollection* rnc, const unsigned int index, const RationalNumber* rn);

/**
 * Returns a pointer to the rn at the given index.
 *
 * @param rnc - RationalNumberCollection.
 * @param index - Index of the RationalNumber.
 * @return RationalNumber at index position.
 */
RationalNumber* rncGet(RationalNumberCollection* rnc, const unsigned int index);

/**
 * Prints the RationalNumberCollection on the console.
 *
 * @param rnc - RationalNumberCollection.
 */
void rncPrint(RationalNumberCollection* rnc);

#endif // RATIONALNUMBERCOLLECTION_H
