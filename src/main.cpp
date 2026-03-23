#include <iostream>
#include <thread>
#include <atomic>
#include "ConfigReader.hpp"
#include "TemperatureSensor.hpp"
#include "HardwareController.hpp"
#include "NetworkManager.hpp"

std::atomic<bool> g_keep_running(true);

void receive_task(NetworkManager* net, HardwareController* controller) {
    char buffer[1024];
    while (g_keep_running) {
        int fd = net->getSocketFd();
        if (fd < 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }
        int len = recv(fd, buffer, sizeof(buffer) - 1, 0);
        if (len > 0) {
            buffer[len] = '\0';
            std::string cmd(buffer);
            if (cmd.find("FORCE_OFF") != std::string::npos) controller->forceAction(0);
        } else if (len == 0 || (len < 0 && errno != EAGAIN)) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

int main() {
    ConfigReader config("gateway.conf");
    TemperatureSensor sensor(config.getString("TEMP_PATH"));
    HardwareController controller(config.getString("LED_PATH"), config.getFloat("THRESHOLD"));
    NetworkManager network(config.getString("SERVER_IP"), (int)config.getFloat("SERVER_PORT"));

    std::thread recv_thread(receive_task, &network, &controller);
    auto last_reconnect = std::chrono::steady_clock::now();
    bool connected = false;

    while (g_keep_running) {
        float temp = sensor.read();
        controller.update(temp);
        controller.control();

        if (!connected) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - last_reconnect).count() >= 10) {
                connected = network.connectToServer();
                last_reconnect = now;
            }
        } else {
            if (!network.sendData("Temp:" + std::to_string(temp) + "\n")) {
                network.closeConnection();
                connected = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    recv_thread.join();
    return 0;
}
