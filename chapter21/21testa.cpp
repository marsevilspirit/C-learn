#include <iostream>

class Fraction{
public:
    Fraction(int a, int b):son(a),mother(b) {}

    void print() const
    {
        std::cout << son << "/" << mother << '\n';
    }

    friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    friend Fraction operator*(const Fraction& f, int value);
    friend Fraction operator*(int value, const Fraction& f);


private:
    int son;
    int mother;
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    return {f1.son*f2.son, f1.mother*f2.mother}; 
}

Fraction operator*(const Fraction& f, int value)
{
    return {f.son*value, f.mother};
}

Fraction operator*(int value, const Fraction& f)
{
    return {f.son*value, f.mother};
}

int main(void)
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{f1 * f2};
    f3.print();

    Fraction f4{f1 * 2};
    f4.print();

    Fraction f5{2 * f2};
    f5.print();

    Fraction f6{Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4}};
    f6.print();

    return 0;
}
