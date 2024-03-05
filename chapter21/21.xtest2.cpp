#include <cstdint>
#include <iostream>

class Average{
private:
    std::int32_t m_avg{};
    std::int8_t  m_count{};

public:
    Average():m_avg(0), m_count(0){}

    Average& operator+=(int num)
    {
        m_avg += num; 
        m_count++;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Average& A);
        
};

std::ostream& operator<<(std::ostream& out, const Average& A)
{
    out << static_cast<float>(A.m_avg)/A.m_count << '\n';
    return out;
}

int main(void)
{
    Average avg{};

    avg += 4;
    std::cout << avg << '\n';

    avg += 8;
    std::cout << avg << '\n';

    avg += 24;
    std::cout << avg << '\n';

    avg += -10;
    std::cout << avg << '\n';

    (avg += 6) += 10;
    std::cout << avg << '\n';

    Average copy{avg};
    std::cout << copy << '\n';

    return 0;
}
