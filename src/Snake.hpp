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
    static const int delay = 120;

    static const sf::Color backgroundColor;
    static const sf::Color snakeSegmentColor;
    static const sf::Color foodColor;

private:

    enum class Direction : uint8_t
    {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };

    std::list<std::pair<int16_t, int16_t>> snakeBody;
    std::list<std::pair<int16_t, int16_t>>::iterator snakeHead;
    Direction snakeDirection;

    std::pair<int16_t, int16_t> foodPos;

    sf::RenderWindow window;
	sf::RectangleShape snakeSegment;
	sf::RectangleShape food;
	sf::Event event;
    sf::Clock clock;

    std::mt19937 rng;
    std::uniform_int_distribution<int16_t> xdist;
    std::uniform_int_distribution<int16_t> ydist;
public:
    Snake();
    ~Snake();

    void run();
private:
    void draw();

    void createNewSnake();
    void move();

    bool checkCollision();
    void updateFoodPos();
};