#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int cargo = 0;

bool shipment_available()
{
    return cargo != 0;
}

void consume(int n)
{
    for(int i=0; i<n; ++i)
    {
        std::unique_lock<std::mutex> lck(mtx);

        cv.wait(lck, shipment_available);
        std::cout << cargo << '\n';
        cargo = 0;
    }
}

