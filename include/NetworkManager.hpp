#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class NetworkManager {
private:
    int _sock_fd;           // 套接字文件描述符
    std::string _server_ip;
    int _server_port;
    bool _is_connected;

public:
    NetworkManager(const std::string& ip, int port);
    ~NetworkManager();      // 析构函数负责关闭连接

    bool connectToServer(); // 建立连接
    bool sendData(const std::string& data); // 发送字符串（如温度）
    void closeConnection();
    int getSocketFd() const { return _sock_fd; }
};

#endif
