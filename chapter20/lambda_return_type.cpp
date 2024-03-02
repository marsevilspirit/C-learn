#include <iostream>

int main(void)
{
    auto divide{[](int x, int y, bool intDivision) -> double {
        if(intDivision)
            return x/y;
        else 
            return static_cast<double>(x)/y;//error, must return same type, -> double can fix
    }};

    std::cout << divide(3, 2, true) << '\n';
    std::cout << divide(3, 2, false) << '\n';

    return 0;
}
