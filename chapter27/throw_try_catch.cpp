#include <iostream>
#include <string>

int main(void)
{
    try
    {
        throw -1;
    }
    catch(int x)
    {
        std::cerr << "We caught an exception with value: " << x << '\n';
    }
    catch(double)
    {
        std::cerr << "We caught an exception of type double" << '\n';
    }

    std::cout << "Continuing on our merry way\n";

    return 0;
}
