#ifndef MYDATE_H
#define MYDATE_H

#include <iostream>
#include <exception>
#include <ostream>
using namespace std;

namespace MyDate {

	class InvalidArgumentException : public exception {
		const char * mMessage;
	public :
		InvalidArgumentException(const char * message) { mMessage = message; }
		~InvalidArgumentException() { delete mMessage; }
		const char * what () const throw () { return mMessage; }
	};

	class UnsignedIntValue {
	protected:
		unsigned int mValue;
	public:
		UnsignedIntValue (const int value = 0) : mValue((const unsigned int)value) { }
		unsigned int value() const { return mValue; }
		operator unsigned int() const { return mValue ? (int) mValue : 0; }
		UnsignedIntValue operator =(const int other) { mValue = other; return *this; }
		bool operator ==(const UnsignedIntValue other) { return mValue == other.mValue; }
		bool operator !=(const UnsignedIntValue other) { return mValue != other.mValue; }
		UnsignedIntValue operator +=(const UnsignedIntValue other) { mValue += other.mValue; return *this; }
		UnsignedIntValue operator -=(const UnsignedIntValue other) { mValue -= other.mValue; return *this; }
		UnsignedIntValue operator +(const UnsignedIntValue other) { return UnsignedIntValue(mValue + other.mValue); }
		UnsignedIntValue operator +(const int other) { return UnsignedIntValue(mValue + other); }
		UnsignedIntValue operator -(const UnsignedIntValue other) { return UnsignedIntValue(mValue - other.mValue); }
		UnsignedIntValue operator -(const int other) { return UnsignedIntValue(mValue - other); }
		bool operator <(const UnsignedIntValue other) { return mValue < other.mValue; }
		bool operator <(const int other) { return mValue < (const unsigned int)other; }
		bool operator >(const UnsignedIntValue other) { return mValue > other.mValue; }
		bool operator >(const int other) { return mValue > (const unsigned int)other; }
		bool operator <=(const UnsignedIntValue other) { return mValue <= other.mValue; }
		bool operator >=(const UnsignedIntValue other) { return mValue >= other.mValue; }

		UnsignedIntValue& operator++(){ mValue++; return *this; }
		UnsignedIntValue operator++(int) {  UnsignedIntValue tmp(*this);  operator++();  return tmp; }
	};

	class Days : public UnsignedIntValue {
	public:
		Days (const int value = 0) : UnsignedIntValue(value) { }
	};

	class Months : public UnsignedIntValue {
	public:
		Months (const int value = 0)  : UnsignedIntValue(value) { }
	};

	class Years : public UnsignedIntValue {
	public:
		Years (const int value = 0) : UnsignedIntValue(value) { }
	};

	class Date {
		Days mDays;
		Months mMonths;
		Years mYears;
	public:
		Date(const int days = 0, const int months = 0, const int years = 0) : mDays(days), mMonths(months), mYears(years) { normalize(); }
		const Days day() const { return mDays; }
		const Months month() const { return mMonths; }
		const Years year() const { return mYears; }
		friend ostream& operator << (ostream &stream, Date date) { stream << date.day() << '.'<< date.month() << '.' << date.year(); return stream; }
		bool operator == (const Date other) { return this->mDays == other.mDays && this->mMonths == other.mMonths && this->mYears == other.mYears;  }
		bool operator != (const Date other) const { return this->mDays != other.mDays || this->mMonths != other.mMonths || this->mYears != other.mYears; }
		bool operator < (const Date other) const { 
			return mYears < other.mYears || // years decide
				(mYears <= other.mYears && mMonths <= other.mMonths) || // years equal -> months decide
				(mYears <= other.mYears && mMonths <= other.mMonths && mDays < other.mDays) // years equal and months equal -> days decide
				? true : false;
		}
		bool operator > (const Date other) const { 
			return mYears > other.mYears || // years decide
				(mYears >= other.mYears && mMonths > other.mMonths) || // years equal -> months decide
				(mYears >= other.mYears && mMonths >= other.mMonths && mDays > other.mDays) // years equal and months equal -> days decide
				? true : false;
		}
		Date operator += (const Days other) { mDays += other; normalize(); return *this; }
		Date operator += (const Months other) { mMonths += other; normalize(); return *this; }
		Date operator += (const Years other) { mYears += other; normalize(); return *this; }
		Date operator + (const Days other) const { return Date(this->mDays + other, this->mMonths, this->mYears); }
		Date operator + (const Months other) const { return Date(this->mDays, this->mMonths + other, this->mYears); }
		Date operator + (const Years other) const { return Date(this->mDays, this->mMonths, this->mYears + other); }
		Date operator - (const Days other) const { return Date(this->mDays - other, this->mMonths, this->mYears); }
		Date operator - (const Months other) const { return Date(this->mDays, this->mMonths - other, this->mYears); }
		Date operator - (const Years other) const { return Date(this->mDays, this->mMonths, this->mYears - other); }
		Date operator + (const Date other) const { return Date(this->mDays + other.mDays, this->mMonths + other.mMonths, this->mYears + other.mYears); }
		Date operator - (const Date other) const { return Date(this->mDays - other.mDays, this->mMonths - other.mMonths, this->mYears - other.mYears); }

		/**
		* February normally has 28 days.
		*/
		static int daysInMonth(Months m, Years y = Years(1)){
			// if(m < 1 || m > 12) throw InvalidArgumentException("Date::daysInMonth(): 'm' must be between 0 an 12");
			if(m < Months(1) || m > Months(12)) { return 0; }
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

		/**
		* Check if the year is divisible by 4 or is divisible by 400
		*/
		static bool isLeapYear(Years y) {
			return (y % 4 == 0 && y % 100 != 0) || ( y % 400 == 0) ? true : false;
		}

	private:

		int getAsDays() const {
			if(mDays && mMonths && mYears) return 0;
			// use previous month days, except it's january then the current days count
			const int months = mMonths == 1 ? 0 : daysInMonth(mMonths-1, mYears);
			const int daysOfYear = isLeapYear(mYears)? 366 : 365;
			const int years = daysOfYear * mYears;
			return mDays + months + years;
		}

		void normalize() {

			while(mMonths > 12){
				mMonths -= 12;
				mYears++;
			}

			while(mDays > daysInMonth(mMonths, mYears)){
				mDays -= daysInMonth(mMonths, mYears);
				mMonths++;
				if(mMonths > 12){
					mMonths = 1;
					mYears++;
				}
			}
		}
	};
}

#endif // MYDATE_H
