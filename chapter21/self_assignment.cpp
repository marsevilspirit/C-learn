#include <algorithm>
#include <iostream>
#include <ostream>

class MyString{
private:
    char* m_data{};
    int m_length{};

public:
    MyString(const char* data = nullptr, int length = 0):m_length{std::max(length, 0)}
    {
        if(length)
        {
            m_data = new char[static_cast<std::size_t>(length)];
            std::copy_n(data, length, m_data);
        }
    }

    ~MyString()
    {
        delete[] m_data;
    }

    MyString& operator=(const MyString& str);
    friend std::ostream& operator<<(std::ostream& out, const MyString& s);
};

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    out << s.m_data;
    return out;
}

MyString& MyString::operator=(const MyString& str)
{
    if(this == &str)
        return *this;

    if(m_data) delete[] m_data;

    m_length = str.m_length;
    m_data = nullptr;

    if(m_length)
        m_data = new char[static_cast<std::size_t>(str.m_length)];
    
    std::copy_n(str.m_data, m_length, m_data);

    return *this;
}

int main(void)
{
    MyString alex {"Alex", 5};
    alex = alex;
    std::cout << alex;

    return 0;
}
