#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "stdafx.h"
#include "Entity.hpp"

class Enemy : public Entity {
private:

public:
	Enemy();
	~Enemy();

	virtual void update() = 0;
	virtual void render(sf::RenderWindow ) = 0;
};

#endif