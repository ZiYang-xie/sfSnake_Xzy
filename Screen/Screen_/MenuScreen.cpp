#include <SFML/Graphics.hpp>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen():
texture(ScreenType::MenuScreen),
bgImg(texture.getTex(TextType::MenuBg))
{}

//处理输入
void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        Game::Screen = std::make_shared<SettingScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;
}

void MenuScreen::render(sf::RenderWindow& window)
{
    window.draw(bgImg);
}
