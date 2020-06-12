#include <SFML/Graphics.hpp>

#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "SettingScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score):
score_(score),
texture(ScreenType::GameOverScreen)
{
    initText();
    initBg();
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        Game::Screen = std::make_shared<SettingScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
    //背景
    window.draw(bgImg);
    //字体
	window.draw(text_);
}

void GameOverScreen::initText()
{
    font_.loadFromFile("./Resource/Fonts/game_chinese.ttf");
    text_.setFont(font_);
    text_.setString((L"你的分数为: ") +std::to_wstring(score_) + L" 分");
    text_.setFillColor(sf::Color(238, 82, 83));

    text_.setPosition(Game::Width / 2 -220, Game::Height / 2 -120);
    text_.setCharacterSize(60);
}

void GameOverScreen::initBg()
{
    bgImg.setTexture(texture.getTex(TextType::GameOverBg));
}
