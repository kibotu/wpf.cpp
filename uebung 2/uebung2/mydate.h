#ifndef MYDATE_H
#define MYDATE_H

namespace MyDate {

    class UnsignedIntValue {
        int v;
    public:
        UnsignedIntValue (int v = 0);
        ~UnsignedIntValue();
        int value();
    };

    class Days : public UnsignedIntValue {
    };

    class Months : public UnsignedIntValue {
    };

    class Years : public UnsignedIntValue {
    };


}

#endif // MYDATE_H
