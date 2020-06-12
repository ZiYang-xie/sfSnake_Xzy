#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "SnakeHead.h"
#include "SoundManager.h"
#include "Fruit.h"

namespace sfSnake
{

class Snake
{
public:
	Snake();
    //处理输入
	void handleKeyBoardInput(sf::Window&);
    void handleMouseInput(sf::Window&);
    
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	std::vector<Fruit>::iterator checkFruitCollisions(std::vector<Fruit>& fruits);

    //碰撞检测
	bool hitSelf() const;

    //获取长度
	const unsigned getSize() const;
    const unsigned getInitSize() const;

private:
    static const int InitialSize;   //初始化长度
    bool hitSelf_;  //碰撞检测
    
    void initNodes();   //初始化节点
    void setSoundBuffer();  //设置
    
    SnakeHead headNode;
    std::vector<SnakeNode> nodes_;
    
	void move();    //移动
    void headMove();    //头部移动
    void nodeMove();    //节点跟随
    
	void grow(const unsigned short& len);   //生长
    
	void checkEdgeCollisions(); //检测边缘
	void checkSelfCollisions(); //检测碰撞
	
    const sf::Vector2f getCursorPosition(sf::Window&);

    //状态
	sf::Vector2f position_; //位置
    sf::Vector2f direction_;    //方向
    float rotation_;    //旋转角
    
    //音效
    SoundManager audio;
    sf::Sound dieSound_,clickSound_,pickupSound_,warnSound_;
    
};
}

#endif
