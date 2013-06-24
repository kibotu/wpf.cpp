#ifndef LESS_H
#define LESS_H

namespace MyDate {

	template<typename T>
	class Less { public: const bool operator ()(const T &lhs, const T &rhs) const { return lhs < rhs; }};

	template<typename T>
	class Greater { public: const bool operator ()(const T &lhs, const T &rhs) const { return rhs < lhs; }};

	template<typename T>
	class Equal { public: const bool operator ()(const T &lhs, const T &rhs) const { return lhs == rhs; }};
}

#endif // LESS_H
