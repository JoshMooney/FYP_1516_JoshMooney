#include "stdafx.h"
#include "AI.hpp"

DemonAI::DemonAI() {
	human = make_shared<HumanForm>();
	demon = make_shared<DemonForm>();
	slime = make_shared<SlimeForm>();

	m_current_form = human.get();
	m_cur_type = Form::TYPE::HUMAN;
	m_pre_type = m_cur_type;
}
DemonAI::~DemonAI() {

}

void DemonAI::think(Player * p, sf::Vector2f pos, float health) {
	//Check for change in transition
	checkForm();
	//if (m_cur_type != m_pre_type) {
	//	m_pre_type = m_cur_type;
	//	m_current_form->reset();
	//	switch (m_cur_type) {
	//	case Form::TYPE::HUMAN:
	//		m_current_form = human.get();
	//		break;
	//	case Form::TYPE::DEMON:
	//		m_current_form = demon.get();
	//		break;
	//	case Form::TYPE::SLIME:
	//		m_current_form = slime.get();
	//		break;
	//	}
	//}

	m_current_form->think(p, pos, health);
}
void DemonAI::checkForm() {
	if (m_current_form->morphin()) {
  		int num;
		switch (m_cur_type) {
		case Form::TYPE::HUMAN:
			m_current_form->reset();
			num = rand() % 10;
			if (num > 5) {
				m_cur_type = Form::TYPE::SLIME;
				m_current_form = slime.get();
			}
			else {
				m_cur_type = Form::TYPE::DEMON;
				m_current_form = demon.get();
			}
			break;
		case Form::TYPE::DEMON:
			m_current_form->reset();
			m_cur_type = Form::TYPE::HUMAN;
			m_current_form = human.get();
			break;
		case Form::TYPE::SLIME:
			m_current_form->reset();
			m_cur_type = Form::TYPE::HUMAN;
			m_current_form = human.get();
			break;
		}
	}
}
