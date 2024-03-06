#include <iostream>

class Base{
public:
    friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        return b.print(out);
    }

    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Base";
        return out;
    }
};

struct Employee{
    std::string name{};
    int id{};

    friend std::ostream& operator<<(std::ostream& out, const Employee& e)
    {
        out << "Employee(" << e.name << ", " << e.id << ")";
        return out;
    }
};

class Derived: public Base 
{
private:
    Employee m_e{};

public:
    Derived(const Employee& e):m_e(e){}

    std::ostream& print(std::ostream& out) const override
    {
        out << "Derived: ";
        out << m_e;

        return out;
    }
};

int main(void)
{
    Base b{};
    std::cout << b << '\n';

    Derived d{Employee{"Jim", 4}};
    std::cout << d << '\n';

    Base& bref{d};
    std::cout << bref << '\n';

    return 0;
}

