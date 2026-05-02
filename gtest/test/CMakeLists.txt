cmake_minimum_required(VERSION 4.0) 
project(GTESTWIN_TEST)

# include gtest & gmock
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/googletest/googletest-1.17.0/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/googletest/googletest-1.17.0/googlemock/include)

# include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# include gtest lib
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/googletest/gtest-1.17.0-build/lib)

AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/../src" SRC_FILES)

#set(SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")

# add test source files
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}" TEST_SRCS)

# add executable
add_executable(gtest_win_test ${SRC_FILES} ${TEST_SRCS})

target_link_libraries(gtest_win_test
        PRIVATE 
        gtest
        gtest_main
        gmock
        gmock_main
        pthread )

# --- Code Coverage Extend ---

set(COVERAGE_FLAGS "--coverage -fprofile-arcs -ftest-coverage -O0 -g")

target_compile_options(gtest_win_test PRIVATE --coverage -fprofile-arcs -ftest-coverage -O0 -g)
target_link_options(gtest_win_test PRIVATE --coverage)

if(MINGW)
    target_link_libraries(gtest_win_test PRIVATE gcov)
endif()