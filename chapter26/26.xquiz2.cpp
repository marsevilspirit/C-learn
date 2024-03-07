#include <iostream>

template<typename T, typename U>
class Pair{
private:
    T m_x{};
    U m_y{};

public:
    Pair(T x, U y):m_x(x), m_y(y){}

    const T& first() const {return m_x;}
    const U& second() const {return m_y;}
};

int main()
{
	Pair<int, double> p1 { 5, 6.7 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2 { 2.3, 4 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

	return 0;
}
