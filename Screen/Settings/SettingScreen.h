#ifndef SettingScreen_h
#define SettingScreen_h

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "RadioBox.h"
#include "TextureManager.h"

namespace sfSnake
{
class SettingScreen : public Screen
{
public:
    SettingScreen();
    
    void handleKeyboardInput();
    void handleMouseInput(const sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    void initChoices();
    void setChoices();
    
    static bool gridState_; //网格状态静态变量
    static ColorType bgColor_;
    static ColorType gridColor_;
private:
    TextureManager texture; //材质管理器
    sf::Sprite bgImg;
    
    RadioBox grid_;
    std::vector<std::shared_ptr<RadioBox>> bgRadioVec_; //背景单选框*3
    std::vector<std::shared_ptr<RadioBox>> gridRadioVec_;   //网格单选框*3
};
}

#endif /* SettingScreen_h */
