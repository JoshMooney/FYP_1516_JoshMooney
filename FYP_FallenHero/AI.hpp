#ifndef _BOSS_AI_HPP
#define _BOSS_AI_HPP
#include "stdafx.h"
#include "ProjectileManager.hpp"
#include "SFML\System.hpp"
#include "Thor\Animations.hpp"

#include "DemonForm.hpp"
#include "HumanForm.hpp"
#include "SlimeForm.hpp"

#include "DarkDemon.hpp"

class DemonAI {
private:
	enum FORM {
		HUMAN,
		DEMON,
		SLIME,
	};
	FORM m_form, m_prev_form;
	sf::Clock m_clock;
	HumanForm* human;
	DemonForm* demon;
	SlimeForm* slime;

	Form* m_current_form;
	thor::Animator<sf::Sprite, DarkDemon::STATE>* m_animatior;
public:
	DemonAI();
	DemonAI(DarkDemon *d);
	~DemonAI();

	void think(Player* p);
	void attack(ProjectileManager* p, b2World *w);
	void move(b2Body *bod);

	void checkForm();
	void setAnimation();
};

#endif