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
	//float distance(sf::Vector2f p1, sf::Vector2f p2) { return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p1.y)); }
}

#endif