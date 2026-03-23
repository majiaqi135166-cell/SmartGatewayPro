#ifndef HARDWARE_CONTROLLER_HPP
#define HARDWARE_CONTROLLER_HPP

#include <string>
#include <chrono>
#include <mutex>
class HardwareController {
public:
    // 软考考点：定义状态枚举，增强代码可读性与可靠性
    enum State {
        SAFE,       // 安全：灯灭
        WARNING,    // 预警：灯闪烁（逻辑预留）
        CRITICAL    // 紧急：灯常亮
    };

private:
    std::string _led_path;
    float _threshold;
    State _current_state;
    std::chrono::steady_clock::time_point _last_action_time;
    int _toggle;
    int _last_hardware_value;
    std::mutex _mtx;
    bool _is_forced;
    int _forced_value;
public:
    HardwareController(const std::string& path, float threshold)
        : _led_path(path), _threshold(threshold), _current_state(SAFE),_last_hardware_value(0),_is_forced(false),_forced_value(0){}
    void forceAction(int val);
    void update(float temp); // 根据温度更新状态
    void control();         // 根据状态控制硬件
    void setForceMode(bool enable);
};

#endif
