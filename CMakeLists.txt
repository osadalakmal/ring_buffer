cmake_minimum_required(VERSION 3.0.0)
project(ring_buf_bench VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

find_package(PkgConfig REQUIRED)
pkg_search_module(PKG_BENCHMARK REQUIRED benchmark)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(ring_buf_test _main.cpp)
add_executable(ring_buf_bench main.cpp)
target_include_directories(ring_buf_bench PRIVATE ${PKG_BENCHMARK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
target_link_libraries(ring_buf_bench
    ${PKG_BENCHMARK_LDFLAGS}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(ring_buf_test PRIVATE ${PKG_BENCHMARK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
target_link_libraries(ring_buf_test
        ${PKG_BENCHMARK_LDFLAGS}
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})
    
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
