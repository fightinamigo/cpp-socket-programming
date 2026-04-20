cmake_minimum_required(VERSION 4.0)
project(socket_programming)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 udp_dns_server.cpp
        udp_dns_client.cpp
        tcp_crack_server.cpp
        tcp_crack_client.cpp)
