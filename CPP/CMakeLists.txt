cmake_minimum_required(VERSION 3.19)
project(CPP)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPP src/main.cpp src/WAVFile.cpp include/WAVFile.h include/interpolation.h src/interpolation.cpp)

target_link_libraries(CPP PRIVATE sndfile)