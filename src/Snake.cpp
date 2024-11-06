#include "Snake.hpp"

const sf::Color Snake::backgroundColor = sf::Color::Black;
const sf::Color Snake::snakeSegmentColor = sf::Color::Red;
const sf::Color Snake::foodColor = sf::Color::Green;

Snake::Snake()
    : rng(std::chrono::system_clock::now().time_since_epoch().count()), xdist(0, cols - 1), ydist(0, rows - 1),
        snakeDirection(Direction::LEFT), snakeSegment(sf::Vector2f((float)segmentSize, (float)segmentSize)),
        food(sf::Vector2f((float)segmentSize, (float)segmentSize))
{
    snakeBody = {
        { cols / 2, rows / 2 }, 
        { (cols / 2 + 1) % cols, rows / 2 },
        { (cols / 2 + 2) % cols, rows / 2 },
        { (cols / 2 + 3) % cols, rows / 2 }
        };
    snakeHead = snakeBody.begin();
    snakeSegment.setFillColor(snakeSegmentColor);
    food.setFillColor(foodColor);
}

void Snake::createNewSnake()
{
    std::list<std::pair<int16_t, int16_t>>::iterator it1 = snakeHead;

    if(it1 == snakeBody.begin())
        it1 = snakeBody.end();
    --it1;

    std::list<std::pair<int16_t, int16_t>>::iterator it2 = it1;

    while (snakeBody.size() > 3)
    {
        if(it2 == snakeBody.begin())
            it2 = snakeBody.end();
        --it2;
        snakeBody.erase(it1);
        it1 = it2;
    }
}

Snake::~Snake()
{
    
}

void Snake::draw()
{
    window.clear(backgroundColor);

    for(auto& seg : snakeBody)
    {
        snakeSegment.setPosition(sf::Vector2f(segmentSize * seg.first, segmentSize * seg.second));
        window.draw(snakeSegment);
    }

    food.setPosition(sf::Vector2f(segmentSize * foodPos.first, segmentSize * foodPos.second));
    window.draw(food);

    window.display();
}

void Snake::run()
{
    window.create(sf::VideoMode(cols * segmentSize, rows * segmentSize), "Snake v1.0", sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(framerateLimit);

    while (window.isOpen())
    {
        clock.restart();

        Direction nextSnakeDirection = snakeDirection;

        while(clock.getElapsedTime().asMilliseconds() < delay)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Up)
                        nextSnakeDirection = Direction::UP;
                    else if(event.key.code == sf::Keyboard::Down)
                        nextSnakeDirection = Direction::DOWN;
                    else if(event.key.code == sf::Keyboard::Left)
                        nextSnakeDirection = Direction::LEFT;
                    else if(event.key.code == sf::Keyboard::Right)
                        nextSnakeDirection = Direction::RIGHT;
                }
            }
        }

        if( ((uint8_t)nextSnakeDirection + (uint8_t)snakeDirection) % 2 != 0)
            snakeDirection = nextSnakeDirection;
        
        move();
        
        draw();
    }
    
}

void Snake::move()
{
    std::pair<int16_t, int16_t> snakeHeadPos = *snakeHead;

    switch (snakeDirection)
    {
        case Direction::UP    : snakeHeadPos.second--; break;
        case Direction::DOWN  : snakeHeadPos.second++; break;
        case Direction::LEFT  : snakeHeadPos.first--; break;
        case Direction::RIGHT : snakeHeadPos.first++; break;
    }

    if(snakeHeadPos.first < 0)
        snakeHeadPos.first = cols - 1;
    else if(snakeHeadPos.first >= cols)
        snakeHeadPos.first = 0;
    else if(snakeHeadPos.second < 0)
        snakeHeadPos.second = rows - 1;
    else if(snakeHeadPos.second >= rows)
        snakeHeadPos.second = 0;

    if(foodPos.first == snakeHeadPos.first && foodPos.second == snakeHeadPos.second)
    {
        snakeBody.insert(snakeHead, snakeHeadPos);

        if(snakeHead == snakeBody.begin())
            snakeHead = snakeBody.end();
        --snakeHead;

        updateFoodPos();
    }
    else
    {
        if(snakeHead == snakeBody.begin())
            snakeHead = snakeBody.end();
        --snakeHead;
        
        *snakeHead = snakeHeadPos;

        if(checkCollision())
            createNewSnake();
    }
}

bool Snake::checkCollision()
{
    std::list<std::pair<int16_t, int16_t>>::iterator tmpIt = snakeHead;

    if(snakeHead != snakeBody.begin())
    {
        do
        {
            --tmpIt;
            if(*tmpIt == *snakeHead)
                return true;
        } while (tmpIt != snakeBody.begin());
        
    }

    if(snakeHead != --snakeBody.end())
    {
        tmpIt = snakeHead;
        ++tmpIt;

        while(tmpIt != snakeBody.end())
        {
            if(*tmpIt == *snakeHead)
                return true;
            ++tmpIt;
        }
    }

    return false;
}

void Snake::updateFoodPos()
{
    int16_t x;
    int16_t y;
    bool isFoodColliding;

    do
    {
        x = xdist(rng);
        y = ydist(rng);
        isFoodColliding = false;

        for(auto& seg : snakeBody)
            if(seg.first == x && seg.second == y)
            {
                isFoodColliding = true;
                break;
            }
        
    } while (isFoodColliding);
    
    foodPos.first = x;
    foodPos.second = y;
}