#include <iostream>

class IntList{
private:
    int m_list[10]{0,1,2,3,4,5,6,7,8,9};

    const int& getIdnex(int index) const
    {
        return m_list[index];
    }

public:
    int& operator[](int index)
    {
        return const_cast<int&>(getIdnex(index));
    }

    const int& operator[](int index) const
    {
        return getIdnex(index);
    }
};

int main(void)
{
    IntList list{};
    list[2] = 3;
    std::cout << list[2] << '\n';

    const IntList clist{};
    std::cout << clist[2] << '\n';

    return 0;
}
