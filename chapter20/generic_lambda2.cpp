#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main(void)
{
    constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    const auto fiveLetterMonths{std::count_if(months.begin(), months.end(),
                                        [](std::string_view str){
                                        return str.length() == 5;
                                        })};

    std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";

    return 0;
}
