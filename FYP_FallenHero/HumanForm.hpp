#ifndef _HUMAN_FORM_HPP
#define _HUMAN_FORM_HPP
#include "stdafx.h"
#include "Form.hpp"

class HumanForm : public Form {
private:
	thor::FrameAnimation frame_idle;
	thor::FrameAnimation frame_dash;
	thor::FrameAnimation frame_hurt;
	thor::FrameAnimation frame_recover;
	thor::FrameAnimation frame_ready;
	thor::FrameAnimation frame_attack;
	thor::FrameAnimation frame_transform;

public:
	HumanForm();
	~HumanForm();

	void think(Player* p);
	void attack(ProjectileManager* p, b2World *w);
	void move(b2Body *bod);
	void setOrigin(sf::Sprite *s);
	void reset();
};

#endif