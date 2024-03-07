#include <algorithm>
#include <iostream>
#include <string_view>

template <typename T, int size>
class StaticArray{
private:
    T m_array[size]{};

public:
    T* getArray() {return m_array;}

    const T& operator[](int index) const {return m_array[index];}
    T& operator[](int index){return m_array[index];}
};

template <typename T, int size>
void print(const StaticArray<T, size>& array)
{
    for(int count{0}; count < size; ++count)
        std::cout << array[count] << ' ';
}

template <int size>
void print(const StaticArray<char, size>& array)
{
    for(int count{0}; count < size; ++count)
        std::cout << array[count];
}

int main(void)
{
    StaticArray<char, 14> char14{};

    constexpr std::string_view hello14{"Hello, world!"};
    std::copy_n(hello14.begin(), hello14.size(), char14.getArray());

    print(char14);

    std::cout << ' ';

    StaticArray<char, 12> char12{};

    constexpr std::string_view hello12{"Hello, mom!"};
    std::copy_n(hello12.begin(), hello12.size(), char12.getArray());

    print(char12);

    return 0;
}
