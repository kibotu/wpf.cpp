#include "rationalnumber.h"
using namespace MyDate;

UnsignedIntValue::UnsignedIntValue(int v) {
    this->v = v;
}

UnsignedIntValue::~UnsignedIntValue() {
    v = 0;
}

int UnsignedIntValue::value() {
    return v;
}
