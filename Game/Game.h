#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include <memory>

#include "Screen.h"

namespace sfSnake
{

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

    void bgmControl();
    void bgmInit();
    
    static bool bgState;
    static bool isPause;
    
    void pauseControl();
    //设置屏幕高度
	static const int Width = 1600;
	static const int Height = 900;

	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	
	static const sf::Time TimePerFrame;
};
}


#endif
