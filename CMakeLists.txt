project(tetris)

set(SRC main.cpp
        tetris.cpp)

add_executable(tetris ${SRC})
target_compile_options(tetris PUBLIC -g -std=c++20)
target_link_libraries(tetris sfml-graphics sfml-window sfml-system)
