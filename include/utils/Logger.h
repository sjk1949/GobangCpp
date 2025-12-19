#pragma once

#include <sstream>
#include <string>
#include <mutex>
#include <vector>
#include <utility>

enum class LogLevel
{
    Debug,
    Info,
    Warn,
    Error
};

class Logger
{
public:
    static void log(LogLevel level, const std::string& msg);
    static void debug(const std::string& msg);
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);

    template<typename... Args>
    static void debug(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::Debug, oss.str());
    }

    template<typename... Args>
    static void info(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::Info, oss.str());
    }

    template<typename... Args>
    static void warn(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::Warn, oss.str());
    }

    template<typename... Args>
    static void error(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log(LogLevel::Error, oss.str());
    }
    /**
     * @brief 获取最近几条日志的记录
     * @param num 获取最近日志的数量
     */
    static std::vector<std::string> getRecentLogs(size_t maxCount);

private:
    static std::mutex logMutex;
    static const std::string levelToStr(LogLevel level);

    static std::vector<std::string> logs;
};