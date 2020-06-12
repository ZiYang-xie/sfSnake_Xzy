#include "SoundManager.h"
#include <iostream>
using namespace sfSnake;

SoundManager::SoundManager(){
    mSoundHolder.load(SoundType::pickup, "./Resource/Sounds/pickup.wav");
    mSoundHolder.load(SoundType::warn, "./Resource/Sounds/warn.wav");
    mSoundHolder.load(SoundType::click, "./Resource/Sounds/click.wav");
    mSoundHolder.load(SoundType::die, "./Resource/Sounds/die.wav");
};
SoundManager::~SoundManager(){};
