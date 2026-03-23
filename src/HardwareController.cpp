#include "HardwareController.hpp"
#include <fstream>
#include <chrono>

void HardwareController::update(float temp) {
    std::lock_guard<std::mutex> lock(_mtx);
    if (_is_forced) return;

    if (temp >= _threshold + 5.0f) _current_state = CRITICAL;
    else if (temp >= _threshold) _current_state = WARNING;
    else _current_state = SAFE;
}

void HardwareController::control() {
    auto now = std::chrono::steady_clock::now();
    int target = -1;

    switch (_current_state) {
        case CRITICAL: target = 1; break;
        case SAFE:     target = 0; break;
        case WARNING: {
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - _last_action_time);
            if (diff.count() >= 500) {
                _toggle = !_toggle;
                target = _toggle ? 1 : 0;
                _last_action_time = now;
            }
            break;
        }
    }

    if (target != -1 && target != _last_hardware_value) {
        std::ofstream file(_led_path + "/brightness");
        if (file.is_open()) {
            file << target;
            _last_hardware_value = target;
        }
    }
}

void HardwareController::forceAction(int val) {
    std::lock_guard<std::mutex> lock(_mtx);
    _is_forced = true;
    _forced_value = val;
}

void HardwareController::setForceMode(bool enable) {
    std::lock_guard<std::mutex> lock(_mtx);
    _is_forced = enable;
}
