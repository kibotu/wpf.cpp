#ifndef MYDATE_H
#define MYDATE_H

namespace MyDate {

    class UnsignetIntValue {
    protected:
        const unsigned int mValue;
    public:
        UnsignetIntValue (const int value = 0) : mValue((const unsigned int)value) { }
        unsigned int value() const { return mValue; }
        operator unsigned int() const { return (int) mValue; }
    };

    class Days : public UnsignetIntValue {
    public:
        Days (const int value = 0) : UnsignetIntValue(value) { }
    };

    class Months : public UnsignetIntValue {
    public:
        Months (const int value = 0)  : UnsignetIntValue(value) { }
    };

    class Years : public UnsignetIntValue {
    public:
        Years (const int value = 0) : UnsignetIntValue(value) { }
    };
}

#endif // MYDATE_H
