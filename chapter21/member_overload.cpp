#include <iostream>

class Cents{
private:
    int m_cents{};

public:
    Cents(int cents):m_cents(cents) {}

    Cents operator+(int value) const;

    int getCents() const {return m_cents;}
};

Cents Cents::operator+(int value) const
{
    return Cents{m_cents + value};
}

int main(void)
{
    const Cents cents1 {6};
    const Cents cents2 {cents1 + 2};
    std::cout << "I have" << cents2.getCents() << " cents.\n";

    return 0;
}
