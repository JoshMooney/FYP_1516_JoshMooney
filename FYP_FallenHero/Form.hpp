#ifndef _FORM_HPP
#define _FORM_HPP
#include "stdafx.h"
#include "Box2D\Box2D.h"
#include "Player.hpp"
#include "Thor\Animations.hpp"
#include <vector>

class Form {
private:
	
public:
	bool m_action_cool_down;
	float m_cool_down;
	float m_speed;
	sf::Vector2f m_position;
	bool has_attacked;

	enum TYPE {
		HUMAN,
		DEMON,
		SLIME,
	};
	TYPE m_form;

	enum ACTIONS {
		MOVE,
		ATTACK,
		SHOOT,
		TRANS,
		TAUNT,
	};
	ACTIONS m_current_action;

	vector<float> m_probablity;
	Form() {	}
	~Form()	{	}

	virtual void setOrigin(sf::Sprite *s) = 0;
	virtual void think(Player* p, sf::Vector2f pos, float health) = 0;
	bool morphin() {
  		if (m_current_action == TRANS)
			return true;
		return false;
	}
	ACTIONS getAction() {
		float max = 0;
		for (int i = 0; i < m_probablity.size(); i++)
			max += m_probablity[i];

		float result;
		result = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
		
		for (int i = m_probablity.size() - 1; i >= 0; i--) {
			max -= m_probablity[i];
			if (result > max) {
				m_current_action = static_cast<ACTIONS>(i);
				return m_current_action;
			}
		}
	}
	virtual void reset() = 0;
	void clampProbablity() {
		for (int i = 0; i < m_probablity.size(); i++) {
			if (m_probablity[i] > 1.0)
				m_probablity[i] = 1.0;
			if (m_probablity[i] < 0.0)
				m_probablity[i] = 0.0;
		}
	}
};

#include "DarkDemon.hpp"

#endif