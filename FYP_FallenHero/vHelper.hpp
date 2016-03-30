#ifndef V_HELPER_HPP
#define V_HELPER_HPP

#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "Box2D\Box2D.h"
#include <math.h>

/**
*	@namespace vHelper
*	@brief This is the vector helper class for the game. It has a 
*	Box2D to SFML Vector translation methods and also stores the box2d
*	scale required.
*/
namespace vHelper{
	static float B2_SCALE = 32.0f;																	//!<This is the BOX2D scale to multiply and divide everything by 
	static sf::Vector2f toSF(b2Vec2 v)	{ return sf::Vector2f(v.x * B2_SCALE, v.y * B2_SCALE); }	//!<Translates a Box2D Vector2 to a sf::Vector2f
	static b2Vec2 toB2(sf::Vector2f v)	{ return b2Vec2(v.x / B2_SCALE, v.y / B2_SCALE); }          //!<Translates a sf::Vector2f to a Box2D Vector2
	static sf::IntRect FloatToInt(const sf::FloatRect& f) {                                         //!<Translates a FloatRect to a IntRect
		return sf::IntRect((int)f.left, (int)f.top, (int)f.width, (int)f.height);                   
	}
	static float distance(sf::Vector2f point_a, sf::Vector2f point_b) { return sqrt(pow(point_a.x - point_b.x, 2) + pow(point_a.y - point_b.y, 2)); }
}

#endif