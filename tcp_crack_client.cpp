#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return -1;
    }

    SOCKET sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        WSACleanup();
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    std::string password;
    std::cout << "Enter password to test (try 'admin' or '123'): ";
    std::cin >> password;

    send(sock, password.c_str(), password.length(), 0);
    std::cout << "Password sent. Waiting for analysis..." << std::endl;

    recv(sock, buffer, BUFFER_SIZE, 0);
    std::cout << "Server Report: " << buffer << std::endl;

    closesocket(sock);
    WSACleanup();

    system("pause");
    return 0;
}