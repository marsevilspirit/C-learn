#include <string>
#include <string_view>
#include <iostream>

class MyString{
private:
    std::string m_str;

public:
    MyString(std::string_view str):m_str(str){}

    friend std::ostream& operator<<(std::ostream& out, const MyString& f)
    {
        out << f.m_str;
        return out;
    }

    MyString& operator()(int index, size_t len)
    {
        std::string str = m_str.substr(index, len);
        m_str = str;

        return *this;
    }
};


int main(void)
{
    MyString s {"Hello, world!"};
    std::cout << s(7, 5) << '\n';
}
