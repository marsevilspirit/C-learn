#include <cassert>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>
#include <condition_variable>
#include <atomic>
#include <future>

#define MAX_THREAD 5

class threadpool{
public:
    threadpool(size_t threads = MAX_THREAD);
    template<class F, class... Args>
        auto enqueue(F &&f, Args &&...args)
        ->std::future<typename std::result_of<F(Args...)>::type>;
    ~threadpool();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

inline threadpool::threadpool(size_t threads):stop(false)
{
    assert(threads >= 1);
    for(size_t i = 0; i < threads; i++)
    {
        workers.emplace_back([this]{
                for(;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock,[this]{return stop || !tasks.empty();});
                        if(stop && tasks.empty())
                            return;

                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    task();
                }
                });
    }
}

template <class F, class... Args>
auto threadpool::enqueue(F &&f, Args &&...args)
    ->std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
}
