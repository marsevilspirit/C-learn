#include <string>
#include <string_view>

class Person{
private: 
    std::string m_name{};
    int m_age{};

public:
    Person(std::string_view name, int age):m_name(name), m_age(age){}
    
    const std::string& getName() const {return m_name;}
    int getAge() const {return m_age;}
};

class Employee{
private:
    std::string m_employer{};
    double m_wage{};

public:
    Employee(std::string_view employer, double wage):m_employer(employer),m_wage(wage){}

    const std::string& getEmployer() const {return m_employer;}
    double getWage() const {return m_wage;}
};

class Teather:public Person, public Employee
{
private:
    int m_teachesGrade{};

public:
    Teather(std::string_view name, int age, std::string_view employer, double wage, int teachesGrade):Person(name, age), Employee(employer, wage), m_teachesGrade(teachesGrade){}
};

int main(void)
{
    Teather t{"Mary", 45, "Boo", 14.3, 8};

    return 0;
}


