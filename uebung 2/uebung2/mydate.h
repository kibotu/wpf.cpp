#ifndef MYDATE_H
#define MYDATE_H

namespace MyDate {

    class Days {
        const unsigned int mValue;
    public:
        Days (const int value = 0) : mValue((const unsigned int)value) { }
        unsigned int value() const { return mValue; }
        operator unsigned int() { return (int) mValue; }
    };

    class Months {
        const unsigned int mValue;
    public:
        Months  (const int value = 0) : mValue((const unsigned int)value) { }
        unsigned int value() const { return mValue; }
        operator unsigned int() const { return (int) mValue; }
    };

    class Years {
        const unsigned int mValue;
    public:
        Years (const int value = 0) : mValue((const unsigned int)value) { }
        unsigned int value() const { return mValue; }
        operator unsigned int() const { return (int) mValue; }
    };
}

#endif // MYDATE_H
