#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8081
#define BUFFER_SIZE 1024

std::string crackPassword(std::string target) {
    std::vector<std::string> commonPass = {"123456", "password", "admin", "welcome", "1111"};
    
    for(const auto& pass : commonPass) {
        if(pass == target) return "Password CRACKED via Dictionary Attack! Value: " + pass;
    }

    for(int i = 0; i <= 999; i++) {
        std::string pin = std::to_string(i);
        if(pin == target) return "Password CRACKED via Brute Force! Value: " + pin;
    }

    return "Password too strong (Simulation failed).";
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return -1;
    }

    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        WSACleanup();
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    if (listen(server_fd, 3) == SOCKET_ERROR) {
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    std::cout << "TCP Password Cracker Server running on port " << PORT << "..." << std::endl;

    while(true) {
        std::cout << "Waiting for client..." << std::endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        recv(new_socket, buffer, BUFFER_SIZE, 0);
        std::string targetPass(buffer);
        std::cout << "Target password received: " << targetPass << ". Cracking..." << std::endl;

        std::string result = crackPassword(targetPass);

        send(new_socket, result.c_str(), result.length(), 0);
        std::cout << "Result sent to client.\n" << std::endl;

        closesocket(new_socket);
    }
    
    closesocket(server_fd);
    WSACleanup();
    return 0;
}