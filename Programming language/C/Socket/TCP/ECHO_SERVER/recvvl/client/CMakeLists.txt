cmake_minimum_required(VERSION 3.9)
project(client C)

set(CMAKE_C_STANDARD 11)

add_executable(client main.c)

TARGET_LINK_LIBRARIES(client -lwsock32)