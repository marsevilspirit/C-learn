#include <functional>
#include <iostream>

void repeat1(int repetitions, const std::function<void(int)>& fn)
{
    for(int i{0}; i < repetitions; i++)
        fn(i);
}

template <typename T>
void repeat2(int repetitions, const T& fn)
{
    for(int i{0}; i < repetitions; i++)
        fn(1);
}

void repeat3(int repetitions, const auto& fn)//c++20
{
    for(int i{0}; i < repetitions; i++)
        fn(i);
}

int main(void)
{
    auto lambda = [](int i){
        std::cout << i << '\n';
    };

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);

    return 0;
}
