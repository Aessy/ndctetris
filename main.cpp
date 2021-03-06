#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "tetris.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    static constexpr uint32_t brick_size = 25;

    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(250,500), "Tetris", sf::Style::Resize);

    auto game = createGame(10, 20);
    Player player = newPlayer(game.width);

    auto start = std::chrono::system_clock::now();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    movePlayer(-1, player, game);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    movePlayer(1, player, game);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    game.fast_drop = true;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    rotatePlayer(player, game);
                }
            }
        }

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end-start;
        start = end;
        tickGame(game, player, elapsed_seconds.count());

        window.clear(sf::Color::White);

        // Draw the game grid
        for (int y = 0; y < game.grid.size(); ++y)
        {
            for (int x = 0; x < game.grid[y].size(); ++x)
            {
                if (game.grid[y][x].occ)
                {
                    sf::RectangleShape rect{sf::Vector2f(brick_size-1, brick_size-1)};
                    rect.setFillColor(sf::Color(100, 250, 50));
                    rect.setPosition(sf::Vector2f((x*brick_size)+1, (y*brick_size)+1));
                    window.draw(rect);
                }
                else
                {
                    sf::RectangleShape rect{sf::Vector2f(brick_size-1, brick_size-1)};
                    rect.setFillColor(sf::Color(0, 0, 0));
                    rect.setPosition(sf::Vector2f((x*brick_size)+1, (y*brick_size)+1));
                    window.draw(rect);
                }
            }
        }

        // Draw the player
        forEachBlockInPiece(player.tetromino.grid,[&player, &window](auto pos){
                pos += player.position;
                sf::RectangleShape rect{sf::Vector2f(brick_size-1, brick_size-1)};
                rect.setFillColor(sf::Color(100, 250, 50));
                rect.setPosition(sf::Vector2f((pos.x*brick_size)+1, (pos.y*brick_size)+1));
                window.draw(rect);
                return false;
                });

        window.display();
        std::this_thread::sleep_for (std::chrono::milliseconds(2));
    }

    /*
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
    */
}
