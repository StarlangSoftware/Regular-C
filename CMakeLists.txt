cmake_minimum_required(VERSION 3.23)
project(Regular C)

set(CMAKE_C_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(Regular src/State.c src/State.h src/Automaton.c src/Automaton.h src/RegularExpression.c src/RegularExpression.h)
target_link_libraries(Regular ${CONAN_LIBS})
add_executable(TestDfa src/State.c src/State.h src/Automaton.c src/Automaton.h Test/TestDfa.c)
target_link_libraries(TestDfa ${CONAN_LIBS})
add_executable(TestNfa src/State.c src/State.h src/Automaton.c src/Automaton.h Test/TestNfa.c)
target_link_libraries(TestNfa ${CONAN_LIBS})
add_executable(TestRegularExpression src/State.c src/State.h src/Automaton.c src/Automaton.h src/RegularExpression.c src/RegularExpression.h Test/TestRegularExpression.c)
target_link_libraries(TestRegularExpression ${CONAN_LIBS})
