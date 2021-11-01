#pragma once

#include <cstdint>
#include <vector>
#include <ostream>

#include <boost/optional.hpp>

struct Point
{
    bool occ {false};
};

using Tetromino = std::vector<std::vector<bool>>;

enum class Piece
{
      i_block
    , j_block
    , l_block
    , o_block
    , s_block
    , t_block
    , z_block
};

struct Player
{
    boost::optional<Tetromino> active_tetromino;
    vec2<int> position{0,0};
};

struct Game
{
    std::vector<std::vector<Point>> grid{};

    uint32_t ticks{};

    uint32_t hight{};
    uint32_t width{};
};

Game createGame(uint32_t height, uint32_t width);

Tetromino createTetromino(Piece piece_type);
Tetromino rotateTetromino(Tetromino tetromino);

inline std::ostream & operator <<(std::ostream & os, Tetromino const& t)
{
    for (auto row : t)
    {
        for (auto col : row)
        {
            os << col << " ";
        }
        os << "\n";
    }

    return os;
}
