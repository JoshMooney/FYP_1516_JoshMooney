#include "stdafx.h"
#include "DemonForm.hpp"

DemonForm::DemonForm() {
	m_speed = 20;
	m_action_cool_down = false;
	m_cool_down = 1.0f;

	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);
	m_probablity.push_back(0.0f);

	m_probablity[TRANS]		= 0.05f;
	m_probablity[MOVE]		= 0.10f;
	m_probablity[SHOOT]		= 0.10f;
	m_form = DEMON;
}
DemonForm::~DemonForm() {

}

void DemonForm::think(Player * p, sf::Vector2f pos, float health) {
	//Pre Think Adjustments
	float dis_to_player = vHelper::distance(pos, p->getPosition());
	if (dis_to_player > 400 && (health <= 50 || p->getPosition().y - pos.y > 150)) {
		m_probablity[SHOOT] += 0.20f;
		m_probablity[TRANS] += 0.01f;
	}
	else if (dis_to_player < 300) {
		m_probablity[MOVE] += 0.20f;
		m_probablity[TRANS] += 0.01f;
	}
	else {
	
	}

	//Clamp the Probablities
	clampProbablity();

	//Take Action
	m_current_action = getAction();

	//Post Think Adjustments
	switch (m_current_action) {
	case MOVE:
		m_probablity[MOVE]		-= 0.05f;
		m_probablity[TRANS]		+= 0.005f;
		break;
	case ATTACK:
		m_probablity[ATTACK]	-= 0.05f;
		m_probablity[TRANS]		+= 0.005f;
		break;
	case SHOOT:
		m_probablity[SHOOT]		-= 0.0025f;
		m_probablity[TRANS]		+= 0.005f;
		break;
	case TRANS:
		break;
	case TAUNT:
		break;
	}
}

void DemonForm::setOrigin(sf::Sprite *s) {

}
void DemonForm::reset() {
	m_probablity[TRANS] = 0.05f;
	m_probablity[MOVE]	= 0.10f;
	m_probablity[SHOOT] = 0.10f;
	
	m_probablity[TAUNT]	= 0.00f;
	m_probablity[ATTACK] = 0.00f;

	m_current_action = MOVE;
}