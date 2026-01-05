cmake_minimum_required(VERSION 3.15)

# 工程名与语言
project(GobangCpp
    VERSION 1.0.0
    LANGUAGES CXX
)

# C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 收集源文件
file(GLOB_RECURSE GOBANG_SOURCES
    src/*.cpp
)

# 可执行文件
add_executable(GobangCpp ${GOBANG_SOURCES})

# 头文件搜索路径
target_include_directories(GobangCpp
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# 编译选项（区分编译器）
if (MSVC)
    target_compile_options(GobangCpp PRIVATE /W4)
else()
    target_compile_options(GobangCpp PRIVATE -Wall -Wextra)
endif()
