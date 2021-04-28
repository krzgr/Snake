#include "Snake.hpp"

const sf::Color Snake::backgroundColor = sf::Color::Black;
const sf::Color Snake::segmentColor = sf::Color::Red;

Snake::Snake()
    : rng(std::chrono::system_clock::now().time_since_epoch().count()), xdist(0, cols - 1), ydist(0, rows - 1),
        snakeDirection(Direction::LEFT), snakeSegment(sf::Vector2f((float)segmentSize, (float)segmentSize))
{
    snakeSegment.setFillColor(segmentColor);
    createNewSnake();
}

void Snake::createNewSnake()
{

}

Snake::~Snake()
{
    
}

void Snake::draw()
{
    window.clear(backgroundColor);

    window.display();
}

void Snake::run()
{
    window.create(sf::VideoMode(cols * segmentSize, rows * segmentSize), "Snake v1.0", sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(framerateLimit);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        draw();
    }
    
}