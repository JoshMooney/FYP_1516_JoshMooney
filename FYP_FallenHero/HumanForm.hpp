#ifndef _HUMAN_FORM_HPP
#define _HUMAN_FORM_HPP
#include "stdafx.h"
#include "Form.hpp"

class HumanForm : public Form {
private:

public:
	HumanForm();
	~HumanForm();

	void think(Player* p, sf::Vector2f pos, float health);
	void setOrigin(sf::Sprite *s);
	void reset();
};

#endif