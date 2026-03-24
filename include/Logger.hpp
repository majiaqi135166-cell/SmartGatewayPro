#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>
#include <iostream>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& level, const std::string& message);

private:
    Logger() : _log_file("gateway.log", std::ios::app) {}
    ~Logger() { if (_log_file.is_open()) _log_file.close(); }
    
    std::ofstream _log_file;
    std::mutex _mtx; // 保证多线程写日志时不会乱序
};

#endif
