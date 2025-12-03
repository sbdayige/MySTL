cmake_minimum_required(VERSION 3.10)
project(MySTL)

# 生成 compile_commands.json 以供 VS Code IntelliSense 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加头文件目录，这样 main.cpp 可以直接 #include "MyVector.hpp"
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/h)

# 1. 主程序
add_executable(MySTL main.cpp)

# 2. 头文件检查库 (OBJECT library)
# 将 h/ 目录下的头文件加入此库，强制 CMake 生成编译命令
add_library(header_checks OBJECT
    h/MyQueue.hpp
    h/MyString.hpp
    h/MyVector.hpp
)

# 3. 强制将 .hpp 文件识别为 C++ 源文件
# 这样 CMake 才会为它们生成编译命令，从而让 IDE 能正确检查头文件中的错误
set_source_files_properties(
    h/MyQueue.hpp
    h/MyString.hpp
    h/MyVector.hpp
    PROPERTIES LANGUAGE CXX
)
