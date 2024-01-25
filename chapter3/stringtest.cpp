#include <iostream>
#include <string>
using std::string;

int main(void)
{
    string word;
    while(std::cin >> word)
        std::cout << word << std::endl;
    return 0;
}
