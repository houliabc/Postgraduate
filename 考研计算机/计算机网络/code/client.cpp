// Windows TCP 客户端 (专门用于连接 Ubuntu 8888 端口)
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// 你的公网IP
#define SERVER_IP "23.95.166.162"
#define SERVER_PORT 8888

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // 创建socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("socket创建失败\n");
        return 1;
    }

    // 配置服务器地址
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &addr.sin_addr);

    // 连接 (触发 TCP 三次握手)
    printf("正在连接 %s:%d...\n", SERVER_IP, SERVER_PORT);
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf("连接失败！检查服务器是否运行/防火墙是否开放8888\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("✅ 连接成功！按 Ctrl+C 断开 (触发四次挥手)\n");

    // 保持连接
    while (1) { Sleep(1000); }

    // 关闭连接
    closesocket(sock);
    WSACleanup();
    return 0;
}