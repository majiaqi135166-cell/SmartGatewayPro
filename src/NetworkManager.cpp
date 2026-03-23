#include "NetworkManager.hpp"
#include <iostream>

NetworkManager::NetworkManager(const std::string& ip, int port)
    : _sock_fd(-1), _server_ip(ip), _server_port(port), _is_connected(false) {}

bool NetworkManager::connectToServer() {
    _sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock_fd < 0) return false;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_server_port);
    inet_pton(AF_INET, _server_ip.c_str(), &addr.sin_addr);

    if (connect(_sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(_sock_fd);
        return false;
    }
    _is_connected = true;
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
