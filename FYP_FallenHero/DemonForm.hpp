#ifndef _DEMON_FORM_HPP
#define _DEMON_FORM_HPP
#include "stdafx.h"
#include "Form.hpp"

class DemonForm : public Form {
private:

public:
	DemonForm();
	~DemonForm();

	void think(Player* p, sf::Vector2f pos, float health);
	void setOrigin(sf::Sprite *s);
	void reset();
};

#endif