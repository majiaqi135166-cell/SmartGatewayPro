#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <string>
#include <map>

class ConfigReader {
private:
    // 使用 map 存储键值对，查找非常方便
    std::map<std::string, std::string> _configs;

public:
    // 构造函数直接读取文件
    ConfigReader(const std::string& filename);

    // 根据键名获取字符串值
    std::string getString(const std::string& key, const std::string& default_val = "");

    // 根据键名获取浮点值（用于阈值）
    float getFloat(const std::string& key, float default_val = 0.0f);
    std::string trim(const std::string& s);
};

#endif
