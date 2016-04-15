#include "stdafx.h"
#include "SlimeForm.hpp"

SlimeForm::SlimeForm() {
	m_speed = 15;
	m_action_cool_down = false;
	m_cool_down = 1.0f;

	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);
	m_probablity.push_back(0.1f);

	m_probablity[TRANS] = 0.01f;
	m_form = SLIME;
}
SlimeForm::~SlimeForm() {

}

void SlimeForm::think(Player * p, sf::Vector2f pos, float health) {
	//Pre Think Adjustments
	if (vHelper::distance(pos, p->getPosition()) > 500) {
		m_probablity[MOVE] += 0.2f;
		m_probablity[SHOOT] += 0.1f;
	}
	else {
		m_probablity[MOVE] -= 0.2f;
		m_probablity[SHOOT] -= 0.1f;
	}

	//Clamp the Probablities
	clampProbablity();

	//Take Action
	m_current_action = getAction();

	//Post Think Adjustments
	switch (m_current_action) {
	case MOVE:
		break;
	case ATTACK:
		break;
	case SHOOT:
		break;
	case TRANS:
		break;
	case TAUNT:
		break;
	}
}

void SlimeForm::setOrigin(sf::Sprite *s) {

}
void SlimeForm::reset() {
	m_probablity[MOVE] = 0.1f;
	m_probablity[ATTACK] = 0.1f;
	m_probablity[SHOOT] = 0.1f;
	m_probablity[TRANS] = 0.01f;
	m_probablity[TAUNT] = 0.1f;
}