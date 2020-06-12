#include "MathProcess.h"

const float rad(const float& degree)
{
    return pi*degree/180;
}

const float deg(const float& rad)
{
    return 180*rad/pi;
}

const float getAngle(const sf::Vector2f& a, const sf::Vector2f& b)
{
    auto lenA = sqrt(pow(a.x, 2)+pow(a.y, 2));
    auto lenB = sqrt(pow(b.x, 2)+pow(b.y, 2));
    return acos((a.x*b.x+a.y*b.y)/(lenA*lenB));
}

const sf::Vector2f generateLocation()
{
    static std::default_random_engine engine(time(NULL));
    static std::uniform_int_distribution<int> xDistribution(0, sfSnake::Game::Width - 2*sfSnake::SnakeNode::Radius);
    static std::uniform_int_distribution<int> yDistribution(0, sfSnake::Game::Height - 2*sfSnake::SnakeNode::Radius);
    return sf::Vector2f(xDistribution(engine), yDistribution(engine));
}
