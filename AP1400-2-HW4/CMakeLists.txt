cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_test.cpp
        # src/shared_ptr.cpp
        # src/unique_ptr.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
)