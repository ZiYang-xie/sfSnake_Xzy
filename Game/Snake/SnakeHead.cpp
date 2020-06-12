#include <SFML/Graphics.hpp>

#include "SnakeHead.h"
using namespace sfSnake;

const float SnakeHead::Radius = 15.f;

SnakeHead::SnakeHead(const sf::Vector2f& position)
:
texture(TextType::SnakeHead),
position_(position)
{
    headNode_.setPosition(position_);
    headNode_.setTextureRect(sf::IntRect(0,0,2*SnakeHead::Radius,2*SnakeHead::Radius));
    headNode_.setOrigin(SnakeHead::Radius, SnakeHead::Radius);
}

void SnakeHead::setPosition(const sf::Vector2f& position)
{
    position_ = position;
    headNode_.setPosition(position_);
}

void SnakeHead::setPosition(const float& x, const float& y)
{
    position_.x = x;
    position_.y = y;
    headNode_.setPosition(position_);
}

void SnakeHead::setRotation(const float& angle)
{
    headNode_.setRotation(angle);
}

void SnakeHead::setTexture(const sf::Texture& texture)
{
    headNode_.setTexture(texture);
}

const sf::Vector2f SnakeHead::getPosition() const
{
    return position_;
}

const sf::FloatRect SnakeHead::getBounds() const
{
    return headNode_.getGlobalBounds();
}

const float SnakeHead::getRotation() const
{
    return headNode_.getRotation();
}

void SnakeHead::move(const float& xOffset, const float& yOffset)
{
    position_.x += xOffset;
    position_.y += yOffset;
    headNode_.setPosition(position_);
}

void SnakeHead::rotate(const float& angle)
{
    headNode_.rotate(angle);
}

void SnakeHead::render(sf::RenderWindow& window)
{
    headNode_.setTexture(texture.getTex(TextType::SnakeHead));
    window.draw(headNode_);
}
