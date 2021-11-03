#include "tetris.h"
#include "linalg.h"

Game createGame(uint32_t width, uint32_t height)
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

bool collidingWithStructures(Player const& player, Grid const& grid)
{
    auto pred = [&](vec2<int> pos)
    {
        pos += player.position;

        if (pos.y >= grid.size())
        {
            return true;
        }
        if (grid.at(pos.y).at(pos.x).occ)
        {
            return true;
        }

        return false;
    };

    return forEachBlockInPiece(player.tetromino.grid, pred);
}

bool collidingWithWalls(Player const& player, Grid const& grid)
{
    return false;
}

void blitTetrominoToGrid(Player const& player, Grid& grid)
{
    forEachBlockInPiece(player.tetromino.grid, [&](vec2<int> pos){
                pos += player.position;
                grid.at(pos.y).at(pos.x).occ = true;
                return false;
            });
}

TetrominoPiece createTetromino(Piece piece_type)
{
    switch (piece_type)
    {
        case Piece::i_block:
            return {
              { {0,0,0,0}
               ,{1,1,1,1}
               ,{0,0,0,0}
               ,{0,0,0,0}}
            ,TetrisColor::GREEN
            ,{4,4}};
        case Piece::j_block:
            return {
                { {1,0,0}
                 ,{1,1,1}
                 ,{0,0,0}}
             ,TetrisColor::GREEN
             ,{3,3}};
        case Piece::l_block:
            return {
                { {0,0,1}
                 ,{1,1,1}
                 ,{0,0,0}}
             ,TetrisColor::GREEN
             ,{3,3}};
        case Piece::o_block:
            return {
                { {0,1,1,0}
                 ,{0,1,1,0}
                 ,{0,0,0,0}}
             ,TetrisColor::GREEN
             ,{4,3}};
        case Piece::s_block:
            return {
                { {0,1,1}
                 ,{1,1,0}
                 ,{0,0,0}}
             ,TetrisColor::GREEN
             ,{3,3}};
        case Piece::t_block:
            return {
                { {0,1,0}
                 ,{1,1,1}
                 ,{0,0,0}}
             ,TetrisColor::GREEN
             ,{3,3}};
        case Piece::z_block:
            return {
                { {1,1,0}
                 ,{0,1,1}
                 ,{0,0,0}}
             ,TetrisColor::GREEN
             ,{3,3}};
    };

    return TetrominoPiece{{},TetrisColor::GREEN, {0,0}};
}

Tetromino rotateTetromino(Tetromino tetromino)
{
    // TODO: quick hack for o-piece rotation issue
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

Player newPlayer(int width)
{ 
    int piece = std::rand()/((RAND_MAX + 1u)/7);
    std::cout << piece << '\n';
    Player player{ createTetromino(static_cast<Piece>(piece)), vec2<int>(0,0) };
    int spawn_x = (width/2) - (player.tetromino.size.x/2);
    player.position.x = spawn_x;

    return player;
}

void tickGame(Game& game, Player& player)
{
    ++game.ticks;

    ++player.position.y;
    if (collidingWithStructures(player, game.grid))
    {
        std::cout << "Colliding\n";
        --player.position.y;
        blitTetrominoToGrid(player, game.grid);
        player = newPlayer(game.width);
    }
}

std::ostream & operator <<(std::ostream & os, Tetromino const& t)
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
