#include "Logger.hpp"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(_mtx);
    
    // 获取当前时间
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto tm_struct = std::localtime(&now);

    // 格式化输出: [2026-03-24 20:00:00] [INFO] Message
    std::stringstream ss;
    ss << "[" << std::put_time(tm_struct, "%Y-%m-%d %H:%M:%S") << "] "
       << "[" << level << "] " << message << std::endl;

    // 同时输出到控制台和文件
    std::cout << ss.str();
    if (_log_file.is_open()) {
        _log_file << ss.str();
        _log_file.flush(); // 确保立即写入磁盘
    }
}
