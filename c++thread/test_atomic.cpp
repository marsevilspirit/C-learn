#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

std::atomic<bool> stop(false);

void worker(){
    while(!stop.load()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Worker thread stopped." << '\n';
    }
}

int main(void)
{
    std::thread t(worker);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    stop.store(true);

    t.join();

    return 0;
}
