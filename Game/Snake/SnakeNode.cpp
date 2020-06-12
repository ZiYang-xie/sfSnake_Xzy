#include <SFML/Graphics.hpp>

#include "SnakeNode.h"
#include <math.h>

using namespace sfSnake;

const float SnakeNode::Radius = 15.f;

SnakeNode::SnakeNode(const sf::Vector2f& position)
: position_(position)
{
    //身体节点
    shape_.setPosition(position_);
    shape_.setRadius(SnakeNode::Radius);
    shape_.setFillColor(sf::Color(126,229,70));
    shape_.setOutlineThickness(-2.f);
    shape_.setOutlineColor(sf::Color(106,176,76));
    shape_.setOrigin(SnakeNode::Radius, SnakeNode::Radius);
    //条纹
    stripe_.setPosition(position_);
    stripe_.setSize(sf::Vector2f(2*SnakeNode::Radius-5,(SnakeNode::Radius-2.5)/2));
    stripe_.setFillColor(sf::Color::Black);
    stripe_.setOrigin(SnakeNode::Radius-2.5, (SnakeNode::Radius-2.5)/5);
}

void SnakeNode::setPosition(const sf::Vector2f& position)
{
	position_ = position;
    shape_.setPosition(position);
    stripe_.setPosition(position);
}

void SnakeNode::setPosition(const float& x, const float& y)
{
	position_.x = x;
	position_.y = y;
    shape_.setPosition(position_);
    stripe_.setPosition(position_);
}

void SnakeNode::setRotation(const float& angle)
{
    //shape_.setRotation(angle);
    stripe_.setRotation(angle);
}

const sf::Vector2f& SnakeNode::getPosition() const
{
    return position_;
}

const sf::FloatRect SnakeNode::getBounds() const
{
    return shape_.getGlobalBounds();
}

const float SnakeNode::getRotation() const
{
    return stripe_.getRotation();
}

void SnakeNode::render(sf::RenderWindow& window)
{
    window.draw(shape_);
    window.draw(stripe_);
}
