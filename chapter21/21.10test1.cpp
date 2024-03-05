#include <string>
#include <string_view>
#include <iostream>
#include <cassert>

class MyString{
private:
    std::string m_str{};

public:
    MyString(std::string_view str = {}):m_str(str){}

    friend std::ostream& operator<<(std::ostream& out, const MyString& f)
    {
        out << f.m_str;
        return out;
    }

    MyString operator()(int index, size_t len)
    {
        assert(index >= 0);
        assert(index + len <= static_cast<int>(m_string.length()) && "MyString::operator(int, int):
                substring is out of range");
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
