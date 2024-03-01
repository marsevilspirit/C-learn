#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

bool containNut(std::string_view str)
{
    return str.find("nut") != std::string_view::npos;
}

int main(void)
{
    constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon"};

    auto found{std::find_if(arr.begin(), arr.end(), containNut)};
    
    if(found == arr.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << * found << '\n'; 
    }
}
