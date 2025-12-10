#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

// 辅助函数：检查字符串是否以特定后缀结尾
bool endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

// 获取当前时间字符串
std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buffer);
}

class SimpleFileMerger {
public:
    bool mergeFiles(const std::string& sourceDir, 
                   const std::string& outputFile,
                   bool recursive = false) {
        
        // 获取文件列表
        std::vector<std::string> files;
        if (recursive) {
            listSourceFilesRecursive(sourceDir, sourceDir, files);
        } else {
            listSourceFiles(sourceDir, files);
        }
        
        if (files.empty()) {
            std::cerr << "错误：没有找到任何源文件" << std::endl;
            return false;
        }
        
        // 按路径排序
        std::sort(files.begin(), files.end());
        
        // 打开输出文件
        std::ofstream outFile(outputFile);
        if (!outFile) {
            std::cerr << "错误：无法创建输出文件" << std::endl;
            return false;
        }
        
        // 写入头部
        outFile << "/*\n * 合并的源文件\n"
                << " * 来源目录: " << sourceDir << "\n"
                << " * 文件数量: " << files.size() << "\n"
                << " * 生成时间: " << getCurrentTime() << "\n"
                << " */\n\n";
        
        // 处理每个文件
        for (const auto& filepath : files) {
            std::string displayPath = filepath;
            
            // 如果是相对路径，移除基础目录部分
            if (filepath.find(sourceDir) == 0) {
                displayPath = filepath.substr(sourceDir.length());
                if (displayPath[0] == '/') displayPath = displayPath.substr(1);
            }
            
            outFile << "\n/* ============================================ */\n"
                    << "/* 文件: " << displayPath << " */\n"
                    << "/* ============================================ */\n\n";
            
            if (!appendFile(outFile, filepath)) {
                std::cerr << "警告：无法读取 " << filepath << std::endl;
            }
        }
        
        std::cout << "成功合并 " << files.size() << " 个文件到 " << outputFile << std::endl;
        return true;
    }
    
private:
    bool listSourceFiles(const std::string& dir, 
                        std::vector<std::string>& files) {
        DIR* dp = opendir(dir.c_str());
        if (!dp) return false;
        
        struct dirent* entry;
        while ((entry = readdir(dp)) != nullptr) {
            std::string filename(entry->d_name);
            
            // 跳过特殊目录
            if (filename == "." || filename == "..") continue;
            
            std::string fullpath = dir + "/" + filename;
            
            // 检查是否为普通文件
            struct stat statbuf;
            if (stat(fullpath.c_str(), &statbuf) == 0) {
                if (S_ISREG(statbuf.st_mode)) {  // 是普通文件
                    if (isSourceFile(filename)) {
                        files.push_back(fullpath);
                    }
                }
            }
        }
        
        closedir(dp);
        return true;
    }
    
    void listSourceFilesRecursive(const std::string& baseDir,
                                 const std::string& currentDir,
                                 std::vector<std::string>& files) {
        DIR* dp = opendir(currentDir.c_str());
        if (!dp) return;
        
        struct dirent* entry;
        while ((entry = readdir(dp)) != nullptr) {
            std::string filename(entry->d_name);
            
            if (filename == "." || filename == "..") continue;
            
            std::string fullpath = currentDir + "/" + filename;
            
            struct stat statbuf;
            if (stat(fullpath.c_str(), &statbuf) == 0) {
                if (S_ISDIR(statbuf.st_mode)) {
                    // 递归处理子目录
                    listSourceFilesRecursive(baseDir, fullpath, files);
                } else if (S_ISREG(statbuf.st_mode)) {
                    if (isSourceFile(filename)) {
                        files.push_back(fullpath);
                    }
                }
            }
        }
        
        closedir(dp);
    }
    
    bool isSourceFile(const std::string& filename) {
        std::string lower = filename;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        
        return endsWith(lower, ".cpp") || endsWith(lower, ".h") ||
               endsWith(lower, ".hpp") || endsWith(lower, ".cxx") ||
               endsWith(lower, ".cc") || endsWith(lower, ".c");
    }
    
    bool appendFile(std::ofstream& outFile, const std::string& filepath) {
        std::ifstream inFile(filepath);
        if (!inFile) return false;
        
        std::string line;
        while (std::getline(inFile, line)) {
            outFile << line << "\n";
        }
        
        return true;
    }
};

int main() {
    SimpleFileMerger merger;
    
    // 使用示例
    std::string sourceDir = "./src";
    std::string outputFile = "merged_output.cpp";
    bool recursive = true;
    
    if (merger.mergeFiles(sourceDir, outputFile, recursive)) {
        return 0;
    } else {
        return 1;
    }
}