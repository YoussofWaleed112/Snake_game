#include "..\header_files\Snake.hpp"
#include "..\header_files\Texture.hpp"
#include "..\header_files\Game.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


Snake::Snake() : snakeBody(std::list<sf::Sprite>(3))
{
    headSegment = --snakeBody.end();
    tailSegment = snakeBody.begin();
}

Snake::~Snake()
{}

void Snake::initSnake(const sf::Texture& texture)
{
    int x = 400, y = 300;

    for (auto& segment : snakeBody)
    {
        segment.setTexture(texture);
        segment.setPosition(x, y);

        x -= 38; // FIX 2: removed "y -= 38", body was diagonal instead of horizontal
    }
}


void Snake::move(sf::Vector2f direction)
{
    // FIX 3: correct circular buffer — advance tailSegment BEFORE reassigning headSegment
    sf::Vector2f newHeadPos = headSegment->getPosition() + direction;

    auto newHead = tailSegment;

    ++tailSegment;
    if (tailSegment == snakeBody.end())
    {
        tailSegment = snakeBody.begin();
    }

    newHead->setPosition(newHeadPos);
    headSegment = newHead;
}


void Snake::growSnake(sf::Vector2f direction)
{
    sf::Sprite newSegment;
    newSegment.setTexture(*(headSegment->getTexture()));
    newSegment.setPosition(headSegment->getPosition() + direction);

    headSegment = snakeBody.insert(snakeBody.end(), newSegment);
}


bool Snake::isOn(sf::Sprite& sprite) const
{
    return sprite.getGlobalBounds().intersects(headSegment->getGlobalBounds());
}


void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& piece : snakeBody)
    {
        target.draw(piece);
    }
}