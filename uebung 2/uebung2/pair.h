#ifndef PAIR_H
#define PAIR_H

#include <iostream>

namespace MyDate {

	template <typename T1, typename T2>
	class Pair {

		T1 m_first;
		T2 m_second;

	public:
		Pair(): m_first(T1()), m_second(T2()) {}
		Pair(T1 first, T2 second): m_first(first), m_second(second) {}
		Pair(const Pair<T1, T2>& other): m_first(other.m_first), m_second(other.m_second) { }
		Pair<T1, T2> operator=(const Pair<T1, T2> &other) { m_first = other.m_first; m_second = other.m_second; return *this; }
		T1 &first() { return m_first; }
		T2 &second() { return m_second; }
		const T1 &first() const { return m_first; }
		const T2 &second() const { return m_second; }
	};
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream &stream, const MyDate::Pair<T1, T2> &pair) {
	return stream << '<' << pair.first()  << ',' << pair.second() << '>';
}

#endif // PAIR_H
