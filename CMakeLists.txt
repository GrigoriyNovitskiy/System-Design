cmake_minimum_required(VERSION 3.13)
project(System_Design)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
        src/
)

add_executable(System_Design ${SOURCES})
