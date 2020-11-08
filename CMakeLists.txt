cmake_minimum_required(VERSION 3.17)
project(OS_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(OS_1 pt.c os.c)
target_link_libraries(OS_1 m)