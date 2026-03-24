#include "ConfigReader.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
// 注意：加上类名作用域 ConfigReader::

std::string ConfigReader::trim(const std::string& s) {
    if (s.empty()) return s;
    std::string res = s;
    
    // 1. 移除末尾的所有空白字符（包含空格、制表符、回车符 \r、换行符 \n）
    res.erase(res.find_last_not_of(" \t\r\n") + 1);
    
    // 2. 移除开头的所有空白字符
    res.erase(0, res.find_first_not_of(" \t\r\n"));
    
    return res;
}

ConfigReader::ConfigReader(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开配置文件: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // 1. 彻底清除 \r (针对 Windows 格式)
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        
        // 2. 去掉前后空格
        line = trim(line);
        
        // 3. 跳过空行和注释
        if (line.empty() || line[0] == '#') continue;

        // 4. 查找等号进行分割
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = trim(line.substr(0, pos));
            std::string val = trim(line.substr(pos + 1));
            
            if (!key.empty()) {
                _configs[key] = val;
                // 调试：看看解析到了什么
                // std::cout << "解析成功: [" << key << "] = [" << val << "]" << std::endl;
            }
        }
    }
}

std::string ConfigReader::getString(const std::string& key, const std::string& default_val) {
    return _configs.count(key) ? _configs[key] : default_val;
}

float ConfigReader::getFloat(const std::string& key, float default_val) {
    if (_configs.count(key)) {
        try { return std::stof(_configs[key]); }
        catch (...) { std::cerr << "Config error: " << key << std::endl; }
    }
    return default_val;
}
