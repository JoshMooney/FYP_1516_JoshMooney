#include "stdafx.h"
#include "HumanForm.hpp"

HumanForm::HumanForm() {
	m_speed = 10;
	m_action_cool_down = false;
	m_cool_down = 1.0f;

	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);

	m_probablity[TRANS] = 0.01f;

	m_form = HUMAN;
}
HumanForm::~HumanForm() {	}

void HumanForm::think(Player * p, sf::Vector2f pos, float health) {
	//Tweak and adjest the probabilties of all the actions here before thinking about anything else
	if (vHelper::distance(pos, p->getPosition()) > 500) {
		m_probablity[SHOOT] += 0.2f;
		m_probablity[TAUNT] += 0.2f;

	}
	else {
		m_probablity[SHOOT] -= 0.2f;
		m_probablity[TAUNT] -= 0.2f;
	}

	//Clamp the Probablities
	clampProbablity();

	//Take Action
	m_current_action = getAction();

	//Tweak Probablity depending on the outcome
	switch (m_current_action) {
	case MOVE:
		m_probablity[MOVE] -= 0.05f;
		m_probablity[ATTACK] += 0.2f;
		break;
	case ATTACK:
		m_probablity[MOVE] += 0.2f;
		m_probablity[TAUNT] += 0.2f;
		m_probablity[SHOOT] += 0.2f;
		m_probablity[ATTACK] -= 0.2f;
		break;
	case SHOOT:
		m_probablity[MOVE] += 0.2f;
		m_probablity[TAUNT] += 0.05f;
		m_probablity[SHOOT] -= 0.1f;
		m_probablity[ATTACK] -= 0.2f;
		break;
	case TRANS:
		reset();
		break;
	case TAUNT:
		m_probablity[TAUNT] -= 0.3f;
		break;
	}
}

void HumanForm::setOrigin(sf::Sprite *s) {

}
void HumanForm::reset() {
	m_probablity[MOVE] =	0.10f;
	m_probablity[ATTACK] =	0.10f;
	m_probablity[SHOOT] =	0.10f;
	m_probablity[TRANS] =	0.05f;
	m_probablity[TAUNT] =	0.10f;
}