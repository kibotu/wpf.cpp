/**
*
*  C++ für Java-Programmierer
*  Testtreiber zur Aufgabe 2, "MyDate"
*  Autor: Hartmut Schirmacher, http://hschirmacher.beuth-hochschule.de
*
*/

#include <iostream>
#include <assert.h>
#include "mydate.h"
#include "mydate_map.h"
#include "order.h"
#include "map.h"

std::string BoolToString(bool v) { return v ? "true" : "false"; }
template<typename T1, typename T2>
void assertEqual(T1 &t1, T2 &t2) { assert(t1 == t2); }
template<typename T1, typename T2>
void assertNotEqual(T1 &t1, T2 &t2) { assert(t1 != t2); }

using namespace std;
using namespace MyDate;

#define SUCCESS cout << "successful" << endl << endl;

int main()
{
	cout << "Starting Unit Tests for Day, Month, Year, Date...\n" << endl;

	/*
	* ##############
	*	DAYS	   #
	* ##############
	*/

	{
		cout << "test: typesafety... " ;

		// Day, Month, Year are just type-safe wrappers for unsigned int
		Days myday;
		assert(myday.value() == 0);

		Months mymonth(12);
		assert(mymonth.value() == 12);

		// have you declared your getters const??? :-)
		const Years CONST_YEAR(2012);
		assert(CONST_YEAR.value() == 2012);

		// test implicit conversion to unsigned int (operator unsigned int())
		assert(0 == myday);
		assert(12 == mymonth);
		assert(2012 == CONST_YEAR);

		SUCCESS
	}

	/*
	* ##############
	*	DATE	   #
	* ##############
	*/

	{
		cout << "test: leap year... " << endl;

		// static member function Date::daysInMonth()
		int days_feb = Date::daysInMonth(2);
		cout << "February normally has " << days_feb << " days." << endl;
		assert(days_feb == 28);

		int days_feb_2400 = Date::daysInMonth(Months(2),Years(2400));
		cout << "In year 2400, February will have " << days_feb_2400 << " days." << endl;
		assert(days_feb_2400 == 29);

		// test months from 0 to 13
		for(int i = 0; i <= 13; ++i) {
			try {
				Date::daysInMonth(Months(i));
			} catch(const std::exception & e) {
				cout << i << ":\t" << e.what() << endl;
			}
		}

		SUCCESS
	}

	{
		cout << "test: daysInMonth... ";

		assert(Date::daysInMonth(Months(1)) == 31);
		assert(Date::daysInMonth(Months(2)) == 28);
		assert(Date::daysInMonth(Months(2),2000) == 29);
		assert(Date::daysInMonth(Months(3)) == 31);
		assert(Date::daysInMonth(Months(4)) == 30);

		assert(Date::daysInMonth(Months(5)) == 31);
		assert(Date::daysInMonth(Months(6)) == 30);
		assert(Date::daysInMonth(Months(7)) == 31);
		assert(Date::daysInMonth(Months(8)) == 31);

		assert(Date::daysInMonth(Months(9)) == 30);
		assert(Date::daysInMonth(Months(10)) == 31);
		assert(Date::daysInMonth(Months(11)) == 30);
		assert(Date::daysInMonth(Months(12)) == 31);

		SUCCESS
	}

	{
		cout << "test: default constructor... " << endl;

		// Date constructor, getters, and stream output
		Date d1;
		cout << "Date1: " << d1 << endl;
		assert(d1.day() == 0);
		assert(d1.month() == 0);
		assert(d1.year() == 0);

		SUCCESS
	}


	{
		cout << "test: compare operators... " << endl;

		// comparison of two dates
		Date d2(1, 1, 2013);
		cout << "Date2: " << d2 << endl;
		Date d3(28, 2, 2013);
		cout << "Date3: " << d3 << endl;
		Date d5(28, 2, 2013);
		cout << "Date5: " << d5 << endl;
		cout << "Date2 == Date3: " << BoolToString(d2==d3) << endl;
		assert(! (d2 == d3));
		cout << "Date3 == Date5: " << BoolToString(d3==d5) << endl;
		assert(d3 == d5);
		cout << "Date2 != Date3: " << BoolToString(d2!=d3) << endl;
		assert(d2 != d3);
		cout << "Date2 < Date3: " << BoolToString(d2<d3) << endl;
		assert(d2<d3);
		cout << "Date3 !< Date2: " << BoolToString(!(d3<d2)) << endl;
		assert(!(d3<d2));

		Date d4(29,2,2012);
		cout << "Date4: " << d4 << endl;
		cout << "Date4 < Date3: " << BoolToString(d4<d3) << endl;
		assert(d4<d3);
		cout << "Date3 !< Date4: " << BoolToString(!(d3<d4)) << endl;
		assert(!(d3<d4));
		cout << "Date4 > Date3: " << BoolToString(d4>d3) << endl;
		assert(d3>d4);

		SUCCESS
	}

	{
		cout << "test: leap year... " << endl;

		// static member function Date::isLeapYear()
		cout << "Is 1999 a leap year: " << Date::isLeapYear(1999) << endl;
		assert(!Date::isLeapYear(1999));
		cout << "Is 2000 a leap year: " << Date::isLeapYear(2000) << endl;
		assert(Date::isLeapYear(2000));
		cout << "Is 2100 a leap year: " << Date::isLeapYear(2100) << endl;
		assert(!Date::isLeapYear(2100));

		SUCCESS
	}

	{
		cout << "test: add day to date... " << endl;

		Date d(0,1,0);
		cout << "Date: " << d << endl;
		cout << "Days(1): " << Days(1) << endl;
		d += Days(1);
		cout << "Date +1d: " << d << endl;

		SUCCESS
	}

	{
		cout << "test: ++ operator... " << endl;

		Days d(1);
		cout << "Day: " << d << endl;
		d++;
		cout << "Day +1d: " << d << endl;
		assert(d == Days(2));

		SUCCESS
	}

	{
		cout << "test: date arythmethic... " << endl;

		Date d3(28, 2, 2013);

		// add one day
		d3 += Days(1);
		cout << "Date3 +1d: " << d3 << endl;
		assert(d3 == Date(1,3,2013));

		// add many days (multiple months)
		int manydays = 31+30+31+30+31+31; // March ... August
		d3 += Days(manydays);
		cout << "Date3 +" << manydays << "d: " << d3 << endl;
		assert(d3 == Date(1,9,2013));

        // add more days (so year is changed)
        int evenmoredays = 30+31+30+31+365; //480;
        cout << "Date3: " << d3 << endl;
        d3 += Days(evenmoredays);
        cout << "Date3 +" << evenmoredays << "d: " << d3 << endl;
        assert(d3.year() == 2015);

		// does += return the correct return type and value?
		Date x(1,1,2012);
		Date y = x+=Days(4); // should work!!!
		cout << x << " + 4d = " << y <<endl;
		assert(x == Date(5,1,2012));

		SUCCESS
	}

	{
		cout << "test: some more date arythmethic... " << endl;

		Date d3(1,1,2015);

		// add months
		Months m3 = d3.month();
		d3 += Months(2);
		cout << "Date3 +2m:" << d3 << endl;
		assert(d3.month() == m3+2);

		// add years
		Years y3 = d3.year();
		d3 += Years(20);
		cout << "Date3 +20y:" << d3 << endl;
		assert(d3.year() == y3+20);

		// verifizieren Sie, dass die folgende Zeile NICHT compiliert,
		// und kommentieren Sie sie dann aus 
		// d3 += 1; // 'operator +=' is ambiguous

		SUCCESS
	}

	{
		cout << "test: addition... " << endl;

		const Date d1(1,1,1);
		const Date d2(2,2,2);
		Days d(1);
		Months m(1);
		Years y(1);
		cout << Date(d1.day() + d2.day(), d1.month() + d2.month(), d1.year() + d2.year()) << endl;
		cout << (d1+d2) << endl;
		cout << (d1+d) << endl;
		cout << (d1+m) << endl;
		cout << (d1+y) << endl;

		cout << (d1+Days(33)) << endl;
		cout << (d1+Months(12)) << endl;
		cout << (d1+Years(2012)) << endl;

		SUCCESS
	}

	{
		cout << "test: non-mutating addition operators... " << endl;

		// non-mutating addition operators
		const Date dd(31,12,2012);
		Date dd2 = dd + Days(1);
		cout << dd << " + 1 day = " << dd2 << endl;
		assert(dd2 == Date(1,1,2013));

		Date dd3 = dd + Months(4);
		cout << dd << " + 4 months = " << dd3 << endl;
		assert(dd3 == Date(31,4,2013)); // 1.5.2013

		Date dd4 = dd + Years(1000);
		cout << dd << " + 1000 years = " << dd4 << endl;
		assert(dd4 == Date(31,12,3012));

		// mixed units
		Date dd5 = dd + Days(2) + Months(3) + Years(5);
		cout << dd << " + 2d + 3m + 5y = " << dd5 << endl;
		assert(dd5 == Date(2,4,2018));

		SUCCESS
	}

	/*
	* ##############
	*	PAIR	   #
	* ##############
	*/

	{
		cout << "test: pair... " << endl;

		Map::Pair p1(Date(1,1,1),"first");
		Map::Pair p2(Date(22,6,2013),"second");
		cout << '<' << p1.first  << ',' << p1.second << '>' << endl;
		cout << '<' << p2.first  << ',' << p2.second << '>' << endl;
		SUCCESS
	}

	/*
	* ##############
	*	ORDER      #
	* ##############
	*/

	{ 
		cout << "test: order... " << endl;

		Less<int> lessInt;
		cout << "2<3 == " << lessInt(2,3) << endl;
		cout << "4<3 == " << lessInt(4,3) << endl;

		Greater<int> greaterInt;
		cout << "2>3 == " << greaterInt(2,3) << endl;
		cout << "4>3 == " << greaterInt(4,3) << endl;

		Equal<int> equalInt;
		cout << "3==3 == " << equalInt(3,3) << endl;
		cout << "2==2 == " << equalInt(2,2) << endl;
		cout << "2<3 == " << equalInt(2,3) << endl;
		cout << "2>3 == " << equalInt(2,3) << endl;

		SUCCESS
	}
	
	/*
	* ##############
	*	DATE MAP   #
	* ##############
	*/

	{ 
		cout << "test: empty map... " << endl;

		Map m;
		assert(m.size() == 0); 
		assert(m.isEmpty());

		Map::Pair p1(Map::key_t(22,1,1986),"birthday");

		m.insert(p1);
		assert(m.size() != 0); 
		assert(!m.isEmpty());

		SUCCESS
	}

	{ 
		cout << "test: [] operator... " << endl;
		Map::key_t d1 = Map::key_t(22,1,1986);
		Map::mapped_t s1 = "birthday";
		Map::Pair p1(d1,s1);
		Map m;

		m.insert(p1);
		assert(m.size() == 1); 
		
		cout << "search by value: " << "<" << m.find(p1)->first << "," << m.find(p1)->second << ">" << endl;
		cout << "search by value: " << "<" << m.find(s1)->first << "," << m.find(s1)->second << ">" << endl;
		cout << "search by key: " << "<" << m.find(d1)->first << "," << m.find(d1)->second << ">" << endl;
		assert(m.size() == 1); 

		Map::mapped_t value = m[d1]; 
		cout << "[" << d1 << "] = " << value << endl;
		assert(m.size() == 1); 

		SUCCESS
	}

	{
		cout << "test: map... " << endl;

		Map::Pair p42(Date(1,5,2013),"Static");
		Map::Pair p1(Date(1,12,2013),"Dynamic");
		Map::Pair p3(Date(6,12,2013),"Enum");
		Map::Pair p7(Date(7,12,2013),"Cast");

		Map m;

		// insert pairs of (key,value)
		m.insert(p42);
		m.insert(p7);

		cout << "test: contains... " << endl;

		assert(m.contains(p42.first));
		assert(m.contains(p7.first));
		assert(!m.contains(p1.first));
		assert(!m.contains(p3.first));

		SUCCESS

		cout << "map 42-7: ";
		assert(m.size() == 2);

		Map::mapped_t value;

		 // test finding elements via operator()
		cout << "find 42 in map: " << (value=m[p42.first]) << endl;
		assert(value == p42.second);
		cout << "find 3 in map: " << (value=m[p3.first]) << endl;
		assert(value == string());

		SUCCESS
	}
	
	{
		cout << "test: map[key] = value ... " << endl;

		Map::key_t date1(1,5,2013);
		Map::key_t date2(6,12,2013);
		Map map1;
		map1[date1] = "Wenig Arbeit, viele Demos";
		map1[date2] = "Nikolaus kommt";
		assert(map1.size() == 2);
		map1[date2] = "Niko kommt doch nicht";
		assert(map1.size() == 2);

		SUCCESS
	}

	{
		cout << "test: operator = and const map ... " << endl;

		Map::Pair p1(Map::key_t(1,1,1), "first date");
		Map::Pair p2(Map::key_t(2,2,2), "second date");
		Map::Pair p3(Map::key_t(3,3,3), "third date");
		Map::mapped_t overwritten = "overwritten";
		Map map1;

		map1[p1.first] = p1.second;
		map1[p2.first] = p2.second;
		map1[p2.first] = overwritten;
		map1[p3.first] = p3.second;

		assert(map1.size() == 3);
		cout << "p1: " << "<" << p1.first << "," << map1[p1.first] << ">" << endl;
		cout << "p2: " << "<" << p2.first<< "," << map1[p2.first] << ">" << endl;
		cout << "p3: " << "<" << p3.first << "," << map1[p3.first] << ">" << endl;

		assertEqual(p1.first, map1.find(p1.second)->first);
		assertEqual(p2.first, map1.find(overwritten)->first);
		assertEqual(p3.first, map1.find(p3.second)->first);
		
		assertEqual(map1[p1.first], p1.second);
		assertEqual(map1[p2.first], overwritten);
		assertEqual(map1[p3.first], p3.second);

		cout << "const map2 = map1" << endl;

		const Map map2 = map1;
		assert(map2.size() == 3);
		cout << "p1: " << "<" << p1.first << "," << map2[p1.first] << ">" << endl;
		cout << "p2: " << "<" << p2.first<< "," << map2[p2.first] << ">" << endl;
		cout << "p3: " << "<" << p3.first << "," << map2[p3.first] << ">" << endl;

		assertEqual(p1.first, map2.find(p1.second)->first);
		assertEqual(p2.first, map2.find(overwritten)->first);
		assertEqual(p3.first, map2.find(p3.second)->first);
		
		assertEqual(map2[p1.first], p1.second);
		assertEqual(map2[p2.first], overwritten);
		assertEqual(map2[p3.first], p3.second);

		// not working, because map2 is const
		// map2[p2.first] = p2.second; 
		// map2.insert(p2);

		SUCCESS
	}
	
	/*
	* #######################
	*	MAP<Date, String>   #
	* #######################
	*/

	using namespace MyMap;

	{ 
		cout << "test: map<Date, std::string> ... " << endl;




		SUCCESS
	}

#if 0 // move this line down while your implementation proceeds...
#endif

	cout << "all tests completed." << endl;

	system("pause");

	return 0;
}