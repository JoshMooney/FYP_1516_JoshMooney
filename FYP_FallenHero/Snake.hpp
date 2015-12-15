#ifndef _SNAKE_HPP
#define _SNAKE_HPP
#include "stdafx.h"
#include "Entity.hpp"
#include "Enemy.hpp"



class Snake : public Enemy {
private:

public:
	Snake();
	Snake(b2World *world);

	void update() = 0;
	void render(sf::RenderWindow) = 0;
};

#endif