#ifndef _FLYER_HPP
#define _FLYER_HPP
#include "stdafx.h"
#include "Enemy.hpp"

class Flyer : public Enemy {
private:
	float speedFactor;
	sf::Vector2u m_text_size;
	float m_speed;
public:
	enum AI { WHITE, GREY, BLACK };
	AI ai;
	enum STATE { FREE, RAILED, IDLE, DEATH };
	STATE m_current_state;
};

#endif