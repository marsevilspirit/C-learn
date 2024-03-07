#include <thread>
#include <mutex>
#include <iostream>

int g_i = 0;
std::mutex g_i_mutex;

void safe_inrement()
{
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;
    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
    std::cout << "main id: " << std::this_thread::get_id() << '\n';
    std::cout << "main: " << g_i << '\n';
}

int main(void)
{
    std::thread t1(safe_inrement);
    std::thread t2(safe_inrement);

    t1.join();
    t2.join();

    std::cout << "main: " << g_i << '\n';
}
