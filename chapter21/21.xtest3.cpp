#include <iostream>
#include <cassert>

class IntArray{
private:
    int index{0};
    int* m_arr{nullptr};

public:
    explicit IntArray(int num):index(num)
    {
        m_arr = new int[index];
    }

    IntArray(const IntArray& arr)
    {
        index = arr.index;
        m_arr = new int[index];

        for(int i = 0; i < index; i++)
        {
            m_arr[i] = arr.m_arr[i];
        }
    }

    ~IntArray()
    {
        delete[] m_arr;
    }

    auto& operator[](int num)
    {
        assert(num < index);
        assert(num >= 0);

        return m_arr[num];
    }

    IntArray& operator=(const IntArray& arr)
    {
        if (this == &arr)
            return *this; 

        delete[] m_arr;

        index = arr.index;
        m_arr = new int[index];

        for(int count{0}; count < arr.index; ++count)
            m_arr[count] = arr.m_arr[count];

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const IntArray& arr)
    {
        for(int i = 0; i < arr.index; i++)
        {
            out << arr.m_arr[i] << ' ';
        }
        return out;
    }
};

IntArray fillArray()
{
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}

int main(void)
{
    IntArray a{fillArray()};

    std::cout << a << '\n';

    auto& ref{a};
    a = ref;

    IntArray b(1);
    b = a;

    a[4] = 7;
    std::cout << b << '\n';

    return 0;
}
