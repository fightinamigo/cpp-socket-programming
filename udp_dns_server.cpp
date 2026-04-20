#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
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
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    int addrLen = sizeof(clientAddr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        WSACleanup();
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(sockfd);
        WSACleanup();
        return -1;
    }

    std::map<std::string, std::string> dnsTable;
    dnsTable["google.com"] = "142.250.190.46";
    dnsTable["youtube.com"] = "208.65.153.238";
    dnsTable["facebook.com"] = "157.240.195.35";
    dnsTable["local"] = "127.0.0.1";

    std::cout << "UDP DNS Server running on port " << PORT << "..." << std::endl;

    while (true) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addrLen);
        if (n == SOCKET_ERROR) continue;

        buffer[n] = '\0';
        std::string request(buffer);
        std::cout << "Client requested: " << request << std::endl;

        std::string response;
        if (dnsTable.find(request) != dnsTable.end()) {
            response = "IP Address: " + dnsTable[request];
        } else {
            response = "Error: Hostname not found.";
        }

        sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr *)&clientAddr, addrLen);
        std::cout << "Sent response: " << response << std::endl;
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}