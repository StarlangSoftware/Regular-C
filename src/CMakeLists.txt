cmake_minimum_required(VERSION 3.23)
project(Regular C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(Regular src/State.c src/State.h src/Automaton.c src/Automaton.h src/RegularExpression.c src/RegularExpression.h src/Status.c src/Status.h)
target_link_libraries(Regular ${CONAN_LIBS})
