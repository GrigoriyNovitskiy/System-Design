cmake_minimum_required(VERSION 3.13)
project(System_Design)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
        src/algorithms/a_star.cpp
        src/algorithms/bfs1_k.cpp
        src/algorithms/dijkstra.cpp
        src/algorithms/dinic.cpp
        src/algorithms/floyd_warshall.cpp
        src/algorithms/ford_bellman.cpp
        src/algorithms/kuhn.cpp
        src/algorithms/mincost_kflow.cpp
        src/main.cpp
        tests/main.cpp
)

# Option to enable or disable style checks
option(ENABLE_STYLE_CHECKS "Enable style checks" ON)
if(ENABLE_STYLE_CHECKS)
  add_subdirectory("src/tests/style")
endif()

add_executable(System_Design ${SOURCES})
