#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "ResourceManager.hpp"
#include "cLog.hpp"
#include <string>

class Enemy : public sf::Sprite {
public:
	int e_hp;
	string e_texture;
	bool e_body_active;
	b2Body *e_box_body;
	bool e_direction;

	virtual void update(FTS fts) = 0;
	virtual void render(sf::RenderWindow &w) = 0;
	virtual void alineSprite() = 0;
	virtual b2Vec2 getCenter() { return e_box_body->GetPosition(); }
	bool isAlive() { return e_body_active; }
	void setActive(bool b) { e_body_active = b; }
	//int getHP() { return e_hp; }
	//void setHP(int h) { e_hp = h; }
	//string getTextureString() { return e_texture; }
	//void setTextureString(string s) { e_texture = s; }
	//bool isActive() { return e_body_active; }
	//void setActive(bool a) { e_body_active = a; }
	//b2Body* getBody() { return e_box_body; }
};

#endif