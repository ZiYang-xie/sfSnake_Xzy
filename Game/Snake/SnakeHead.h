#ifndef SnakeHead_h
#define SnakeHead_h

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace sfSnake
{
class SnakeHead
{
public:
    static const float Radius;  //半径静态变量
    
    SnakeHead(const sf::Vector2f& position = sf::Vector2f(0, 0));

    void setPosition(const sf::Vector2f& position);    //设置位置V2f
    void setPosition(const float& x, const float& y); //设置位置xy
    void setRotation(const float& angle);  //控制旋转
    void setTexture(const sf::Texture&);  //设置纹理
    
    const sf::Vector2f getPosition() const;   //获取位置
    const sf::FloatRect getBounds() const;    //获取边界
    const float getRotation() const;    //获取旋转角
    
    void move(const float& xOffset,const float& yOffset);
    void rotate(const float&);

    void render(sf::RenderWindow& window);


    TextureManager texture; //素材资源管理器
private:
    sf::Sprite headNode_;
    sf::Vector2f position_;
};
}


#endif /* SnakeHead_h */
