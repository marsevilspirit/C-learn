#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <filesystem>
#include <condition_variable>
#include <functional>
#include <unistd.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

struct SearchConfig {
    std::string root_path;              // 要搜索的根目录
    std::string file_type;              // 要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;                // 最大并发数 
    int max_depth;                      // 最大搜索深度
    bool skip_hidden;                   // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths;// 要跳过的目录或文件的路径
};

class ThreadPool 
{
public:
    explicit ThreadPool(size_t num_threads) : stop(false) 
    {
        for (size_t i = 0; i < num_threads; ++i)
            workers.emplace_back([this] 
                    {
                for (;;) 
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }

    template<class F, class... Args>
    void enqueue(F &&f, Args &&... args) 
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        }
        condition.notify_one();
    }

    ~ThreadPool() 
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers)
            worker.join();
    }

private:
    std::vector<std::thread> workers;//存储了线程池中的所有工作线程。每个线程都会从任务队列中取出任务并执行
    std::queue<std::function<void()>> tasks;//任务队列，存储了待执行的任务。任务以 std::function<void()> 的形式存储，即可调用对象的容器

    std::mutex queue_mutex;//互斥量，用于保护对任务队列的访问
    std::condition_variable condition;//条件变量
    bool stop;
};

class FileSearch {
public:
    FileSearch(const SearchConfig &config) : config_(config), pool(config_.max_concurrency){}

    void searchFiles() 
    {
        pool.enqueue(&FileSearch::searchTask, this, std::filesystem::path(config_.root_path), 0);
    }

private:
    SearchConfig config_;
    ThreadPool pool;

    void searchTask(const std::filesystem::path &current_path, int depth)
    {
        if (depth > config_.max_depth)
            return;

        try {
            for (const auto &entry : std::filesystem::directory_iterator(current_path)) 
            {
                if (std::filesystem::is_directory(entry)) 
                {
                    if (shouldSkip(entry.path())) 
                    {
                        continue;
                    }
                    pool.enqueue(&FileSearch::searchTask, this, entry.path(), depth + 1);
                } else if (std::filesystem::is_regular_file(entry)) 
                {
                    if (entry.path().extension() == config_.file_type) 
                    {
                        std::cout << GREEN <<"Found file: " << RESET <<entry.path() << '\n';
                    }
                }
            }
        } catch (const std::exception &ex) 
        {
            std::cerr << RED <<"Error accessing: " << RESET << current_path << " - " << ex.what() << '\n';
        }
    }

    bool shouldSkip(const std::filesystem::path &path) const 
    {
        if (config_.skip_hidden && path.filename().string().front() == '.') 
        {
            return true;
        }
        for (const auto &skip_path : config_.skip_paths) 
        {
            if (path == std::filesystem::path(skip_path)) 
            {
                return true;
            }
        }
        return false;
    }
};

int main(void) 
{
    SearchConfig config;

    std::cout << "欢迎使用方泽亚历尽千辛万苦编写的多线程文件搜索程序" << '\n';
    std::cout << "输入你想搜索的根目录: ";
    std::cin >> config.root_path;           // 设置要搜索的根目录
    std::cout << "输入你想搜索的文件类型: ";
    std::cin >> config.file_type;            // 设置要搜索的文件类型
    std::cout << "输入最大并发数: ";
    std::cin >> config.max_concurrency;           // 设置最大并发数
    std::cout << "输入最大搜索深度: ";
    std::cin >> config.max_depth;                 // 设置最大搜索深度

    std::cout << "是否要跳过隐藏文件(y/n): ";

    std::string temp{};
    std::cin >> temp; 
    if(temp == "y")
    {
        config.skip_hidden = true;
    }
    else if(temp == "n")
    {
        config.skip_hidden = false;
    }
    else 
    {
        std::cout << "既然你乱输的话，我就当你要跳过了哦";
        config.skip_hidden = true;
    }

    if(config.root_path == "/")
    {
        std::cout << "检测到你想搜索的根目录是/, 强烈建议你跳过/proc目录，会极大加快搜索速度\n";
    }

    std::cout << "是否有要跳过的路径(y/n): ";

    std::cin >> temp;

    while(temp == "y")
    {
        std::cout << "输入想要跳过的路径: ";
        std::cin >> temp;
        config.skip_paths.emplace_back(temp);
        std::cout << "是否还有要跳过的路径(y/n): ";
    }

    if(temp != "n")
    {
        std::cout << "\n既然你乱输的话，我就当你要没有了哦\n";
    }

    std::cout << "ok，一切就绪，准备好了吗，要开始了!!!\n";

    for(int i = 3; i != 0; i--)
    {
        std::cout << i << ' ' << std::endl;
        usleep(1000000);
    }
    std::cout << "go!\n";
    usleep(1000000);

    FileSearch fileSearch(config);
    fileSearch.searchFiles();

    return 0;
}

