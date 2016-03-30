#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP
#include "stdafx.h"
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"

/**
*	@class Terrain
*	@brief This is a simple wrapper class for creating a box body that also 
*	has a SFML geometry componenet for later features.
*/
struct Terrain{
	//!The Body associated with the Terrain
	b2Body *body;
	//!The Geometry associated with the Terrain
	sf::FloatRect geometry;
};

#endif