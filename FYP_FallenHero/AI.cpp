#include "stdafx.h"
#include "AI.hpp"

DemonAI::DemonAI() {

}
DemonAI::DemonAI(DarkDemon * d) {
	human = new HumanForm();
	demon = new DemonForm();
	slime = new SlimeForm();

	m_current_form = human;
	m_animatior = &d->m_animator;
}
DemonAI::~DemonAI() {

}

void DemonAI::think(Player * p) {
	//Check for change in transition
	checkForm();
	if (m_form != m_prev_form) {
		m_prev_form = m_form;
		m_current_form->reset();
		switch (m_form) {
		case HUMAN:
			m_current_form = human;
			break;
		case DEMON:
			m_current_form = demon;
			break;
		case SLIME:
			m_current_form = slime;
			break;
		}
	}

	if (m_clock.getElapsedTime().asSeconds() > 4)
		m_current_form->think(p);
}
void DemonAI::attack(ProjectileManager * p, b2World * w) {
	if (m_current_form->m_current_action == Form::ATTACK && !m_current_form->has_attacked) {
		m_current_form->has_attacked = true;
	}
}
void DemonAI::move(b2Body * bod) {
	if (m_current_form->m_current_action == Form::MOVE) {
		m_current_form->move(bod);
	}
}
void DemonAI::checkForm() {
	if (m_current_form->morphin()) {
		int num;
		switch (m_form) {
		case HUMAN:
			num = rand() % 10;
			if (num > 5)
				m_form = SLIME;
			else
				m_form = DEMON;
			break;
		case DEMON:
			m_form = HUMAN;
			break;
		case SLIME:
			m_form = HUMAN;
			break;
		}
	}
}
void DemonAI::setAnimation() {
	
}
