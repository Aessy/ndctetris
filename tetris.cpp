#include "tetris.h"
#include "linalg.h"

Game createGame(uint32_t height, uint32_t width)
{
    std::vector<Point> row(width);
    Game game{{}, 0, height, width};

    for (int i = 0; i < height; ++i)
    {
        game.grid.push_back(row);
    }

    return game;
}

static Tetromino clear(Tetromino t)
{
    for (auto& row : t)
    {
        for (auto col : row)
        {
            col = 0;
        }
    }

    return t;
}

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

bool collidingWithStructures(Player const& player, Grid const& grid)
{
    auto pred = [&](vec2<int> pos)
    {
        pos += player.position;

        if (pos.y > grid.size())
        {
            return true;
        }
        if (grid.at(pos.y).at(pos.x).occ)
        {
            return true;
        }

        return false;
    };

    return forEachBlockInPiece(player.tetromino, pred);
}

bool collidingWithWalls(Tetromino const& tetromino, Grid const& grid)
{
    return false;
}

bool blitTetrominoToGrid(Player const& player, Grid& grid)
{
    forEachBlockInPiece(player.tetromino, [&grid](vec2<int> pos){
                pos += player.position;
                grid.at(pos.y).at(pos.x).occ = true;
                return false;
            });
}

Tetromino createTetromino(Piece piece_type)
{
    switch (piece_type)
    {
        case Piece::i_block:
            return { {0,0,0,0}
                    ,{1,1,1,1}
                    ,{0,0,0,0}
                    ,{0,0,0,0}};
        case Piece::j_block:
            return { {1,0,0}
                    ,{1,1,1}
                    ,{0,0,0}};
        case Piece::l_block:
            return { {0,0,1}
                    ,{1,1,1}
                    ,{0,0,0}};
        case Piece::o_block:
            return { {0,1,1,0}
                    ,{0,1,1,0}
                    ,{0,0,0,0}};
        case Piece::s_block:
            return { {0,1,1}
                    ,{1,1,0}
                    ,{0,0,0}};
        case Piece::t_block:
            return { {0,1,0}
                    ,{1,1,1}
                    ,{0,0,0}};
        case Piece::z_block:
            return { {1,1,0}
                    ,{0,1,1}
                    ,{0,0,0}};
    };

    return Tetromino{};
}

Tetromino rotateTetromino(Tetromino tetromino)
{
    // quick hack for o-piece rotation issue
    if (tetromino.size() != tetromino[0].size())
        return tetromino;

    // TODO: Bounds checking.
    Tetromino new_piece = clear(tetromino);
    for (int y = 0; y < tetromino.size(); ++y)
    {
        for (int x = 0; x < tetromino[y].size(); ++x)
        {
            if (tetromino[y][x])
            {
                new_piece[x][tetromino.size()-1-y] = 1;
            }
        }
    }

    return new_piece;
}
