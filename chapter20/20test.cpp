#include <iostream>
#include <string_view>
#include <array>
#include <algorithm>

struct student{
    std::string_view name;
    int score;
};

int main(void)
{
    constexpr std::array<student, 8> arr{
       {{"Albert", 3},
        {"Ben", 5},
        {"Christine", 2},
        {"Dan", 8},
        {"Enchilada", 4},
        {"Francis", 1},
        {"Greg", 3},
        {"Hagrid", 5}}
    };

    const auto best{
        std::max_element(arr.begin(), arr.end(), [](const auto& a, const auto& b){
                    return a.score < b.score;
                })
    };

    std::cout << best->name << " is the best student\n";
    
    return 0;
}
