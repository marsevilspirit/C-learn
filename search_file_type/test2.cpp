#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <filesystem>
#include <condition_variable>
#include <functional>

struct SearchConfig {
    std::string root_path;              // 要搜索的根目录
    std::string file_type;              // 要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;                // 最大并发数 
    int max_depth;                      // 最大搜索深度
    bool skip_hidden;                   // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths;// 要跳过的目录或文件的路径
};

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads) : stop(false) {
        for (size_t i = 0; i < num_threads; ++i)
            workers.emplace_back([this] {
                for (;;) {
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
    void enqueue(F &&f, Args &&... args) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        }
        condition.notify_one();
    }

    ~ThreadPool() {
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
    FileSearch(const SearchConfig &config) : config_(config) {}

    void searchFiles() {
        ThreadPool pool(config_.max_concurrency);
        pool.enqueue(&FileSearch::searchTask, this, std::filesystem::path(config_.root_path), 0);
    }

private:
    SearchConfig config_;

    void searchTask(const std::filesystem::path &current_path, int depth) {
        if (depth > config_.max_depth)
            return;

        try {
            for (const auto &entry : std::filesystem::directory_iterator(current_path)) {
                if (std::filesystem::is_directory(entry)) {
                    // Handle directory
                    if (shouldSkip(entry.path())) {
                        continue;
                    }
                    ThreadPool pool(config_.max_concurrency);
                    pool.enqueue(&FileSearch::searchTask, this, entry.path(), depth + 1);
                } else if (std::filesystem::is_regular_file(entry)) {
                    // Handle file
                    if (entry.path().extension() == config_.file_type) {
                        std::cout << "Found file: " << entry.path() << std::endl;
                        // Do whatever you want with the file
                    }
                }
            }
        } catch (const std::exception &ex) {
            std::cerr << "Error accessing: " << current_path << " - " << ex.what() << std::endl;
        }
    }

    bool shouldSkip(const std::filesystem::path &path) const {
        if (config_.skip_hidden && path.filename().string().front() == '.') {
            return true;
        }
        for (const auto &skip_path : config_.skip_paths) {
            if (path == std::filesystem::path(skip_path)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    SearchConfig config;
    config.root_path = "/home";           // 设置要搜索的根目录
    config.file_type = ".txt";            // 设置要搜索的文件类型
    config.max_concurrency = 4;           // 设置最大并发数
    config.max_depth = 6;                 // 设置最大搜索深度
    config.skip_hidden = true;            // 设置是否跳过隐藏文件或目录

    FileSearch fileSearch(config);
    fileSearch.searchFiles();

    return 0;
}

