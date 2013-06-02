#ifndef MYDATE_H
#define MYDATE_H

namespace MyDate {

    class InvalidArgumentException : public std::exception {
        const char * mMessage;
    public :
      InvalidArgumentException(const char * message) { mMessage = message; }
      const char * what () const throw () { return mMessage; }
    };

    class UnsignetIntValue {
    protected:
        unsigned int mValue;
    public:
        UnsignetIntValue (const int value = 0) : mValue((const unsigned int)value) { }
        unsigned int value() const { return mValue; }
        operator unsigned int() const { return (int) mValue; }
        bool operator ==(UnsignetIntValue other) { return mValue == other.mValue; }
        bool operator !=(UnsignetIntValue other) { return mValue != other.mValue; }
        UnsignetIntValue operator +=(UnsignetIntValue other) { mValue += other.mValue; return *this; }
        UnsignetIntValue operator -=(UnsignetIntValue other) { mValue -= other.mValue; return *this; }
        UnsignetIntValue operator =(int other) { mValue = other; return *this; }
        UnsignetIntValue operator +(UnsignetIntValue other) { return UnsignetIntValue(mValue + other.mValue); }
        UnsignetIntValue operator -(UnsignetIntValue other) { return UnsignetIntValue(mValue - other.mValue); }
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

    class Date {
        Days mDays;
        Months mMonths;
        Years mYears;
    public:
        Date(const int days = 0, const int months = 0, const int years = 0) : mDays(days), mMonths(months), mYears(years) {
           /* int validDays = daysInMonth(months);
            if(days < 1 || days > validDays) throw InvalidArgumentException("Date: 'days' must be between 0 an " + validDays);
            if(months < 1 || months > 12) throw InvalidArgumentException("Date: 'months' must be between 0 an 12");
            if(years < 1 || years > 12) throw InvalidArgumentException("Date: 'years' must be over 0");*/
        }

        /**
         * Check if the year is divisible by 4 or is divisible by 400
         */
        static bool isLeapYear(Years y) {
            return (y % 4 == 0 && y % 100 != 0) || ( y % 400 == 0) ? true : false;
        }

        /**
         * February normally has 28 days.
         */
        static int daysInMonth(Months m, Years y = Years(1)){
            if(m < 1 || m > 12) throw InvalidArgumentException("Date::daysInMonth(): 'm' must be between 0 an 12");
            int result = 31;
            switch(m) {
            case 2: result = isLeapYear(y) ? 29 : 28; break;
            case 4:
            case 6:
            case 9:
            case 11: result = 30;
            }
            return result;
        }

        const Days day() const { return mDays; }
        const Months month() const { return mMonths; }
        const Years year() const { return mYears; }
        friend std::ostream& operator<<(std::ostream &stream, Date date)
        {
            stream << date.day() << '.'<< date.month() << '.' << date.year();
            return stream;
        }
        int getAsDays() const {
            // use previous month days, except it's january then the current days count
            std::cout << "getAsDays mDays " << mDays << std::endl;
            return 360 * mYears + (mMonths == 1 ? 0 : daysInMonth(mMonths-1, mYears)) + mDays;
        }
        bool operator ==(const Date other) {
            return this->mDays == other.mDays && this->mMonths == other.mMonths && this->mYears == other.mYears;
        }
        bool operator !=(const Date other) const {
            return this->mDays != other.mDays || this->mMonths != other.mMonths || this->mYears != other.mYears;
        }
        bool operator <(const Date other) const {
            return this->getAsDays() < other.getAsDays();
        }
        bool operator >(const Date other) const {
            return this->getAsDays() > other.getAsDays();
        }
        Date operator+=(const Days other) {
            mDays += other;
            normalize();
            return *this;
        }
        void normalize() {
            int totalDays = getAsDays();
            std::cout << "bla " << totalDays << std::endl;
            std::cout << "mMonths " << mMonths << std::endl;
            std::cout << "mDays " << mDays << std::endl;
            mYears = totalDays % 360;
            std::cout << mYears << std::endl;
            totalDays = totalDays - mYears * 360;
            mMonths = totalDays % 12;
            mDays = totalDays - mMonths * 12;
            std::cout << totalDays;
            assert(totalDays == 0);
        }
    };
}

#endif // MYDATE_H
