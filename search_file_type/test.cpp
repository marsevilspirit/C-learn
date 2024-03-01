#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <filesystem>

struct SearchConfig {
    std::string root_path;              // 要搜索的根目录
    std::string file_type;              // 要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;                // 最大并发数 
    int max_depth;                      // 最大搜索深度
    bool skip_hidden;                   // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths;// 要跳过的目录或文件的路径
};

class FileSearch{
public:
    FileSearch(const SearchConfig& config): config_(config) {}

    void searchFiles()
    {
        std::queue<std::filesystem::path> paths;
        paths.push(std::filesystem::path(config_.root_path));

        while (!paths.empty()) 
        {
            std::filesystem::path current_path = paths.front();
            paths.pop();

            try {
                for (const auto& entry : std::filesystem::directory_iterator(current_path)) 
                {
                    if (std::filesystem::is_directory(entry)) {
                        // Handle directory
                        if (shouldSkip(entry.path())) {
                            continue;
                        }
                        paths.push(entry.path());
                    } else if (std::filesystem::is_regular_file(entry)) {
                        // Handle file
                        if (entry.path().extension() == config_.file_type) {
                            std::cout << "Found file: " << entry.path() << std::endl;
                            // Do whatever you want with the file
                        }
                    }
                }
            } catch (const std::exception& ex) {
                std::cerr << "Error accessing: " << current_path << " - " << ex.what() << std::endl;
            }
        }
    }

private:
    SearchConfig config_;
    
    bool shouldSkip(const std::filesystem::path& path) const {
        if (config_.skip_hidden && path.filename().string().front() == '.') {
            return true;
        }
        for (const auto& skip_path : config_.skip_paths) {
            if (path == std::filesystem::path(skip_path)) {
                return true;
            }
        }
        return false;
    }
};


int main() {
    SearchConfig config;
    config.root_path = "/home"; // 设置要搜索的根目录
    config.file_type = ".cpp";            // 设置要搜索的文件类型
    config.max_concurrency = 4;           // 设置最大并发数
    config.max_depth = 5;                 // 设置最大搜索深度
    config.skip_hidden = true;            // 设置是否跳过隐藏文件或目录

    FileSearch fileSearch(config);
    fileSearch.searchFiles();

    return 0;
}

