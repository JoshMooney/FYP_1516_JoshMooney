#ifndef V_HELPER_HPP
#define V_HELPER_HPP

#include "SFML\System\Vector2.hpp"
#include "Box2D\Box2D.h"

namespace vHelper{
	sf::Vector2f toSF(b2Vec2 v)	{ return sf::Vector2f(v.x, v.y); }
	b2Vec2 toB2(sf::Vector2f v)	{ return b2Vec2(v.x, v.y); }
}

#endif