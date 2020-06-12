#include "RadioBox.h"

using namespace sfSnake;

RadioBox::RadioBox():
texture(TextType::Radio),
radio_(texture.getTex(TextType::RadioOff)),
state_(false)
{}

RadioBox::RadioBox(const ColorType& color):
texture(TextType::Radio),
color_(color)
{}

void RadioBox::setPosition(const float &x, const float &y)
{
    radio_.setPosition(x, y);
}

void RadioBox::setScale(const float& x, const float& y)
{
    radio_.setScale(x, y);
}

void RadioBox::setRecTexture(const float &x, const float &y)
{
    radio_.setTextureRect(sf::IntRect(0,0,x,y));
}

void RadioBox::setState(const bool flag)
{
    flag ? radio_.setTexture(texture.getTex(TextType::RadioOn)) : radio_.setTexture(texture.getTex(TextType::RadioOff));
    state_ = flag;
}

const bool& RadioBox::getState() const
{
    return state_;
}

const ColorType& RadioBox::getColor() const
{
    return color_;
}

const sf::FloatRect RadioBox::getBounds()
{
    return radio_.getGlobalBounds();
}

void RadioBox::switchState()
{
    state_ ? radio_.setTexture(texture.getTex(TextType::RadioOff)) : radio_.setTexture(texture.getTex(TextType::RadioOn));
    state_ = !state_;
}

void RadioBox::render(sf::RenderWindow &window)
{
    window.draw(radio_);
}
