cmake_minimum_required(VERSION 3.8)
project(AutoDiff)

set(TARGET_NAME AutoDiff)

# 设置默认构建类型和相应的编译器标志  Debug  |  Release
set(ReleaseMode off)

if(ReleaseMode)
    set(CMAKE_BUILD_TYPE "Release")
else()
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build Types;${CMAKE_BUILD_TYPE}")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 ")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

file(GLOB_RECURSE SRC_FILES src/*.cpp main.cpp)
add_executable(${TARGET_NAME} ${SRC_FILES})

# 确保项目使用 C++17
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)


# bin 路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)



