#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "stdafx.h"
#include "Entity.hpp"

class Enemy {
private:
	int e_hp;
	string e_texture;
	bool e_body_active;
	b2Body *e_box_body;
public:
	Enemy();
	~Enemy();

	virtual void update() = 0;
	virtual void render(sf::RenderWindow ) = 0;

	int getHP() { return e_hp; }
	string getTextureString() { return e_texture; }
	bool isActive() { return e_body_active; }
	b2Body* getBody() { return e_box_body; }
};

#endif