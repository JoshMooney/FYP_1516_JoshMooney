#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "ResourceManager.hpp"
#include "cLog.hpp"
#include <string>
#include "vHelper.hpp"

class Enemy : public sf::Sprite {
public:
	int e_hp;
	string e_texture;
	bool e_body_active;
	bool e_can_despawn;
	b2Body *e_box_body;
	bool e_direction;

	virtual void update(FTS fts) = 0;
	virtual void render(sf::RenderWindow &w) = 0;
	virtual void alineSprite() = 0;

	virtual sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }
	bool isAlive() { return e_body_active; }
	bool canDespawn() { return e_can_despawn; }
	void setActive(bool b) { e_body_active = b; }
	sf::FloatRect getBounds() {
		sf::Vector2u size = getTexture()->getSize();
		return sf::FloatRect{ getPosition().x, getPosition().y, (float)size.x, (float)size.y };
	}
};

#endif