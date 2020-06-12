#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "MathProcess.h"
#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "GameOverScreen.h"

using namespace sfSnake;
int count=0;

const int Snake::InitialSize = 5;   //初始化长度5节

Snake::Snake() : direction_(sf::Vector2f(0,-1)), hitSelf_(false)
{
	initNodes();
    setSoundBuffer();
}

/**----------------------Handle-Input----------------------**/

void Snake::handleKeyBoardInput(sf::Window& window)   //输入处理
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && deg(getAngle(direction_, sf::Vector2f(0,1)))>=90)
        direction_ = sf::Vector2f(0,-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && deg(getAngle(direction_, sf::Vector2f(0,-1)))>=90)
        direction_ = sf::Vector2f(0,1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && deg(getAngle(direction_, sf::Vector2f(1,0)))>=90)
        direction_ = sf::Vector2f(-1,0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && deg(getAngle(direction_, sf::Vector2f(-1,0)))>=90)
        direction_ = sf::Vector2f(1,0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void Snake::handleMouseInput(sf::Window& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(deg(getAngle(direction_, getCursorPosition(window) - nodes_[0].getPosition())) <= 90) //禁止反向移动
        {
            clickSound_.play();
            direction_ = getCursorPosition(window) - nodes_[0].getPosition();
        }
        else{
            warnSound_.play();
        }
    }
}

const sf::Vector2f Snake::getCursorPosition(sf::Window& window)
{
    return sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::render(sf::RenderWindow& window)
{
    headNode.render(window);
    for (auto& node : nodes_)
        node.render(window);
}

/**----------------------Init-Stage----------------------**/

void Snake::initNodes()
{
    //inital headNode
    headNode.setPosition(sf::Vector2f(Game::Width / 2 - SnakeNode::Radius,
    Game::Height / 2 - SnakeNode::Radius));
    //inital bodyNode
    for (int i = 0; i < Snake::InitialSize; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(
            Game::Width / 2 - SnakeNode::Radius,
            Game::Height / 2 - SnakeNode::Radius + (2*SnakeNode::Radius * i))));
    }
}

void Snake::setSoundBuffer()
{
    dieSound_.setBuffer(audio.mSoundHolder.get(SoundType::die));
    pickupSound_.setBuffer(audio.mSoundHolder.get(SoundType::pickup));
    clickSound_.setBuffer(audio.mSoundHolder.get(SoundType::click));
    warnSound_.setBuffer(audio.mSoundHolder.get(SoundType::warn));
}

/**----------------------Move & Grow----------------------**/

void Snake::move()
{
    nodeMove();
    headMove();
}

void Snake::headMove()
{
    //方向移动控制
    auto directionLen = sqrt(pow(direction_.x,2)+pow(direction_.y,2));
    auto moveDirection = sf::Vector2f( (direction_.x/directionLen),(direction_.y/directionLen));
    //头部移动
    headNode.move(2*SnakeNode::Radius*moveDirection.x,2*SnakeNode::Radius*moveDirection.y);
    //头部旋转
    if(moveDirection.x>0)
        headNode.setRotation(deg(acos(-moveDirection.y)));
    else
        headNode.setRotation(-deg(acos(-moveDirection.y)));
}

void Snake::nodeMove()
{
    nodes_.at(0).setPosition(headNode.getPosition());
    nodes_.at(0).setRotation(headNode.getRotation());
    for (decltype(nodes_.size()) i = nodes_.size()-1; i > 0 ; --i)
    {
        nodes_.at(i).setPosition(nodes_.at(i-1).getPosition());
        if(nodes_.at(i).getRotation()!=nodes_.at(i-1).getRotation())
            nodes_.at(i).setRotation(nodes_.at(i-1).getRotation());
    }
}

void Snake::grow(const unsigned short& len)
{
    //蛇尾最初生长时重叠在一起，随着蛇的移动慢慢生长，从而防止出现蛇头被突然生长出来的蛇尾撞死的情况
    for(auto i=len;i>0;--i){
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
                nodes_[nodes_.size() - 1].getPosition().y)));
    }
}

/**----------------------------CheckCollisions----------------------------**/

std::vector<Fruit>::iterator Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
        if (it->getBounds().intersects(nodes_[0].getBounds())){
			toRemove = it;
            //collide!
            grow(toRemove->getBonus());
            pickupSound_.play();
            toRemove->setPosition(generateLocation());
        }
	}
    return toRemove;
}

void Snake::checkEdgeCollisions()
{
    if (headNode.getPosition().x <= -SnakeNode::Radius)   //左侧溢出
        headNode.setPosition(Game::Width-SnakeNode::Radius, headNode.getPosition().y);
    else if (headNode.getPosition().x >= Game::Width)    //右侧溢出
        headNode.setPosition(0, headNode.getPosition().y);
    else if (headNode.getPosition().y <= -SnakeNode::Radius)  //上侧溢出
        headNode.setPosition(headNode.getPosition().x, Game::Height-SnakeNode::Radius);
    else if (headNode.getPosition().y >= Game::Height)  //下侧溢出
        headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::checkSelfCollisions()
{
    for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
    {
        if (headNode.getBounds().intersects(nodes_[i].getBounds()))
        {
            dieSound_.play();
            sf::sleep(sf::seconds(audio.mSoundHolder.get(SoundType::die).getDuration().asSeconds()));
            hitSelf_ = true;
            return;
        }
    }
}

bool Snake::hitSelf() const
{
    return hitSelf_;
}

/**--------------------getSize---------------------------*/

const unsigned Snake::getSize() const
{
	return nodes_.size();
}

const unsigned Snake::getInitSize() const
{
    return InitialSize;
}






