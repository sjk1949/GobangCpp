#include "utils/Logger.h"

#include <mutex>
#include <sstream>

std::mutex Logger::logMutex;
std::vector<std::string> Logger::logs;

const std::string Logger::levelToStr(LogLevel level) {
    switch (level)
    {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warn:
        return "WARN";
    case LogLevel::Error:
        return "ERROR";
    }
    return "";
}

void Logger::log(LogLevel level, const std::string& msg) {
    std::stringstream ss;
    ss << "[" << levelToStr(level) << "] " << msg;
    std::lock_guard<std::mutex> lock(logMutex);
    logs.push_back(ss.str());
}

void Logger::debug(const std::string& msg) {log(LogLevel::Debug, msg);}
void Logger::info(const std::string& msg) {log(LogLevel::Info, msg);}
void Logger::warn(const std::string& msg) {log(LogLevel::Warn, msg);}
void Logger::error(const std::string& msg) {log(LogLevel::Error, msg);}

std::vector<std::string> Logger::getRecentLogs(size_t maxCount) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logs.empty()) {
        return {};
    }
    size_t count = std::min(maxCount, logs.size());
    return std::vector<std::string>(logs.end() - count, logs.end());
}