#include <algorithm>
#include <array>
#include <iostream>

int main(void)
{
    std::array areas{100, 25, 121, 40, 56};

    int width{};
    int height{};

    std::cout << "Enter width and height: ";
    std::cin >> width >> height;

    auto found{std::find_if(areas.begin(), areas.end(),
                            [=](int knownArea){
                                return width * height == knownArea;
                            })};
    if(found == areas.end())
    {
        std::cout << "I don't know this area :(\n";
    }
    else 
    {
        std::cout << "Area found :)\n";
    }

    return 0;
}
