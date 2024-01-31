#include <iostream>
#include <string>
#include <vector>

int main(void)
{
    std::vector<int> text = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int sought;
    std::cin >> sought;

    auto beg = text.begin(), end = text.end();
    auto mid = text.begin() + (end - beg) / 2;

    while(mid != end && *mid != sought)
    {
        if(sought < * mid)
            end = mid;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }

    std::cout << sought << std::endl;
}
