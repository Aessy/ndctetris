#include "tetris.h"
#include <iostream>

int main()
{
    auto tetromino = createTetromino(Piece::z_block);

    std::cout << tetromino;
    tetromino = rotateTetromino(tetromino);
    std::cout << '\n';
    std::cout << tetromino;
    tetromino = rotateTetromino(tetromino);
    std::cout << '\n';
    std::cout << tetromino;
    tetromino = rotateTetromino(tetromino);
    std::cout << '\n';
    std::cout << tetromino;
    tetromino = rotateTetromino(tetromino);
    std::cout << '\n';
    std::cout << tetromino;
}
