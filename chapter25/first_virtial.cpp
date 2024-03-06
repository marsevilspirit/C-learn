#include <iostream>
#include <string_view>

class Base{
public:
    virtual std::string_view getName() const {return "Base";}
};

class Derived: public Base
{
public:
    virtual std::string_view getName() const {return "Derived";}
};

int main(void)
{
    Derived derived{};
    Base& rBase{derived};
    std::cout << "rBase is a " << rBase.getName() << '\n';

    return 0;
}

