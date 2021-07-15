cmake_minimum_required(VERSION 3.19)
project(Gameboy)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(Gameboy main.cpp
                        CPU/CPU.cpp CPU/CPU.h
                        CPU/Memory/Memory.cpp
                        CPU/Memory/Memory.h
                        CPU/Memory/MemUtils/MemUtils.h)