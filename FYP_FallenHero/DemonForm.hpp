#ifndef _DEMON_FORM_HPP
#define _DEMON_FORM_HPP
#include "stdafx.h"
#include "Form.hpp"

class DemonForm : public Form {
private:

public:
	DemonForm();
	~DemonForm();

	void think(Player* p);
	void attack(ProjectileManager* p, b2World *w);
	void move(b2Body *bod);
	void setOrigin(sf::Sprite *s);
	void reset();
};

#endif