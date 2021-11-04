#pragma once

#include <cstdint>
#include <vector>
#include <ostream>

#include <boost/optional.hpp>

#include "linalg.h"

struct Point
{
    bool occ {false};
};

using Tetromino = std::vector<std::vector<bool>>;
using Grid = std::vector<std::vector<Point>>;

enum class TetrisColor
{
    GREEN,
    BLACK,
    PINK
};

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

struct TetrominoPiece
{
    Tetromino grid;
    TetrisColor color;
    vec2<int> size;
};

struct Player
{
    TetrominoPiece tetromino;
    vec2<int> position{0,0};
};

struct Game
{
    std::vector<std::vector<Point>> grid{};

    uint32_t ticks{};

    uint32_t hight{};
    uint32_t width{};

    float current_speed {0.8f};
    bool fast_drop {false};

    float elapsed {};
    float last_tick {};
};

template<typename Pred>
static bool forEachBlockInPiece(Tetromino const& tetromino, Pred pred)
{
    for (int y = 0; y < tetromino.size(); ++y)
    {
        for (int x = 0; x < tetromino[y].size(); ++x)
        {
            if (tetromino[y][x])
            {
                if (pred(vec2<int>(x, y)))
                {
                    return true;
                }
            }
        }
    }

    return false;
}



Game createGame(uint32_t width, uint32_t height);
TetrominoPiece createTetromino(Piece piece_type);
Tetromino rotateTetromino(Tetromino tetromino);
void movePlayer(int dir, Player& player, Game const& game);
void rotatePlayer(Player& player, Game const& game);

void tickGame(Game& game, Player& player, float elapsed);
Player newPlayer(int width);

std::ostream & operator <<(std::ostream & os, Tetromino const& t);
