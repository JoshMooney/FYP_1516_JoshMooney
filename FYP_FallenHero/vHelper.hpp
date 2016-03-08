#ifndef V_HELPER_HPP
#define V_HELPER_HPP

#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "Box2D\Box2D.h"
#include <math.h>

namespace vHelper{
	static float B2_SCALE = 32.0f;
	static sf::Vector2f toSF(b2Vec2 v)	{ return sf::Vector2f(v.x * B2_SCALE, v.y * B2_SCALE); }
	static b2Vec2 toB2(sf::Vector2f v)	{ return b2Vec2(v.x / B2_SCALE, v.y / B2_SCALE); }
	static sf::IntRect FloatToInt(const sf::FloatRect& f) {
		return sf::IntRect((int)f.left, (int)f.top, (int)f.width, (int)f.height);
	}
	static float distance(sf::Vector2f p1, sf::Vector2f p2) {
		return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));//sqrt((p1.getX() - p2.getX())*(p1.getX() - p2.getX()) + (p1.getY() - p2.getY())*(p1.getY() - p1.getY())); 
	}
}

#endif