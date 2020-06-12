# 贪吃蛇小游戏 / SfSnake
#### 源码出自：https://github.com/jhpy1024/sfSnake.git
![版本号](https://img.shields.io/badge/Version-ALpha--0.0.1-blue) ![作者](https://img.shields.io/badge/Author-Xzy-orange)  
#### ( 注：本md仅包含代码与性能分析，游戏与功能介绍请移步readme.md )

---
## 特点简介
_1.贪吃蛇的操作 :_
* 相比源代码，对于贪吃蛇的操作在满足需求的基础上，保证了其不会有因为反向移动而造成的死亡，且在鼠标和键盘操作的切换上较为流畅，保证了不会有穿越身体突然死亡的bug产生，确保贪吃蛇单次旋转角度不大于90° (鼠标点击时还会有禁止音效)。

* 对于自身碰撞，由于前两节身体不可能被自己撞到，碰撞检测由第三节身体开始检测，

_2.资源管理 :_
   * 在资源管理上我的项目较为有特点，通过类型进行统一的资源管理，将所有的资源路径整合到TextureManager和SoundManager中，增强了可扩展性，降低了维护难度。

   * 通过ReasourceHolder将资源统一储存在Map中，防止了重复读取，二次读取直接从cache中载入，提高了资源管理的有效性和合理性。

   * 在TextureManager中通过初始化的参数可以指定需要加载的界面以及指定网格颜色素材，或是直接从单一素材载入，提供了素材载入的精确度，防止重复载入，提高了内存利用率。

_3.水果的实现 :_
#### 一些思考：
* 对于不同水果颜色的实现，实际上有两种思路，一种是写一个Fruit基类，在下面设置不同颜色的衍生类，另一种是只使用一个Fruit类，通过API进行灵活的设置管理。

* 衡量之后我选择了后者
  
> 从可扩展性上来说，其实二者差不多，第一种方法的主要优势是其可读性强，但其基类要设置虚函数，必然会造成更多的内存开支，并且因为不同颜色的水果为其不同的衍生类，因而只能将其指针插入Vector中不便管理，容易出错。

* 而仅用一个Fruit类的优势则比较明显，通过大量的getter和setter函数可以轻松的管理设置水果类型，通过不同的初始化参数可以达成不同的水果样式的需求。且可以一致塞入一个vector中易于管理。
#### 水果的刷新：
* 对于水果的刷新，相比于源代码的直接删除节点，我使用了通过将水果移位的方式来进行水果吃掉后的刷新机制。通过再次生成位置，并将其重新渲染在屏幕上，节省了开支，提高了速度。

_4.设置界面的实现 :_
* 在原来的界面中，我添加了一个设置界面。其中除了介绍按键功能以外，其中有7个可以交互的选框，来设置游戏的样式。

<img src="https://s1.ax1x.com/2020/06/12/tOVOI0.png" />

* 其中背景和网格处的选框为单选框，有且只有一个风格被选中。

_5.内存管理和运行效益 :_
* 相比于源码，我将源码中多处传值方式改为const &类型，最大程度上优化了运行效率和内存使用。

_6.精美的美工 :_
* 其中所有的素材美工，以及蛇头的像素画都是由我通过PS制作而得，界面精美好看，比源代码的游戏提升不少。

_7.一些不足 :_
* 有一些不足之处，例如对游戏并没有做进一步的多线程处理，从而导致cpu占用率普遍偏高，这是后续可以改进的点。

* 类和类之间的关系较为复杂，日后可以进行简化。

* 在资源素材的管理上仍然还可以进一步优化。


---


## 代码分析

<img src="https://s1.ax1x.com/2020/06/12/tOohAP.png"/>

---
### 一、Game部分
* Game类

Game.cpp/h
#### 增加了bgm控制和暂停控制功能
#### 由bgState和isPause两个静态变量控制
```c++
    static bool bgState;
    static bool isPause;
```

* BGM控制
```c++
//BGM初始化
void Game::bgmInit()
{
    bgMusic_.openFromFile("Music/bg_music.wav");    //设置背景音乐
    bgMusic_.setVolume(20);
    bgMusic_.setLoop(true); //设置音乐循环
    bgMusic_.play();    //播放音乐
}

//BGM控制
void Game::bgmControl()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) //按 M 静音
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
```

*暂停控制
```c++
//暂停控制
void Game::pauseControl()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){    //按P暂停
        isPause = true;
        return;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){   //按Q恢复
        isPause = false;
        return;
    }
}
```
---

### Snake主体

#### Snake主体包含Snake.cpp/h，SnakeHead.cpp/h，SnakeNode.cpp/h三部分

* 1、SnakeHead类

SnakeHead.h
```c++
//主体部分
class SnakeHead
{
public:
    static const float Radius;  //半径静态变量
    
    SnakeHead(const sf::Vector2f& position = sf::Vector2f(0, 0));

    void setPosition(const sf::Vector2f& position);    //设置位置V2f
    void setPosition(const float& x, const float& y); //设置位置xy
    void setRotation(const float& angle);  //控制旋转
    void setTexture(const sf::Texture&);  //设置纹理
    

    void move(const float& xOffset,const float& yOffset);   //移动
    void rotate(const float&);  //旋转

    void render(sf::RenderWindow& window);

    const sf::Vector2f getPosition() const;   //获取位置
    const sf::FloatRect getBounds() const;    //获取边界
    const float getRotation() const;    //获取旋转角

    TextureManager texture; //素材资源管理器
private:
    sf::Sprite headNode_;
    sf::Vector2f position_;
};
```

> 通过一个SnakeHead来作为蛇头结点，其中设置了许多getter&setter方法，来为其设定获取位置、旋转角度、材质、边界，并有move和rotate方法来控制头结点的移动和旋转。

* 2、SnakeNode类

SnakeNode.h
```c++
//主体部分
class SnakeNode
{
public:
    static const float Radius;
	SnakeNode(const sf::Vector2f& position = sf::Vector2f(0, 0));

	void setPosition(const sf::Vector2f& position);    //设置位置V2f
	void setPosition(const float& x,const float& y); //设置位置xy
    void setRotation(const float& angle);  //控制旋转

	const sf::Vector2f& getPosition() const;   //获取位置
	const sf::FloatRect getBounds() const;    //获取边界
    const float getRotation() const;    //获取旋转角
    
    void render(sf::RenderWindow& window);

private:
	sf::CircleShape shape_;
    sf::RectangleShape stripe_;
    
	sf::Vector2f position_;
};
```

>  SnakeNode作为蛇的身体节点，同样定义了多个getter&setter方法为其设定/获取位置，控制旋转（ 特别是条纹的旋转 ）,其由一个圆形身体及长方形的条纹组成，后续将被放入一个Vector容器中。

* 3、Snake类
> Snake是一个较为庞大的类，其中除了上述讲到的蛇的主体类以外实例化了很多其他类来帮助完成游戏功能，接下来将依次讲解。

Snake.h
```c++
//主体部分
class Snake
{
public:
	Snake();
    //处理输入
	void handleKeyBoardInput(sf::Window&);
    void handleMouseInput(sf::Window&);
    
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	std::vector<Fruit>::iterator checkFruitCollisions(std::vector<Fruit>& fruits);

    //碰撞检测
	bool hitSelf() const;

    //获取长度
	const unsigned getSize() const;
    const unsigned getInitSize() const;

private:
    static const int InitialSize;   //初始化长度
    bool hitSelf_;  //碰撞检测
    
    void initNodes();   //初始化节点
    void setSoundBuffer();  //设置
    
    SnakeHead headNode;
    std::vector<SnakeNode> nodes_;
    
	void move();    //移动
    void headMove();    //头部移动
    void nodeMove();    //节点跟随

	void grow(const unsigned short& len);   //生长
    
	void checkEdgeCollisions(); //检测边缘
	void checkSelfCollisions(); //检测碰撞
	
    const sf::Vector2f getCursorPosition(sf::Window&);

    //状态
	sf::Vector2f position_; //位置
    sf::Vector2f direction_;    //方向
    float rotation_;    //旋转角
    
    //音效
    SoundManager audio;
    sf::Sound dieSound_,clickSound_,pickupSound_,warnSound_;
    
};
```

#### 我们先来看initNode方法

```c++
void Snake::initNodes()
{
    //初始化头结点
    headNode.setPosition(sf::Vector2f(Game::Width / 2 - SnakeNode::Radius,
    Game::Height / 2 - SnakeNode::Radius));
    //初始化身体
    for (int i = 0; i < Snake::InitialSize; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(
            Game::Width / 2 - SnakeNode::Radius,
            Game::Height / 2 - SnakeNode::Radius + (2*SnakeNode::Radius * i))));
    }
}
```
> 将头结点和身体节点分别初始化，对头结点进行初始化，将身体节点放入nodes_的Vector中  


#### 我们再来看move方法

```c++
void Snake::move()
{
    nodeMove();
    headMove();
}
```
> move方法中含有两部分，一个是nodeMove,另一个是headMove.

```c++
void Snake::headMove()
{
    //方向移动控制
    auto directionLen = sqrt(pow(direction_.x,2)+pow(direction_.y,2));
    auto moveDirection = sf::Vector2f( (direction_.x/directionLen),(direction_.y/directionLen));
    //头部移动
    headNode.move(2*SnakeNode::Radius*moveDirection.x,2*SnakeNode::Radius*moveDirection.y);
    //头部旋转
    if(moveDirection.x>0)
        headNode.setRotation(deg(acos(-moveDirection.y)));
    else
        headNode.setRotation(-deg(acos(-moveDirection.y)));
}
```

> headMove控制着头部的方向移动（1单位长度）和旋转方向，保证着头部的正确旋转

```c++
void Snake::nodeMove()
{
    nodes_.at(0).setPosition(headNode.getPosition());
    nodes_.at(0).setRotation(headNode.getRotation());
    for (decltype(nodes_.size()) i = nodes_.size()-1; i > 0 ; --i)
    {
        nodes_.at(i).setPosition(nodes_.at(i-1).getPosition());
        if(nodes_.at(i).getRotation()!=nodes_.at(i-1).getRotation())
            nodes_.at(i).setRotation(nodes_.at(i-1).getRotation());
    }
}

```

> nodeMove控制着身体的跟随，先将第一个身体节点的位置和旋转相同于头结点，再通过遍历nodes_，使每一个节点的位置和旋转度同步于其前方的一个节点，从而实现整体的跟随移动和自然的旋转。

### 接下来是grow方法

```c++
void Snake::grow(const unsigned short& len)
{
    //蛇尾最初生长时重叠在一起，随着蛇的移动慢慢生长，从而防止出现蛇头被突然生长出来的蛇尾撞死的情况
    for(auto i=len;i>0;--i){
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
                nodes_[nodes_.size() - 1].getPosition().y)));
    }
}
```

> 正如注释所说，蛇尾最初生长时重叠在一起，随着蛇的移动慢慢生长，从而防止出现蛇头被突然生长出来的蛇尾撞死的情况

### 下面是处理输入部分

handleKeyBoardInput
```c++
void Snake::handleKeyBoardInput(sf::Window& window)   //输入处理
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && deg(getAngle(direction_, sf::Vector2f(0,1)))>=90)
        direction_ = sf::Vector2f(0,-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && deg(getAngle(direction_, sf::Vector2f(0,-1)))>=90)
        direction_ = sf::Vector2f(0,1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && deg(getAngle(direction_, sf::Vector2f(1,0)))>=90)
        direction_ = sf::Vector2f(-1,0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && deg(getAngle(direction_, sf::Vector2f(-1,0)))>=90)
        direction_ = sf::Vector2f(1,0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}
```

> 键盘输入，限制了转向方向，不能反向转向，避免了源代码反向移动死亡的现象。

```c++
void Snake::handleMouseInput(sf::Window& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(deg(getAngle(direction_, getCursorPosition(window) - nodes_[0].getPosition())) <= 90) //禁止反向移动
        {
            clickSound_.play();
            direction_ = getCursorPosition(window) - nodes_[0].getPosition();
        }
        else{
            warnSound_.play();
        }
    }
}
```

> 在鼠标移动中，也限制了转向角不能大于90°

### 接着看一下处理水果碰撞部分

```c++
std::vector<Fruit>::iterator Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
        if (it->getBounds().intersects(nodes_[0].getBounds())){
			toRemove = it;
            //collide!
            grow(toRemove->getBonus());
            pickupSound_.play();
            toRemove->setPosition(generateLocation());
        }
	}
    return toRemove;
}
```

> 并非像源代码中直接删除节点，而是用genertateLocation()重新生成位置

### 然后是setSoundBuffer部分，这里就涉及到我的统一资源管理

```c++
void Snake::setSoundBuffer()
{
    dieSound_.setBuffer(audio.mSoundHolder.get(SoundType::die));
    pickupSound_.setBuffer(audio.mSoundHolder.get(SoundType::pickup));
    clickSound_.setBuffer(audio.mSoundHolder.get(SoundType::click));
    warnSound_.setBuffer(audio.mSoundHolder.get(SoundType::warn));
}
```

> 其中audio为实例化的SoundManager类

---
### 素材管理
#### 素材管理包含ResourceHolder,SoundManager,TextureManager三部分

> 此处附上SoundManager.h代码

```c++
enum class SoundType{
    die,click,pickup,warn
};
class SoundManager
{
public:
    SoundManager();
    ~SoundManager();
    
    ResourceHolder<sf::SoundBuffer, SoundType> mSoundHolder;
};
```
> 其中实例化了模板类 ResourceHolder,将SoundType作为key，sf::SoundBuffer为value储存在map中进行统一管理。

### 同理的有TextureManager
```c++
enum class ColorType    //颜色类型
{
    White,Black,Brown
};
enum class TextType // Text(ure)Type 素材类型
{
    Grid,MenuBg,SettingBg,GameOverBg,SnakeHead,MusicIconOn,MusicIconOff,RadioOn,RadioOff,Radio
};
enum class ScreenType   //屏幕类型
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
```

> 可以看见TextureManager定义了多个初始化入口，可以直接通过材质类型初始化，或指定特定游戏屏幕，和网格颜色，初始化相应内容。

```c++
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
```

> 通过指定屏幕初始化的方式，在载入相应屏幕的时候加载对应需要的材质，既实现了材质路径的统一化管理，也实现了精确化加载，防止重复载入的现象发生


#### 我们可以看到上面两个资源管理类中，都有一个实例化的ResourceHolder模板类，此处附上代码

```c++
template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    ResourceHolder();
    ~ResourceHolder();
    void load(Identifier id, const std::string& filename);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
    const short getlen() const;

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
    
};
```

> 此处使用了智能指针，将模板的Identifier和Resource作为map的key和value插入map中，实现资源的统一管理。

### 水果 Fruit.cpp/h

```c++
class Fruit
{
public:
    Fruit(const float& radius_ = 0.f, const sf::Color& Color = sf::Color::White,const unsigned short& Bonus = 0,const sf::Vector2f& position_ = sf::Vector2f(0, 0));  //初始化构造函数
    
    void setPosition(const sf::Vector2f&); //设置位置
    void setRadius(const float&); //设置半径大小
    void setColor(const sf::Color&); //设置颜色
    
    const sf::Color& getColor();    //获取颜色
    const unsigned short& getBonus();   //获取分数(即增长长度)
    sf::FloatRect getBounds() const;
    
    void render(sf::RenderWindow& window);
    
private:
    sf::CircleShape shape_;
    const unsigned short bonus_;
};
```

> 在水果这个类中，设置了较多的getter&setter方法，方便从外部定义改变水果的外观和种类。

> 初始化构造函数中，使用了四个参数，并都带有默认值的构造方法。可以分别指定水果的半径、颜色、分数和位置，十分灵活。

Fruit.cpp
* Fruit代码整体非常的简洁漂亮
```c++
Fruit::Fruit(const float& radius_, const sf::Color& color_, const unsigned short& Bonus,const sf::Vector2f& position_):bonus_(Bonus)
{
	shape_.setPosition(position_);
    shape_.setRadius(radius_);
    shape_.setFillColor(color_);
}

void Fruit::setPosition(const sf::Vector2f& position_)
{
    shape_.setPosition(position_);
}

void Fruit::setRadius(const float& radius_)
{
    shape_.setRadius(radius_);
}

void Fruit::setColor(const sf::Color& color_)
{
    shape_.setFillColor(color_);
}

const sf::Color& Fruit::getColor()
{
    return shape_.getFillColor();
}

const unsigned short& Fruit::getBonus()
{
    return bonus_;
}

sf::FloatRect Fruit::getBounds() const
{
    return shape_.getGlobalBounds();
}


void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

```


---
### 游戏屏幕 GameScreen.cpp/h
再来看游戏屏幕的代码
```c++
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
    
    sf::Text score_;    //分数
    sf::RectangleShape scoreBg_;    //背景遮罩
    sf::Text mKey;  //提示键
    sf::CircleShape musicBg_;   //背景遮罩
};
```
> 其核心是initFruit,initText,initTexture和initGrid四个方法，分别用来初始化水果、字体、材质和网格

#### 主要看 initFruit
```c++
void GameScreen::initFruit(const unsigned short &fruitNum)
{
    fruit_.reserve(fruitNum);
    while (fruit_.size() < int(fruitNum*0.25)){
        fruit_.push_back(Fruit(9.f,sf::Color::Black,0,generateLocation())); //黑色水果
        fruit_.push_back(Fruit(9.f,sf::Color(67, 39, 21),0,generateLocation()));    //棕色水果
    }
    while (fruit_.size() < fruitNum) {
        fruit_.push_back(Fruit(6.f,sf::Color(255,71,87),3,generateLocation())); //红色水果
        fruit_.push_back(Fruit(7.f,sf::Color(2, 252, 254),2,generateLocation()));   //蓝色水果
        fruit_.push_back(Fruit(8.f,sf::Color(18, 243, 8),1,generateLocation()));    //绿色水果
    }
}
```
> 其中利用初始化构造函数指定参数，往vector里按比例插入了不同颜色的水果，其有不同的分数，半径，颜色和随机初始位置

---
### 设置屏幕 SettingScreen.cpp/h
为了能够实现游戏内部的界面风格设置调整，我添加了设置屏幕，并且利用Sprite和鼠标点击位置实现了简单的交互。

```c++
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
    static ColorType bgColor_;  //背景颜色静态变量
    static ColorType gridColor_;    //网格静态变量
private:
    TextureManager texture; //材质管理器
    sf::Sprite bgImg;
    
    RadioBox grid_;
    std::vector<std::shared_ptr<RadioBox>> bgRadioVec_;
    std::vector<std::shared_ptr<RadioBox>> gridRadioVec_;
};
```

> 其中实例化了一个RadioBox类，作为网格开关，以及两个智能指针类型的Vector分别存放三个对应的单选框

* 我们先来看这个RadioBox类

#### RadioBox.cpp/h

```c++
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
```
> 通过定义了很多getter&setter函数进行设置

> 我们主要来看setState和switchState方法

setState
```c++
void RadioBox::setState(const bool flag)
{
    flag ? radio_.setTexture(texture.getTex(TextType::RadioOn)) : radio_.setTexture(texture.getTex(TextType::RadioOff));
    state_ = flag;
}
```
> 通过传入的flag判断设置单选框的On，Off素材，然后把state_更新为flag

switchState
```c++
void RadioBox::switchState()
{
    state_ ? radio_.setTexture(texture.getTex(TextType::RadioOff)) : radio_.setTexture(texture.getTex(TextType::RadioOn));
    state_ = !state_;
}
```

> switchState大致与setState相同，不过是更改当前状态


#### 再回来看SettingScreen

其用了三个静态变量来控制窗口在销毁时依然留存有选项信息

```c++
bool SettingScreen::gridState_ = true;
ColorType SettingScreen::bgColor_ = ColorType::White;
ColorType SettingScreen::gridColor_ = ColorType::Black;
```

> 初始化开启网格，并且背景白色，网格黑色

* 在编写的过程中由于 bgRadioVec_和gridRadioVec_同为存有RadioBox的智能指针Vector，因而编写了一系列模板函数，来简化重复的操作。

```c++
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
```

* 我们接下来看交互如何实现

对于鼠标输入的处理
```c++
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
```

> 通过判断鼠标点按位置和单选框RadioBox的位置是否重合来判断是否点击，

> 而checkRadio保证了单选条件，分别对于背景或网格的三个风格有且仅有一个选项被选中。

---

### 基本上的变换点就介绍到这，更多详情可以阅读代码，注释还是比较详细的。


## 致谢
> 感谢面向对象程序设计的王雪平老师以及张一鸣助教一学期以来的耐心指导，收益颇丰。