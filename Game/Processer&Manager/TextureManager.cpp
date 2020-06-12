#include "TextureManager.h"
using namespace sfSnake;

//默认初始化
TextureManager::TextureManager()
{}

//按单素材初始化
TextureManager::TextureManager(const TextType& Ttype_)
{
    switch (Ttype_) {
        //加载蛇头
        case TextType::SnakeHead:
            mTextureHolder.load(TextType::SnakeHead, "./Resource/Img/snake_head.png");
            break;
        //加载单选框
        case TextType::Radio:
            mTextureHolder.load(TextType::RadioOn,"./Resource/Img/radio_on.png");
            mTextureHolder.load(TextType::RadioOff,"./Resource/Img/radio_off.png");
            break;
        default:
            break;
    }
}

//界面素材初始化
TextureManager::TextureManager(const ScreenType& screenType, const ColorType& color_)
:screenType_(screenType),
gridColor_(color_)
{
    switch (screenType_)
    {
        case ScreenType::MenuScreen:
            mTextureHolder.load(TextType::MenuBg, "./Resource/Background/menu_background.png");
            break;
        case ScreenType::SettingScreen:
            mTextureHolder.load(TextType::SettingBg, "./Resource/Background/setting_background.png");
            break;
        case ScreenType::GameScreen:
            mTextureHolder.load(TextType::MusicIconOn, "./Resource/Img/music_on.png");
            mTextureHolder.load(TextType::MusicIconOff,"./Resource/Img/music_off.png");
            ColorSwitch_(color_);
            break;
        case ScreenType::GameOverScreen:
            mTextureHolder.load(TextType::GameOverBg, "./Resource/Background/gameOver_background.png");
        default:
            break;
    }
}

//网格颜色设置
void TextureManager::ColorSwitch_(const ColorType& color_)
{
    switch (color_) {
        case ColorType::White:
            mTextureHolder.load(TextType::Grid, "./Resource/Grid/grid_white.png");
            break;
        case ColorType::Black:
            mTextureHolder.load(TextType::Grid, "./Resource/Grid/grid_black.png");
            break;
        case ColorType::Brown:
            mTextureHolder.load(TextType::Grid, "./Resource/Grid/grid_brown.png");
            break;
        default:
            break;
    }
}

const sf::Texture& TextureManager::getTex(TextType textType)
{
    return mTextureHolder.get(textType);
}



