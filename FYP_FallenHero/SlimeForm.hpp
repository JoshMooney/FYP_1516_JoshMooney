#ifndef _SLIME_FORM_HPP
#define _SLIME_FORM_HPP
#include "stdafx.h"
#include "Form.hpp"

class SlimeForm : public Form {
private:

public:
	SlimeForm();
	~SlimeForm();

	void think(Player* p);
	void attack(ProjectileManager* p, b2World *w);
	void move(b2Body *bod);
	void setOrigin(sf::Sprite *s);
	void reset();
};

#endif