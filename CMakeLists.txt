cmake_minimum_required(VERSION 3.13)
project(System_Design)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/utility)
include_directories(include/algorithms)

set(SOURCES
        src/algorithms/a_star.cpp
        src/algorithms/bfs1_k.cpp
        src/algorithms/dijkstra.cpp
        src/algorithms/dinic.cpp
        src/algorithms/floyd_warshall.cpp
        src/algorithms/ford_bellman.cpp
        src/algorithms/kuhn.cpp
        src/algorithms/mincost_kflow.cpp
        src/utility/utility.cpp
)

add_library(System_Design STATIC ${SOURCES})

target_include_directories(System_Design PUBLIC include)

add_subdirectory(tests)

