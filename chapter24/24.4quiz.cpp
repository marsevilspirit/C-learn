#include <iostream>
#include <string>
#include <string_view>

class Fruit{
private:
    std::string m_name{};
    std::string m_color{};

public:
    Fruit(std::string_view name="", std::string_view color=""):m_name(name), m_color(color){}
   
    const std::string& getName() const {return m_name;}
    const std::string& getColor() const {return m_color;}
};

class Apple: public Fruit
{
private:
    double m_fibre{};

public:
    Apple(std::string_view name, std::string_view color, double fibre=0.0):Fruit(name, color), m_fibre(fibre){}

    friend std::ostream& operator<<(std::ostream& out, const Apple& apple)
    {
        out << "Apple(" << apple.getName() << ", " << apple.getColor() << ", " << apple.m_fibre << ")";
        return out;
    }
};

class Banana: public Fruit
{
public:
    Banana(std::string_view name, std::string_view color):Fruit(name, color){}

    friend std::ostream& operator<<(std::ostream& out, const Banana& banana)
    {
        out << "Banana(" << banana.getName() << ", " << banana.getColor() << ")";
        return out;
    }
};

int main(void)
{
    const Apple a{"Red delicious", "red", 4.2};
    std::cout << a << '\n';

    const Banana b{"Cavendish", "yellow"};
    std::cout << b << '\n';

    return 0;
}
