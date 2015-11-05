#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

struct Entity : public sf::Sprite {
	virtual void update(sf::Time dt) = 0;

	int e_hp;
	sf::Texture e_texture;
	bool e_body_active;
	b2Body *e_box_body;
};

#endif