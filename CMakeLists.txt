cmake_minimum_required(VERSION 3.9)
project(marguerite
        VERSION 1.0.1
        DESCRIPTION "simple handy modern c++ library")

set(CMAKE_CXX_STANDARD 17)

add_library(marguerite STATIC
        net/Socket.cpp
        net/Socket.hpp
        io/BinaryStream.cpp
        io/BinaryStream.hpp
        threading/ThreadPool.cpp
        threading/ThreadPool.hpp
        io/BinaryStreamReader.cpp
        io/BinaryStreamReader.hpp
        io/BinaryStreamWriter.cpp
        io/BinaryStreamWriter.hpp)

target_include_directories(marguerite PRIVATE .)
set_target_properties(marguerite PROPERTIES VERSION ${PROJECT_VERSION})
set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) # only if you want copy from the build tree

add_executable(crazy_tester
        unit_tests/main.cpp unit_tests/main.cpp)
target_link_libraries(crazy_tester marguerite)
