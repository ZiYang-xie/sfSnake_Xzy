#ifndef SoundManager_h
#define SoundManager_h

#include <SFML/Audio.hpp>
#include "ReasourceHolder.h"

namespace sfSnake
{
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
}
#endif /* SoundManager_h */
