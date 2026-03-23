#include "ConfigReader.hpp"
#include <fstream>
#include <iostream>

// 注意：加上类名作用域 ConfigReader::
std::string ConfigReader::trim(const std::string& s) {
    const std::string whitespace = " \t\r\n";
    size_t first = s.find_first_not_of(whitespace);
    if (std::string::npos == first) return "";
    size_t last = s.find_last_not_of(whitespace);
    return s.substr(first, (last - first + 1));
}

ConfigReader::ConfigReader(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = trim(line.substr(0, pos));
            std::string val = trim(line.substr(pos + 1));
            if (!key.empty()) _configs[key] = val;
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
