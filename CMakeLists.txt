cmake_minimum_required(VERSION 3.10)
project(CppReconTool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(recon ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(recon Threads::Threads)