#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main(void)
{
    std::cout << max<int>(1, 2) << '\n';// instantiates and calls function max<int>(int, int)

    return 0;
}
