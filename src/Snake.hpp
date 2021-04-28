#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <chrono>
#include <iostream>

class Snake
{
public:
    static const int cols = 25;
    static const int rows = 25;    
    static const int segmentSize = 20;

    static const int framerateLimit = 60;

    static const sf::Color backgroundColor;
    static const sf::Color segmentColor;

private:

    enum class Direction : uint8_t
    {
        TOP = 0,
        RIGHT = 1,
        BOTTOM = 2,
        LEFT = 3
    };

    std::list<std::pair<uint16_t, uint16_t>> snakeBody;
    std::list<std::pair<uint16_t, uint16_t>>::iterator snakeHead;
    Direction snakeDirection;

    std::pair<uint16_t, uint16_t> foodPos;

    sf::RenderWindow window;
	sf::RectangleShape snakeSegment;
	sf::Event event;

    std::mt19937 rng;
    std::uniform_int_distribution<uint16_t> xdist;
    std::uniform_int_distribution<uint16_t> ydist;
public:
    Snake();
    ~Snake();

    void run();
private:
    void draw();

    void createNewSnake();
    void move();
};