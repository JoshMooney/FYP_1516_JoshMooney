#include <stdafx.h>
#include "Achievement.hpp"
#include <string>
#include <assert.h>

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
	sf::Texture* m_texture;

	//Make Achievement here and push onto achievement queue.
	switch (e) {
	case Subject::FIRST_JUMP:
		m_texture = &ResourceManager<sf::Texture>::instance()->get(pre + "first_jump" + ext);
		assert(m_texture == nullptr);
		m_cheevo.setTexture(*m_texture);
		break;
	case Subject::FIRST_ATTACK:
		m_texture = &ResourceManager<sf::Texture>::instance()->get(pre + "first_attack" + ext);
		assert(m_texture == nullptr);
		m_cheevo.setTexture(*m_texture);
		break;
	case Subject::PICKUP_100:
		m_texture = &ResourceManager<sf::Texture>::instance()->get(pre + "pickup_100" + ext);
		assert(m_texture == nullptr);
		m_cheevo.setTexture(*m_texture);
		break;

	case Subject::ELEVATOR_PITCH:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "elevator_pitch" + ext));
		break;
	case Subject::DEMO_DAY:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "demo_day" + ext));
		break;
	case Subject::PROJECTILE_HITTER:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "projectile_hitter" + ext));
		break;
	case Subject::OUCH:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "ouch" + ext));
		break;
	case Subject::OUT_OF_CATS_LIVES:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "outofcatslives" + ext));
		break;
	case Subject::WILE_E_COYOTE:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "wile_e_coyote" + ext));
		break;

	case Subject::FINISH_LVL1:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "finishedLVL1" + ext));
		break;
	case Subject::FINISH_LVL2:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "finishedLVL2" + ext));
		break;
	case Subject::FINISH_LVL3A:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "finishedLVL3A" + ext));
		break;
	case Subject::FINISH_LVL3B:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "finishedLVL3B" + ext));
		break;
	case Subject::FINISH_LVL4:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "finishedLVL4" + ext));
		break;
	case Subject::FINISH_LVL5:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "finishedLVL5" + ext));
		break;

	case Subject::PICKUP_1000:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "pickup_1000" + ext));
		break;
	case Subject::ALL_SHAPES_SIZES:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "all_shapes_sizes" + ext));
		break;
	case Subject::LOCK_SMITH:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "lock_smith" + ext));
		break;
	case Subject::THIEF_OR_ADVENTURER:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "thief_or_adventurer" + ext));
		break;
	case Subject::MULTI_CHECKPOINT:
		m_cheevo.setTexture(ResourceManager<sf::Texture>::instance()->get(pre + "multi_checkpoint" + ext));
		break;
	}
	
	m_queue.push(m_cheevo);
	m_current_slot->m_ACH_DATA[tag + std::to_string(e)] = true;
	m_current_slot->m_achieve_unlocked++;

	//If there is nothing in the queue restart the clock because it proabably running.
	if (m_queue.size() == 1) {
		m_cheevo_clock.restart();
		//Make Unlock Noise
	}
}

void Achievements::onNotify(Subject::EVENT evnt, Entity *entity) {
	string tag = "ACH";

	switch (evnt) {
	case Subject::FIRST_JUMP:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FIRST_JUMP)]) {
			unlock(Subject::FIRST_JUMP);
		}
		break;
	case Subject::FIRST_ATTACK:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FIRST_ATTACK)]) {
			unlock(Subject::FIRST_ATTACK);
		}
		break;
	case Subject::PICKUP_100:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::PICKUP_100)]) {
			unlock(Subject::PICKUP_100);
		}
		break;

	case Subject::ELEVATOR_PITCH:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::ELEVATOR_PITCH)]) {
			unlock(Subject::ELEVATOR_PITCH);
		}
		break;
	case Subject::DEMO_DAY:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::DEMO_DAY)]) {
			unlock(Subject::DEMO_DAY);
		}
		break;
	case Subject::PROJECTILE_HITTER:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::PROJECTILE_HITTER)]) {
			unlock(Subject::PROJECTILE_HITTER);
		}
		break;
	case Subject::OUCH:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::OUCH)]) {
			unlock(Subject::OUCH);
		}
		break;
	case Subject::OUT_OF_CATS_LIVES:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::OUT_OF_CATS_LIVES)]) {
			m_current_slot->m_STAT_DATA["STAT1"] += 1;
			if(m_current_slot->m_STAT_DATA["STAT1"] > 9)
				unlock(Subject::OUT_OF_CATS_LIVES);
		}
		break;
	case Subject::WILE_E_COYOTE:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::WILE_E_COYOTE)]) {
			unlock(Subject::WILE_E_COYOTE);
			m_current_slot->m_STAT_DATA["STAT1"] += 1;
			if (m_current_slot->m_STAT_DATA["STAT1"] > 9)
				unlock(Subject::OUT_OF_CATS_LIVES);
		}
		break;

	#pragma region Finish Level Achievements
	case Subject::FINISH_LVL1:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FINISH_LVL1)]) {
			unlock(Subject::FINISH_LVL1);
		}
		break;
	case Subject::FINISH_LVL2:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FINISH_LVL2)]) {
			unlock(Subject::FINISH_LVL2);
		}
		break;
	case Subject::FINISH_LVL3A:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FINISH_LVL3A)]) {
			unlock(Subject::FINISH_LVL3A);
		}
		break;
	case Subject::FINISH_LVL3B:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FINISH_LVL3B)]) {
			unlock(Subject::FINISH_LVL3B);
		}
		break;
	case Subject::FINISH_LVL4:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FINISH_LVL4)]) {
			unlock(Subject::FINISH_LVL4);
		}
		break;
	case Subject::FINISH_LVL5:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::FINISH_LVL5)]) {
			unlock(Subject::FINISH_LVL5);
		}
		break;
	#pragma endregion

	case Subject::PICKUP_1000:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::PICKUP_1000)]) {
			unlock(Subject::PICKUP_1000);
		}
		break;
	case Subject::ALL_SHAPES_SIZES:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::ALL_SHAPES_SIZES)]) {
			unlock(Subject::ALL_SHAPES_SIZES);
		}
		break;
	case Subject::LOCK_SMITH:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::LOCK_SMITH)]) {
			unlock(Subject::LOCK_SMITH);
		}
		break;
	case Subject::THIEF_OR_ADVENTURER:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::THIEF_OR_ADVENTURER)]) {
			unlock(Subject::THIEF_OR_ADVENTURER);
		}
		break;
	case Subject::MULTI_CHECKPOINT:
		if (!m_current_slot->m_ACH_DATA[tag + std::to_string(Subject::MULTI_CHECKPOINT)]) {
			unlock(Subject::MULTI_CHECKPOINT);
		}
		break;
	
	//Stat trackers
	case Subject::GEM_PICK:
		
		break;
	case Subject::CB_DESTROY:
		
		break;
	case Subject::CP_TRIP:
		m_current_slot->m_STAT_DATA["STAT3"] += 1;
		if(m_current_slot->m_STAT_DATA["STAT3"] >= 5 && !m_current_slot->m_ACH_DATA["ACH" + Subject::MULTI_CHECKPOINT])
			onNotify(Subject::MULTI_CHECKPOINT, entity);
		break;
	case Subject::BULLET_HIT:
		m_current_slot->m_STAT_DATA["STAT4"] += 1;
		if (m_current_slot->m_STAT_DATA["STAT4"] >= 5 && !m_current_slot->m_ACH_DATA["ACH" + Subject::PROJECTILE_HITTER])
			onNotify(Subject::PROJECTILE_HITTER, entity);
		break;
	//Each of the different types of blocks
	case Subject::DIRT_32:
		m_current_slot->m_STAT_DATA["STAT5"] += 1;
		if (!m_current_slot->m_ACH_DATA["ACH" + Subject::instance()->ALL_SHAPES_SIZES]) {
			bool all_blocks = true;
			for (int i = 4; i < 10; i++)
				if (!m_current_slot->m_STAT_DATA["STAT" + (i + 1)])
					all_blocks = false;

			if (all_blocks)
				onNotify(Subject::ALL_SHAPES_SIZES, entity);
		}
		break;
	case Subject::DIRT_64:
		m_current_slot->m_STAT_DATA["STAT6"] +=1;
		if (!m_current_slot->m_ACH_DATA["ACH" + Subject::instance()->ALL_SHAPES_SIZES]) {
			bool all_blocks = true;
			for (int i = 4; i < 10; i++)
				if (!m_current_slot->m_STAT_DATA["STAT" + (i + 1)])
					all_blocks = false;

			if (all_blocks)
				onNotify(Subject::ALL_SHAPES_SIZES, entity);
		}
		break;
	case Subject::SAND_32:
		m_current_slot->m_STAT_DATA["STAT7"] += 1;
		if (!m_current_slot->m_ACH_DATA["ACH" + Subject::instance()->ALL_SHAPES_SIZES]) {
			bool all_blocks = true;
			for (int i = 4; i < 10; i++)
				if (!m_current_slot->m_STAT_DATA["STAT" + (i + 1)])
					all_blocks = false;

			if (all_blocks)
				onNotify(Subject::ALL_SHAPES_SIZES, entity);
		}
		break;
	case Subject::SAND_64:
		m_current_slot->m_STAT_DATA["STAT8"] += 1;
		if (!m_current_slot->m_ACH_DATA["ACH" + Subject::instance()->ALL_SHAPES_SIZES]) {
			bool all_blocks = true;
			for (int i = 4; i < 10; i++)
				if (!m_current_slot->m_STAT_DATA["STAT" + (i + 1)])
					all_blocks = false;

			if (all_blocks)
				onNotify(Subject::ALL_SHAPES_SIZES, entity);
		}
		break;
	case Subject::ROCK_32:
		m_current_slot->m_STAT_DATA["STAT9"] += 1;
		if (!m_current_slot->m_ACH_DATA["ACH" + Subject::instance()->ALL_SHAPES_SIZES]) {
			bool all_blocks = true;
			for (int i = 4; i < 10; i++)
				if (!m_current_slot->m_STAT_DATA["STAT" + (i + 1)])
					all_blocks = false;

			if (all_blocks)
				onNotify(Subject::ALL_SHAPES_SIZES, entity);
		}
		break;
	case Subject::ROCK_64:
		m_current_slot->m_STAT_DATA["STAT10"] += 1;
		if (!m_current_slot->m_ACH_DATA["ACH" + Subject::instance()->ALL_SHAPES_SIZES]) {
			bool all_blocks = true;
			string l_name;
			for (int i = 4; i < 10; i++) {
				int index = i + 1;
				l_name = "STAT" + std::to_string(index);
				if (!m_current_slot->m_STAT_DATA[l_name] > 0)
					all_blocks = false;
			}
			if (all_blocks)
				onNotify(Subject::ALL_SHAPES_SIZES, entity);
		}
		break;
	}
}