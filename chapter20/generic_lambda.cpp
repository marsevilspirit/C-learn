#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main(void)
{
    constexpr std::array months{
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

    const auto sameLetter{std::adjacent_find(months.begin(), months.end(),
                                        [](const auto& a, const auto& b){
                                            return a[0] == b[0]; 
                                        })};
    
    if(sameLetter != months.end())
    {
        std::cout << * sameLetter << " and " << *std::next(sameLetter)
            << " start with the same letter\n";
    }

    return 0;
}
