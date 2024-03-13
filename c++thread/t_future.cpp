#include <iostream>
#include <future>

int square(int x){
    return x * x;
}

int main(void)
{
    std::future<int> result = std::async(square, 5);

    int squared_value = result.get();

    std::cout << "Square of 5 is: " << squared_value << '\n';
}
