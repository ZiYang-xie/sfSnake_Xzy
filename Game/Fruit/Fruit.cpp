#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

Fruit::Fruit(const float& radius_, const sf::Color& color_, const unsigned short& Bonus,const sf::Vector2f& position_):bonus_(Bonus)
{
	shape_.setPosition(position_);
    shape_.setRadius(radius_);
    shape_.setFillColor(color_);
}

void Fruit::setPosition(const sf::Vector2f& position_)
{
    shape_.setPosition(position_);
}

void Fruit::setRadius(const float& radius_)
{
    shape_.setRadius(radius_);
}

void Fruit::setColor(const sf::Color& color_)
{
    shape_.setFillColor(color_);
}

const sf::Color& Fruit::getColor()
{
    return shape_.getFillColor();
}

const unsigned short& Fruit::getBonus()
{
    return bonus_;
}

sf::FloatRect Fruit::getBounds() const
{
    return shape_.getGlobalBounds();
}


void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}



