#include <iostream>
#include <thread>

void thread_1()
{
    while(1)
    {
        std::cout << "thread:1111" << '\n';
    }
}

void thread_2(int x)
{
    while(1)
    {
        std::cout << "thread:2222" << '\n';
    }
}

int main(void)
{
    std::thread first(thread_1);
    std::thread second(thread_2, 100);

    first.join();
    second.join();
    
    while (1)
    {
        std::cout << "main thread\n"; 
    }

    return 0;
}
