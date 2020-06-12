#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "TextureManager.h"


namespace sfSnake
{
class GameScreen : public Screen    //游戏屏幕
{
public:
    GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
    
	void initFruit(const unsigned short&);  //初始化水果
    void initText();    //初始化字体
    void initTexture(); //初始化素材
    void initGrid();    //初始化网格
    
    void setScore();
    
    TextureManager texture; //纹理管理器
private:
    Snake snake_;
    
    const unsigned short fruitNum;
    std::vector<Fruit> fruit_;
    
    //网格和音乐图标素材
    sf::Sprite gridSprite_;
    sf::Sprite musicIcon_;

    sf::Font font_; //外部字体
    
    sf::Text score_;
    sf::RectangleShape scoreBg_;
    sf::Text mKey;
    sf::CircleShape musicBg_;
    
    
};
}

#endif
