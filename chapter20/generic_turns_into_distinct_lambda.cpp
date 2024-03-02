#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main(void)
{
    auto print{
        [](auto value){
            static int callCount{0};
            std::cout << callCount++ << ": " << value << '\n';
        }
    };

    print("hello");
    print("world");

    print(1);
    print(2);

    print("ding dong");

    return 0;
}
