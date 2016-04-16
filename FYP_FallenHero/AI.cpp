#include "stdafx.h"
#include "AI.hpp"

DemonAI::DemonAI() {
	human = make_shared<HumanForm>();
	demon = make_shared<DemonForm>();
	slime = make_shared<SlimeForm>();

	m_current_form = human.get();
	m_current_type = Form::TYPE::HUMAN;
	m_previous_type = m_current_type;
}
DemonAI::~DemonAI() {

}

void DemonAI::think(Player * p, sf::Vector2f pos, float health) {
	//Check for change in transition
	checkForm();
	if (m_current_type != m_previous_type) {
		m_previous_type = m_current_type;
		m_current_form->reset();
		switch (m_current_type) {
		case Form::TYPE::HUMAN:
			m_current_form = human.get();
			break;
		case Form::TYPE::DEMON:
			m_current_form = demon.get();
			break;
		case Form::TYPE::SLIME:
			m_current_form = slime.get();
			break;
		}
	}

	m_current_form->think(p, pos, health);
}
void DemonAI::checkForm() {
	if (m_current_form->morphin()) {
  		int num;
		switch (m_current_form->m_form) {
		case Form::TYPE::HUMAN:
			num = rand() % 10;
			if (num > 5)
				m_current_type = Form::TYPE::SLIME;
			else
				m_current_type = Form::TYPE::DEMON;
			break;
		case Form::TYPE::DEMON:
			m_current_type = Form::TYPE::HUMAN;
			break;
		case Form::TYPE::SLIME:
			m_current_type = Form::TYPE::HUMAN;
			break;
		}
	}
}
