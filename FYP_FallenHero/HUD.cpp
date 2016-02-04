#include "stdafx.h"
#include "HUD.hpp"

HUD::HUD() {
	
}

HUD::HUD(Player * p) {
	player = p;

	loadMedia();
	hp_position = sf::Vector2f(SCREEN_WIDTH / 2 - (m_hp_bar.getTexture()->getSize().x / 2), 20);
	sf::Vector2f xp_position = sf::Vector2f(SCREEN_WIDTH / 2 - (m_hp_bar.getTexture()->getSize().x / 2), 50);
	hp_seperation = sf::Vector2f(9, 5);

	//Position and Scale each of the bars.
	m_hp_bar.setPosition(hp_position);
	m_xp_bar.setPosition(xp_position);

	m_hp.setPosition(hp_position + hp_seperation);
	m_hp.setScale(player->healthRatio(), 1.0f);

	m_xp.setPosition(xp_position + hp_seperation);
	m_xp.setScale(player->experienceRatio(), 1.0f);
}

HUD::~HUD() {

}

void HUD::loadMedia() {
	s_bar = "Assets/Util/HUD_bar.png";
	m_hp_bar.setTexture(ResourceManager<sf::Texture>::instance()->get(s_bar));
	m_xp_bar.setTexture(ResourceManager<sf::Texture>::instance()->get(s_bar));

	s_hp = "Assets/Util/HUD_hp.png";
	m_hp.setTexture(ResourceManager<sf::Texture>::instance()->get(s_hp));

	s_xp = "Assets/Util/HUD_xp.png";
	m_xp.setTexture(ResourceManager<sf::Texture>::instance()->get(s_xp));

	m_gold.setString(std::to_string(player->getGold()));
	m_gold.setFont(ResourceManager<sf::Font>::instance()->get("Assets/Font/Golden Age Shad.ttf"));
	m_gold.setCharacterSize(14.0f);
	m_gold.setColor(sf::Color::Yellow);
	m_gold.setPosition(5, 10);
}

void HUD::update() {
	m_hp.setScale(player->healthRatio(), 1.0f);
	m_gold.setString(std::to_string(player->getGold()));
}

void HUD::render(sf::RenderWindow * w) {
	w->draw(m_hp_bar);
	w->draw(m_hp);

	w->draw(m_xp_bar);
	w->draw(m_xp);

	w->draw(m_gold);
}
