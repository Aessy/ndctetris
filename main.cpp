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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

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

        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        tickGame(game, player);
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
