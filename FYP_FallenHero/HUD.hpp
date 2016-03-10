#ifndef _HUD_HPP
#define _HUD_HPP
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Player.hpp"
#include "cLog.hpp"

/**
*	@class HUD
*	@brief This is a simple hud class for managing the Gold text put
*	on the screen
*/
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
	HUD();					//!<Default constructor for the HUD class
	HUD(Player* p);			//!<The overloaded method which takes the entity it is tracking 
	~HUD();					//!<Deconstructor for the HUD

	/**
	*	@brief Refreshes the HUD and updates all the information within it.
	*/
	void refresh();
	/**
	*	@brief This loads all the assets the HUD requires into memory.
	*/
	void loadMedia();

	/**
	*	@brief Updates the Health and Exp data for the hud and adjusts the bars representing them,
	*/
	void update();
	/**
	*	@brief Draws all the HUD's Items to the window
	*	@param sf::RenderWindow is the window to be rendered to.
	*/
	void render(sf::RenderWindow *w);
};

#endif