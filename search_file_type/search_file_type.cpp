#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct SearchConfig {
    std::string root_path;
    std::string file_type;
    int max_concurrency;
    int max_depth;
    bool skip_hidden;
    std::vector<std::string> skip_paths;
};

class FileSearch {
public:
    FileSearch(const SearchConfig& config) : config_(config), running_threads_(0) {}

    void start() {
        search(config_.root_path, 0);
        while (running_threads_ > 0) {} // 等待所有线程结束
    }

private:
    SearchConfig config_;
    std::mutex mutex_;
    std::condition_variable cv_;
    int running_threads_;

    void search(const std::string& path, int depth) {
        if (depth > config_.max_depth)
            return;

        for (const auto& entry : fs::directory_iterator(path)) {
            const std::string& entry_path = entry.path().string();

            // 如果是目录，且不在跳过列表中，递归搜索
            if (fs::is_directory(entry.status())) {
                if (!shouldSkip(entry_path)) {
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        cv_.wait(lock, [this]() { return running_threads_ < config_.max_concurrency; });
                        ++running_threads_;
                    }

                    std::thread(&FileSearch::search, this, entry_path, depth + 1).detach();
                }
            } 
            // 如果是文件，检查文件类型并输出路径
            else if (fs::is_regular_file(entry.status())) {
                if (entry_path.size() >= config_.file_type.size() && 
                    entry_path.substr(entry_path.size() - config_.file_type.size()) == config_.file_type) {
                    std::lock_guard<std::mutex> lock(mutex_);
                    std::cout << "Found file: " << entry_path << std::endl;
                }
            }
        }
        {
            std::lock_guard<std::mutex> lock(mutex_);
            --running_threads_;
        }
        cv_.notify_all();
    }

    bool shouldSkip(const std::string& path) const {
        // 检查是否跳过隐藏文件或目录
        if (config_.skip_hidden && fs::path(path).filename().string().front() == '.')
            return true;

        // 检查是否跳过指定路径
        for (const auto& skip_path : config_.skip_paths) {
            if (path.find(skip_path) != std::string::npos)
                return true;
        }

        return false;
    }
};

int main() {
    SearchConfig config;
    config.root_path = "/home/mars/code/";
    config.file_type = ".cpp";
    config.max_concurrency = 4;
    config.max_depth = 10;
    config.skip_hidden = true;
    config.skip_paths = {"home/mars/code/leetcode"};

    FileSearch file_search(config);
    file_search.start();

    return 0;
}


