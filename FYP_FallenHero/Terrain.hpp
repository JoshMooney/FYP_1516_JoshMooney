#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP
#include "stdafx.h"
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"

struct Terrain{
	b2Body *body;
	sf::FloatRect geometry;
};

#endif