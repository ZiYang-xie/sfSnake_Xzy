#ifndef RadioBox_h
#define RadioBox_h

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

namespace sfSnake
{
//单选框类
class RadioBox
{
public:
    RadioBox();
    RadioBox(const ColorType&);
    
    //setter & getter
    void setPosition(const float& x, const float& y);   //设置位置
    void setScale(const float& x, const float& y);  //设置缩放比例
    void setState(const bool flag); //设置选中状态
    void setRecTexture(const float& x, const float& y); //设置边界大小
    
    const bool& getState() const;  //获得状态
    const ColorType& getColor() const; //获得颜色
    const sf::FloatRect getBounds();    //获得边界
    
    void switchState(); //切换状态
    
    void render(sf::RenderWindow& window);
    TextureManager texture; //素材资源管理器
private:
    bool state_;
    ColorType color_;
    sf::Sprite radio_;
};
}

#endif /* RadioBox_h */
