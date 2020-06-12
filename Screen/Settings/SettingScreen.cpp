#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"
#include <iostream>

using namespace sfSnake;

//模板函数声明
template <typename T>
void initRadio(T& vec);  //初始化

template <typename T>
void radioSetting(T& vec,const float& height);   //单选框设置

template <typename T>
void checkRadio(T& vec,const sf::RenderWindow& window);     //单选条件判断

template <typename T>
const ColorType& getColor(T& vec);  //获取颜色

template <typename T>
const ColorType& SettingColor(T& vec,ColorType& color_);   //设置菜单颜色

//SettingState静态变量-(默认颜色)
bool SettingScreen::gridState_ = true;
ColorType SettingScreen::bgColor_ = ColorType::White;
ColorType SettingScreen::gridColor_ = ColorType::Black;

//默认构造函数
SettingScreen::SettingScreen():
texture(ScreenType::SettingScreen),
bgImg(texture.getTex(TextType::SettingBg))
{
    initChoices();
    setChoices();
}

//处理键盘输入
void SettingScreen::handleKeyboardInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        Game::Screen = std::make_shared<MenuScreen>();
}

//处理鼠标输入
void SettingScreen::handleMouseInput(const sf::RenderWindow& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(grid_.getBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                grid_.switchState();
        
        //判断单选条件
        checkRadio(bgRadioVec_,window);
        checkRadio(gridRadioVec_, window);
    }
}

//处理输入
void SettingScreen::handleInput(sf::RenderWindow& window)
{
    handleKeyboardInput();
    handleMouseInput(window);
}

void SettingScreen::update(sf::Time delta)
{
    //更新网格的状态
    gridState_ = grid_.getState();
    bgColor_ = getColor(bgRadioVec_);
    gridColor_ = getColor(gridRadioVec_);
}

//渲染
void SettingScreen::render(sf ::RenderWindow& window)
{
    window.draw(bgImg);
    grid_.render(window);
    
    for(const auto& bgRadioBox : bgRadioVec_)
        bgRadioBox->render(window);
    for(const auto& gridRadioBox : gridRadioVec_)
        gridRadioBox->render(window);
}

/**------------------------------------init-RadioBox-------------------------------------------**/

//初始化单选框
void SettingScreen::initChoices()
{
    //初始化单选框
    initRadio(bgRadioVec_);
    initRadio(gridRadioVec_);
}

//设置单选框样式
void SettingScreen::setChoices()
{
    //设置单选框位置大小
    radioSetting(bgRadioVec_,Game::Height-550);
    radioSetting(gridRadioVec_,Game::Height-370);
    
    // 初始样式 initial styleSheet-(不知道为什么用不了模板函数，对应189行)
    switch (bgColor_)
    {
        case ColorType::White:
            bgRadioVec_[0]->setState(true);
            break;
        case ColorType::Black:
            bgRadioVec_[1]->setState(true);
            break;
        case ColorType::Brown:
            bgRadioVec_[2]->setState(true);
        default:
            break;
    }
    
    switch (gridColor_)
    {
        case ColorType::White:
            gridRadioVec_[0]->setState(true);
            break;
        case ColorType::Black:
            gridRadioVec_[1]->setState(true);
            break;
        case ColorType::Brown:
            gridRadioVec_[2]->setState(true);
        default:
            break;
    }
    
    grid_.setRecTexture(200, 200);
    grid_.setPosition(Game::Width-580, Game::Height-232);
    grid_.setScale(0.3, 0.3);
    grid_.setState(gridState_);
}

/**-----------------------------------模板函数-----------------------------------------------**/

template <typename T>
void initRadio(T& vec)
{
    vec.push_back(std::make_shared<RadioBox>(ColorType::White));
    vec.push_back(std::make_shared<RadioBox>(ColorType::Black));
    vec.push_back(std::make_shared<RadioBox>(ColorType::Brown));
}

template <typename T>
void radioSetting(T& vec,const float& height)
{
    for(short i = 0; i < vec.size(); ++i)
    {
        vec[i]->setRecTexture(200, 200);
        vec[i]->setScale(0.3, 0.3);
        vec[i]->setPosition(Game::Width-582+(162*i), height);
        vec[i]->setState(false);
    }
}

template <typename T>
void checkRadio(T& vec,const sf::RenderWindow& window)
{
    std::shared_ptr<RadioBox> toRemove;
    bool flag = false;
    for(auto ptr : vec)
    {
        if(ptr->getState())
            toRemove = ptr;
        if(ptr->getBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y) && toRemove!=ptr){
               ptr->setState(true);
            flag = true;
            }
    }
    if(flag)
    {
        toRemove->setState(false);
    }
}

template <typename T>
const ColorType& getColor(T& vec)
{
    for(const auto& ptr : vec){
        if(ptr->getState())
            return ptr->getColor();
    }
}

//模板函数无法使用问题-对应103行
template <typename T>
const ColorType& SettingColor(T& vec,ColorType& color_)
{
    switch (color_)
    {
        case ColorType::White:
            vec[0]->setState(true);
            break;
        case ColorType::Black:
            vec[1]->setState(true);
            break;
        case ColorType::Brown:
            vec[2]->setState(true);
        default:
            break;
    }
}

