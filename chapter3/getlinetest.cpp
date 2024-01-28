#include <iostream>
#include <string>
using std::string;

int main(void)
{
    string line;
    while(std::getline(std::cin, line))
    {
        if(!line.empty())
            std::cout << line << std::endl;
    }
    return 0;
}
