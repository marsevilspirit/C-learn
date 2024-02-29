#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <string>
#include <atomic>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

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
    std::atomic<int> running_threads_;

    void search(const std::string& path, int depth) {
        if (depth > config_.max_depth)
            return;

        DIR* dir = opendir(path.c_str());
        if (!dir)
            return;

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            std::string entry_path = path + "/" + entry->d_name;

            // 获取文件信息
            struct stat stat_buf;
            if (stat(entry_path.c_str(), &stat_buf) == -1)
                continue;

            if (S_ISDIR(stat_buf.st_mode)) {
                // 如果是目录，且不在跳过列表中，递归搜索
                if (!shouldSkip(entry_path)) {
                    std::thread(&FileSearch::search, this, entry_path, depth + 1).detach();
                    std::lock_guard<std::mutex> lock(mutex_);
                    ++running_threads_;
                }
            } else if (S_ISREG(stat_buf.st_mode)) {
                // 如果是文件，检查文件类型并输出路径
                size_t file_type_len = config_.file_type.length();
                if (entry_path.length() >= file_type_len && 
                    entry_path.substr(entry_path.length() - file_type_len) == config_.file_type) {
                    std::lock_guard<std::mutex> lock(mutex_);
                    std::cout << "Found file: " << entry_path << std::endl;
                }
            }
        }
        closedir(dir);
        std::lock_guard<std::mutex> lock(mutex_);
        --running_threads_;
    }

    bool shouldSkip(const std::string& path) const {
        // 检查是否跳过隐藏文件或目录
        if (config_.skip_hidden && path.back() == '.')
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
    config.root_path = "home";
    config.file_type = ".c";
    config.max_concurrency = 4;
    config.max_depth = 50;
    config.skip_hidden = true;
    config.skip_paths = {"/path/to/skip"};

    FileSearch file_search(config);
    file_search.start();

    return 0;
}

