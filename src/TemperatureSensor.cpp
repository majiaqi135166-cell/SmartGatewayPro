#include "TemperatureSensor.hpp"
#include <fstream>

TemperatureSensor::TemperatureSensor(const std::string& path) 
    : _path(path), _last_temp(0.0f) {}

float TemperatureSensor::read() {
    std::ifstream file(_path);
    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line)) {
            _last_temp = std::stof(line) / 1000.0f;
        }
    }
    return _last_temp;
}
