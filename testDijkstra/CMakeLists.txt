# CMake 最低版本号要求
cmake_minimum_required( VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# 项目信息
project (demo)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

if(CMAKE_COMPILER_IS_GNUCXX OR MINGW OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
SET(THREADLIB "pthread")
ENDIF()

find_package(Boost 1.63 REQUIRED COMPONENTS thread chrono filesystem)


include_directories(${CMAKE_CURRENT_BINARY_DIR})


include_directories(
    include
    src
    )
    

set( SOURCES
    src/demo.cpp
    src/dijkstra.cpp
    )

# 指定生成目标
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})