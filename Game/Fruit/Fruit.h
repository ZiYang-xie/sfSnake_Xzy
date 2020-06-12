#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
    Fruit(const float& radius_ = 0.f, const sf::Color& Color = sf::Color::White,const unsigned short& Bonus = 0,const sf::Vector2f& position_ = sf::Vector2f(0, 0));  //初始化构造函数
    
    void setPosition(const sf::Vector2f&); //设置位置
    void setRadius(const float&); //设置半径大小
    void setColor(const sf::Color&); //设置颜色
    //void setBonus(const unsigned short&); //设置分数
    
    const sf::Color& getColor();    //获取颜色
    const unsigned short& getBonus();   //获取分数(即增长长度)
    sf::FloatRect getBounds() const;
    
    void render(sf::RenderWindow& window);
    
private:
    sf::CircleShape shape_;
    const unsigned short bonus_;
};
}

#endif
