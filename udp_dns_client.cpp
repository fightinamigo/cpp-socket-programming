#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return -1;
    }

    SOCKET sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    int addrLen = sizeof(serverAddr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        WSACleanup();
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(true) {
        std::string hostname;
        std::cout << "\nEnter hostname to resolve (or 'exit'): ";
        std::cin >> hostname;

        if (hostname == "exit") break;

        sendto(sockfd, hostname.c_str(), hostname.length(), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        std::cout << "Request sent to server..." << std::endl;

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverAddr, &addrLen);
        if (n != SOCKET_ERROR) {
            buffer[n] = '\0';
            std::cout << "Server Response: " << buffer << std::endl;
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}