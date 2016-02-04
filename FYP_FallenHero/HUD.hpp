#ifndef _HUD_HPP
#define _HUD_HPP
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Player.hpp"
#include "cLog.hpp"

class HUD {
private:
	string s_bar;
	string s_hp;
	string s_xp;
	sf::Sprite m_hp_bar;
	sf::Sprite m_xp_bar;
	sf::Sprite m_hp;
	sf::Sprite m_xp;
	sf::Vector2f hp_position;
	sf::Vector2f hp_seperation;

	Player *player;
	sf::Text m_play_time;
	sf::Text m_gold;
public:
	HUD();
	HUD(Player* p);
	~HUD();

	void refresh();
	void loadMedia();

	void update();
	void render(sf::RenderWindow *w);
};

#endif