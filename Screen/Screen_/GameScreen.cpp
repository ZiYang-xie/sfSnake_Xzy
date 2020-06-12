#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
//#include <iostream>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "MathProcess.h"
#include "SettingScreen.h"

using namespace sfSnake;

GameScreen::GameScreen() :
fruitNum(15),
snake_(),
texture(ScreenType::GameScreen,SettingScreen::gridColor_),
musicIcon_(texture.getTex(TextType::MusicIconOn))
{
    initFruit(fruitNum);
    initText();
    initTexture();
    initGrid();
}

void GameScreen::handleInput(sf::RenderWindow& window)  //处理输入
{
	snake_.handleKeyBoardInput(window);
    snake_.handleMouseInput(window);
}

void GameScreen::update(sf::Time delta)
{
	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);    //水果碰撞
    setScore(); //设置分数
    Game::bgState ? musicIcon_.setTexture(texture.getTex(TextType::MusicIconOn)) : musicIcon_.setTexture(texture.getTex(TextType::MusicIconOff));
    
	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize()-snake_.getInitSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
    //背景色
    switch (SettingScreen::bgColor_) {
        case ColorType::White:
            window.clear(sf::Color(245, 245, 245));
            break;
        case ColorType::Black:
            window.clear(sf::Color(20, 20, 20));
            break;
        case ColorType::Brown:
            window.clear(sf::Color(170, 122, 75));
        default:
            break;
    }
    
    //背景格
    window.draw(gridSprite_);

	snake_.render(window);
    for (auto& fruit : fruit_)
        fruit.render(window);
    
    //实时分数
    window.draw(scoreBg_);
    window.draw(score_);
    //按键提示
    window.draw(musicBg_);
    window.draw(mKey);
    //音量Icon
    window.draw(musicIcon_);
}

/**-------------------------------------Init-Stage------------------------------------------------------**/

void GameScreen::initFruit(const unsigned short &fruitNum)
{
    fruit_.reserve(fruitNum);
    while (fruit_.size() < int(fruitNum*0.25)){
        fruit_.push_back(Fruit(9.f,sf::Color::Black,0,generateLocation())); //黑色水果
        fruit_.push_back(Fruit(9.f,sf::Color(67, 39, 21),0,generateLocation()));    //棕色水果
    }
    while (fruit_.size() < fruitNum) {
        fruit_.push_back(Fruit(6.f,sf::Color(255,71,87),3,generateLocation())); //红色水果
        fruit_.push_back(Fruit(7.f,sf::Color(2, 252, 254),2,generateLocation()));   //蓝色水果
        fruit_.push_back(Fruit(8.f,sf::Color(18, 243, 8),1,generateLocation()));    //绿色水果
    }
}

void GameScreen::initText()
{
    //加载中文字体
    font_.loadFromFile("Resource/Fonts/game_chinese.ttf");
    score_.setFont(font_);
    mKey.setFont(font_);
    //设置文字
    score_.setString((L"当前分数: ") +std::to_wstring(snake_.getSize()-snake_.getInitSize()) + L" 分");
    mKey.setString(L"M静音");
    //设置字体颜色
    score_.setFillColor(sf::Color::Black);
    mKey.setFillColor(sf::Color::Black);
    //设置字体位置
    score_.setPosition(40, 30);
    mKey.setPosition(Game::Width-120, 85);
    //设置分数背景框
    scoreBg_.setSize(sf::Vector2f(250,50));
    scoreBg_.setPosition(25, 23);
    scoreBg_.setFillColor(sf::Color(255,255,255,150));
    //设置音乐背景框
    musicBg_.setRadius(60);
    musicBg_.setPosition(Game::Width-132, 20);
    musicBg_.setFillColor(sf::Color(255,255,255,150));
}

void GameScreen::initTexture()
{
    musicIcon_.setPosition(Game::Width-100, 23);
    musicIcon_.setScale(0.3, 0.3);
}

void GameScreen::initGrid()
{
    if(SettingScreen::gridState_)
        gridSprite_.setTexture(texture.getTex(TextType::Grid));
}

//setScore
void GameScreen::setScore()
{
    score_.setString((L"当前分数: ") +std::to_wstring(snake_.getSize()-snake_.getInitSize()) + L" 分");
}


