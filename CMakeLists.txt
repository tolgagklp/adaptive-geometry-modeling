cmake_minimum_required(VERSION 3.14)

project(implicitgeometry CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB LIBRARY_SOURCE_FILES library/src/*.cpp)
file(GLOB TEST_SOURCE_FILES library/test/*.cpp)
file(GLOB HEADER_FILES library/inc/*.h*)

add_library(implicitgeometry SHARED ${LIBRARY_SOURCE_FILES} ${HEADER_FILES})

target_include_directories(implicitgeometry PUBLIC
        ${PROJECT_SOURCE_DIR}/library/inc
        ${PROJECT_SOURCE_DIR}/external
)

add_executable(main drivers/main.cpp ${HEADER_FILES})
target_link_libraries(main implicitgeometry)
target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)

# Optional test runner
option(ENABLE_TESTS "Enable compilation of tests" ON)
if(ENABLE_TESTS)
    add_executable(implicitgeometry_testrunner ${TEST_SOURCE_FILES} ${HEADER_FILES})
    target_link_libraries(implicitgeometry_testrunner implicitgeometry)
endif()
