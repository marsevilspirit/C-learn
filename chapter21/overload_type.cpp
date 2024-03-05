#include <iostream>

class Cents{
private:
    int m_cent{};

public:
    Cents(int cents=0):m_cent(cents){}

    operator int() const {return m_cent;}

    int getCents() const {return m_cent;}
    void setCents(int cents) {m_cent = cents;}
};

class Dollars{
private:
    int m_dollars{};

public:
    Dollars(int dollars=0):m_dollars(dollars){}

    operator Cents() const {return Cents(m_dollars * 100);}
};

void printCents(Cents cents)
{
    std::cout << cents;
}

int main(void)
{
    Dollars dollars{9};
    printCents(dollars);

    std::cout << '\n';

    return 0;
}
