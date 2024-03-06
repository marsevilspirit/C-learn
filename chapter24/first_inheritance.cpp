#include <iostream>
#include <string>
#include <string_view>

class Person{
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name = "", int age = 0):m_name(name), m_age(age){}
    
    const std::string& getName() const {return m_name;}
    int getAge() const {return m_age;}
};

class BaseballPlayer: public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0):m_battingAverage(battingAverage), m_homeRuns(homeRuns) {}
};

class Employee: public Person
{
public:
    double m_hourlySalary{};
    long m_employeeID{};
    
    Employee(double hourlySalary = 0.0, long EmployeeID = 0):m_hourlySalary(hourlySalary), m_employeeID(EmployeeID){}
    
    void printNameAndSalary() const
    {
        std::cout << m_name << ": " << m_hourlySalary << '\n';
    }
};

int main(void)
{
    Employee frank{20.25, 12345};
    frank.m_name = "Frank";

    frank.printNameAndSalary();

    return 0;
}

