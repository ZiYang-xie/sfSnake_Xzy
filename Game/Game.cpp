#include <SFML/Graphics.hpp>

#include <memory>
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"

using namespace sfSnake;

//帧率设置
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

//静态变量
bool Game::bgState = true;
bool Game::isPause = false;

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()    //创建窗口和背景音乐
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
    bgmInit(); //初始化音乐
}

void Game::handleInput()
{
    bgmControl();
    pauseControl();
	sf::Event event;    //事件获取

	while (window_.pollEvent(event))    //关闭窗口处理
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)   //游戏刷新
{
    if(!isPause)
        Game::Screen->update(delta);
}

void Game::render() //游戏渲染
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
        while(isPause)  //暂停截断
        {
            pauseControl();
            sf::sleep(sf::microseconds(20));    //sleep以防cpu占用率过高
            clock.restart();
        }
        
        sf::Time delta = clock.restart();   //delta时钟重置
        timeSinceLastUpdate += delta;   //上次刷新时间+delta
        
        while (timeSinceLastUpdate > Game::TimePerFrame)    //当距上次更新时间超过每帧的间隔时间，更新
        {
            timeSinceLastUpdate -= TimePerFrame;
            handleInput();
            update(TimePerFrame);
        }
        render();
	}
}

//BGM初始化
void Game::bgmInit()
{
    bgMusic_.openFromFile("Resource/Music/bg_music.wav");    //设置背景音乐
    bgMusic_.setVolume(20);
    bgMusic_.setLoop(true); //设置音乐循环
    bgMusic_.play();    //播放音乐
}

//BGM控制
void Game::bgmControl()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        if(bgState){
            bgMusic_.pause();
            bgState = false;
            return;
        }
        else{
            bgMusic_.play();
            bgState = true;
        }
    }
}

//暂停控制
void Game::pauseControl()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        isPause = true;
        return;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        isPause = false;
        return;
    }
}
