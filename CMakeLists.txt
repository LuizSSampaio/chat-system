cmake_minimum_required(VERSION 3.30)
project(chat-system)

add_executable(server src/server/main.cpp)
add_executable(client src/client/main.cpp)