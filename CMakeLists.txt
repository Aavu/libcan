cmake_minimum_required(VERSION 3.10)
project(libcan)

set(CMAKE_CXX_STANDARD 17)

add_library(
        libcan
        src/CANAdapter.cpp
        src/CANFrameParser.cpp
        src/SocketCAN.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(test test/test.cpp)
target_link_libraries(test PUBLIC libcan -lpthread)