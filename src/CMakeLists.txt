cmake_minimum_required(VERSION 3.23)
project(Regular)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(dictionary_c REQUIRED)

add_library(Regular State.c State.h Automaton.c Automaton.h RegularExpression.c RegularExpression.h Status.c Status.h)
target_link_libraries(Regular dictionary_c::dictionary_c)
