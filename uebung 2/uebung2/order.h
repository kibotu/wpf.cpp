#ifndef LESS_H
#define LESS_H

namespace MyDate {

	template<typename T>
	class Less { public:  bool operator ()(const T &lhs, const T &rhs) { return lhs < rhs; }};

	template<typename T>
	class Greater { public: bool operator ()(const T &lhs, const T &rhs) { return rhs < lhs; }};

	template<typename T>
	class Equal { public: bool operator ()(const T &lhs, const T &rhs) { return lhs == rhs; }};
}

#endif // LESS_H
