#ifndef _BOSS_AI_HPP
#define _BOSS_AI_HPP
#include "stdafx.h"
#include "ProjectileManager.hpp"
#include "SFML\System.hpp"
#include "Thor\Animations.hpp"
#include <memory>
#include "Form.hpp"

class DemonForm;
class HumanForm; 
class SlimeForm;

class DemonAI {
private:
	sf::Clock m_clock;
	shared_ptr<HumanForm> human;
	shared_ptr<DemonForm> demon;
	shared_ptr<SlimeForm> slime;

	Form* m_current_form;
	Form::TYPE m_current_type, m_previous_type;
public:
	DemonAI();
	~DemonAI();

	void think(Player* p, sf::Vector2f pos, float health);

	void checkForm();
	Form::TYPE getForm() {
		return m_current_type;
	}
	Form::ACTIONS getAction() {
		return m_current_form->m_current_action;
	}
};

#include "DemonForm.hpp"
#include "HumanForm.hpp"
#include "SlimeForm.hpp"

#endif