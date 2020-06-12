#ifndef TextureManager_h
#define TextureManager_h

#include <SFML/Graphics.hpp>
#include "ReasourceHolder.h"

namespace sfSnake
{
enum class ColorType
{
    White,Black,Brown
};
enum class TextType
{
    Grid,MenuBg,SettingBg,GameOverBg,SnakeHead,MusicIconOn,MusicIconOff,RadioOn,RadioOff,Radio
};
enum class ScreenType
{
    MenuScreen,SettingScreen,GameScreen,GameOverScreen
};
class TextureManager
{
public:
    TextureManager();
    TextureManager(const TextType&);
    TextureManager(const ScreenType&,const ColorType& = ColorType::Black); //按屏幕初始化素材,可指定网格颜色,默认黑色
    const sf::Texture& getTex(TextType);

    void ColorSwitch_(const ColorType&);
private:
    ScreenType screenType_;
    ColorType gridColor_;
    ResourceHolder<sf::Texture, TextType> mTextureHolder;
};
}

#endif /* TextureManager_h */
