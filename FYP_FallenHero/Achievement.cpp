#include <stdafx.h>
#include "Achievement.hpp"

Achievements::Achievements() {		}
Achievements::Achievements(SaveSlot *cur) : m_current_slot(cur) {
	first_jump = false;

	m_border_sep = sf::Vector2f(20, 20);
	m_cheevo_size = sf::Vector2f(288, 64);
	m_cheevo.setOrigin(m_cheevo_size.x / 2, m_cheevo_size.y / 2);

	sf::Vector2f pos(SCREEN_WIDTH - (m_border_sep.x + m_cheevo_size.x/ 2), SCREEN_HEIGHT - (m_border_sep.y + m_cheevo_size.y /2));
	//pos = sf::Vector2f(500, 500);
	m_cheevo.setPosition(pos);
}
Achievements::~Achievements() {

}

void Achievements::update() {
	if (m_queue.size() > 0) {
		sf::Color colour = m_cheevo.getColor();
		if (m_cheevo_clock.getElapsedTime().asSeconds() > 6) {
			m_queue.pop();
			//if(m_queue.size() > 0)
				//Make Unlock Noise
			m_cheevo_clock.restart();
		}
		if (m_cheevo_clock.getElapsedTime().asSeconds() > 3.0) {
			float perframe = 255.0f / 3.0f;
			float alpha = m_cheevo_clock.getElapsedTime().asSeconds() * perframe;
			alpha = 255.0 - alpha;

			colour.a = alpha;
			m_queue.front().setColor(colour);
		}
	}
}

void Achievements::render(sf::RenderWindow * w) {
	if (m_queue.size() > 0)
		w->draw(m_queue.front());
}

void Achievements::unlock(Subject::EVENT e) {
	cLog::inst()->print(0, "Achievements", "Achievement Unlocked !");
	string ext = ".png";
	string pre = "Assets/Achievements/";
	string tag = "ACH";

	//Make Achievement here and push onto achievement queue.
	switch (e) {
	case Subject::P_JUMP:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "firstjump" + ext));
		m_queue.push(m_cheevo);
		m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::P_JUMP)] = true;
		m_current_slot->m_achieve_unlocked++;
		break;
	}

	//If there is nothing in the queue restart the clock because it proabably running.
	if (!m_queue.size() > 0) {
		m_cheevo_clock.restart();
		//Make Unlock Noise
	}
}

void Achievements::onNotify(Subject::EVENT evnt, Entity *entity) {
	string tag = "ACH";

	switch (evnt) {
	case Subject::P_JUMP:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::P_JUMP)]) {
			unlock(Subject::P_JUMP);
		}
		break;
	}
}