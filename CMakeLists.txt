cmake_minimum_required(VERSION 3.9)
project(marguerite)

set(CMAKE_CXX_STANDARD 11)

add_executable(marguerite
        net/Socket.cpp
        net/Socket.hpp io/BinaryStream.cpp io/BinaryStream.hpp)
