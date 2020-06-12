#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
    static const float Radius;
	SnakeNode(const sf::Vector2f& position = sf::Vector2f(0, 0));

	void setPosition(const sf::Vector2f& position);    //设置位置V2f
	void setPosition(const float& x,const float& y); //设置位置xy
    void setRotation(const float& angle);  //控制旋转

	const sf::Vector2f& getPosition() const;   //获取位置
	const sf::FloatRect getBounds() const;    //获取边界
    const float getRotation() const;    //获取旋转角
    
    void render(sf::RenderWindow& window);

private:
	sf::CircleShape shape_;
    sf::RectangleShape stripe_;
    
	sf::Vector2f position_;
};
}

#endif
