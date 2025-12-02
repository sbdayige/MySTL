cmake_minimum_required(VERSION 3.10)
project(MySTL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(MySTL main.cpp)

# If you had .cpp files for the classes, you would add them here:
# add_executable(MySTL main.cpp MyString.cpp)
