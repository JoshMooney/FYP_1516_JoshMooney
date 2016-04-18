#include "stdafx.h"
#include "HumanForm.hpp"

HumanForm::HumanForm() {
	m_speed = 10;
	m_action_cool_down = false;
	m_cool_down = 1.0f;

	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);

	m_probablity[TRANS]		= 0.07f;
	m_probablity[ATTACK]	= 0.10f;
	m_probablity[MOVE]		= 0.08f;
	m_probablity[TAUNT]		= 0.05f;
	m_probablity[SHOOT]		= 0.10f;

	m_form = HUMAN;
}
HumanForm::~HumanForm() {	}

void HumanForm::think(Player * p, sf::Vector2f pos, float health) {
	//Tweak and adjest the probabilties of all the actions here before thinking about anything else
	float dis_to_player = vHelper::distance(pos, p->getPosition());
	if (dis_to_player > 500) {
		m_probablity[SHOOT] += 0.02f;
		m_probablity[TAUNT] += 0.01f;
	}
	else if (dis_to_player < 100) {
		m_probablity[ATTACK] += 0.02f;
		m_probablity[MOVE] += 0.01f;
	}
	else {
		m_probablity[TRANS] -= 0.005f;
	}

	//Clamp the Probablities
	clampProbablity();

	//Take Action
	m_current_action = getAction();

	//Tweak Probablity depending on the outcome
	switch (m_current_action) {
	case MOVE:
		m_probablity[TRANS]		-= 0.005f;
		m_probablity[ATTACK]	+= 0.02f;
		m_probablity[MOVE]		-= 0.02f;
		m_probablity[TAUNT]		+= 0.005f;
		m_probablity[SHOOT]		+= 0.01f;
		break;
	case ATTACK:
		m_probablity[TRANS]		+= 0.005f;
		m_probablity[ATTACK]	-= 0.03f;
		m_probablity[MOVE]		+= 0.02f;
		m_probablity[TAUNT]		+= 0.005f;
		m_probablity[SHOOT]		+= 0.005f;
		break;
	case SHOOT:
		m_probablity[TRANS]		+= 0.01f;
		m_probablity[ATTACK]	+= 0.01f;
		m_probablity[MOVE]		+= 0.01f;
		m_probablity[TAUNT]		+= 0.01f;
		m_probablity[SHOOT]		-= 0.0025f;
		break;
	case TRANS:
		m_probablity[TRANS]		-= 0.4f;
		m_probablity[ATTACK]	+= 0.00f;
		m_probablity[MOVE]		+= 0.00f;
		m_probablity[TAUNT]		+= 0.00f;
		m_probablity[SHOOT]		+= 0.00f;
		break;
	case TAUNT:
		m_probablity[TRANS]		+= 0.00f;
		m_probablity[ATTACK]	+= 0.01f;
		m_probablity[MOVE]		+= 0.01f;
		m_probablity[TAUNT]		-= 0.20f;
		m_probablity[SHOOT]		+= 0.01f;
		break;
	}
}

void HumanForm::setOrigin(sf::Sprite *s) {

}
void HumanForm::reset() {
	m_probablity[TRANS]		= 0.07f;
	m_probablity[ATTACK]	= 0.10f;
	m_probablity[MOVE]		= 0.08f;
	m_probablity[TAUNT]		= 0.05f;
	m_probablity[SHOOT]		= 0.10f;

	m_current_action = MOVE;
}