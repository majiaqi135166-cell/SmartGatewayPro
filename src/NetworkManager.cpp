#include "NetworkManager.hpp"
#include <iostream>
#include <cstring>

NetworkManager::NetworkManager(const std::string& ip, int port)
    : _sock_fd(-1), _server_ip(ip), _server_port(port), _is_connected(false) {}

bool NetworkManager::connectToServer() {
    // 1. 彻底清理旧连接
    closeConnection();

    // 2. 创建 Socket
    _sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock_fd < 0) {
        perror("Socket 创建失败");
        return false;
    }

    // 3. 设置地址
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr)); // 清空结构体，防止垃圾数据
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_server_port);

std::cout << "正在尝试转换 IP: [" << _server_ip << "]" << std::endl;    
    if (inet_pton(AF_INET, _server_ip.c_str(), &addr.sin_addr) <= 0) {
        std::cerr << "无效的 IP 地址: " << _server_ip << std::endl;
        closeConnection();
        return false;
    }

    // 4. 尝试连接
    std::cout << "正在连接 " << _server_ip << ":" << _server_port << "..." << std::endl;
    if (connect(_sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        // 打印具体的系统错误原因（比如 Connection refused）
        std::cerr << "连接失败原因: " << strerror(errno) << std::endl;
        closeConnection();
        return false;
    }

    _is_connected = true;
    std::cout << ">>> 连接服务器成功！" << std::endl;
    return true;
}

bool NetworkManager::sendData(const std::string& data) {
    if (!_is_connected) return false;
    if (send(_sock_fd, data.c_str(), data.length(), 0) < 0) {
        _is_connected = false;
        return false;
    }
    return true;
}

void NetworkManager::closeConnection() {
    if (_sock_fd >= 0) { close(_sock_fd); _sock_fd = -1; }
    _is_connected = false;
}

NetworkManager::~NetworkManager() { closeConnection(); }
