#ifndef MathProcess_h
#define MathProcess_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <random>

#include "Game.h"
#include "SnakeNode.h"
#define pi 3.1415926

const float rad(const float&);
const float deg(const float&);

const float getAngle(const sf::Vector2f&, const sf::Vector2f&);
const sf::Vector2f generateLocation();

#endif /* MathProcess_h */
