#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct StudentGrade{
    std::string name{};
    char grade{};
};

class GradeMap{
private:
    std::vector<StudentGrade> m_map{};

public:
    char& operator[](std::string_view str)
    {
        auto it = std::find_if(m_map.begin(), m_map.end(), 
                [str](const auto& student){
                   return (student.name == str); 
                });  

        if(it != m_map.end())
            return it->grade;
        
        m_map.emplace_back(std::string{str});

        return m_map.back().grade;
    }
};

int main(void)
{
    GradeMap grades{};

    grades["Joe"] = 'A';
    grades["Frank"] = 'B';

    std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
    std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
}
