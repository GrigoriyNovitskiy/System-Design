include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest)

add_library(GTest::Main INTERFACE IMPORTED)
target_link_libraries(GTest::Main INTERFACE gtest_main)

include_directories(../include/algorithms)
include_directories(../include/utility)

add_executable(tests
        testBFS_1k.cpp
        test_graph.cpp
        main.cpp
        ../src/algorithms/bfs1_k.cpp
)

target_link_libraries(tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

enable_testing()
add_test(bfs1k_gtests tests)
