#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include <string>

class TemperatureSensor {
private:
    std::string _path;
    float _last_temp;

public:
    TemperatureSensor(const std::string& path);
    float read();
};

#endif // 必须加上这一句！
