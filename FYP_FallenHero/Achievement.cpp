#include <stdafx.h>
#include "Achievement.hpp"

Achievements::Achievements() {		}
Achievements::Achievements(SaveSlot *cur) : m_current_slot(cur) {

}
Achievements::~Achievements() {

}

void Achievements::update() {

}

void Achievements::unlock(string s) {
	std::cout << "Achievement Unlocked" << std::endl;
	sf::Vector2f size = sf::Vector2f(450, 80);
	string ext = ".png";

	/*auto e = std::make_unique<Entity>();
	e->addComponent("gfx", std::make_unique<Component::Drawable>("./res/img/Achievements/" + s + ext, size.getX(), size.getY(), true));
	e->addComponent("pos", std::make_unique<Component::Position>(350, 50));
	e->addComponent("ttl", std::make_unique<Component::TimeToLive>(200));
	
	entity_list->push_back(std::move(e));
	*/
}

void Achievements::onNotify(Subject::EVENT evnt, Entity *entity) {
	switch (evnt) {
	
	}
	/*Component::FactionComponent::Team team;
	string tag;*/
	/*
	if (entity != nullptr && entity->hasComponentsOfType(Component::Type::FACTION) && entity->hasComponentsOfType(Component::Type::USER_DATA)) {
		team = entity->getComponent<Component::FactionComponent>(Component::Type::FACTION)->GetFaction();
		tag = entity->getComponent<Component::UserData<string>>(Component::Type::USER_DATA)->getData();
		if (team == players_team) {
			switch (evnt) {
			case Subject::OVERv1:
				if (!v1Overkill) {
					v1Overkill = true;
					unlock("v1Overkill");
				}
				break;
			case Subject::OVERv2:
				if (!v2Overkill) {
					v2Overkill = true;
					unlock("v2Overkill");
				}
				break;
			case Subject::OVERv3:
				if (!v3Overkill) {
					v3Overkill = true;
					unlock("v3Overkill");
				}
				break;

			case Subject::SPAWN:
				spawn_count += 1;
				if (!first_spawn) {
					first_spawn = true;
					unlock("firstSpawn");
				}
				if (!fifth_spawn && spawn_count >= 5) {
					fifth_spawn = true;
					unlock("fifthSpawn");
				}
				if (!melee_spawn && tag == "Melee") {
					melee_spawn = true;
				}
				if (!archer_spawn && tag == "Archer") {
					archer_spawn = true;
				}
				if (!siege_spawn && tag == "Siege") {
					siege_spawn = true;
				}
				break;
			case Subject::FIRST_SPAWN:
				unlock("firstSpawn");
				break;
			case Subject::FIFTH_SPAWN:
				unlock("fifthSpawn");
				break;
			case Subject::START_G:
				unlock("easyCome");
				break;
			case Subject::BIG_G:
				unlock("bigSpender");
				break;
				break;
			case Subject::BUILD:
				if (!first_build) {
					first_build = true;
					unlock("beginBuilder");
				}
				if (!first_upgrade && (tag == "Power" || tag == "Range")) {
					first_upgrade = true;
					unlock("upgadeTurret");
				}
				if (!built_power && tag == "Power") {
					built_power = true;
				}
				if (!built_ranged && tag == "Range") {
					built_ranged = true;
				}
				break;
			}
		}
	}
	else {
		switch (evnt) {
		case Subject::OPPS:
			if (!oppsCheevo) {
				oppsCheevo = true;
				unlock("opps");
			}
		case Subject::START_G:
			unlock("easyCome");
			break;
		case Subject::BIG_G:
			unlock("bigSpender");
			break;
		case Subject::DEATH:
			if (!first_kill) {
				first_kill = true;
				unlock("firstKill");
			}
			if (!melee_kill && tag == "Melee") {
				melee_kill = true;
			}
			if (!archer_kill && tag == "Archer") {
				archer_kill = true;
			}
			if (!siege_kill && tag == "Siege") {
				siege_kill = true;
			}
			break;
		}
	}*/
}