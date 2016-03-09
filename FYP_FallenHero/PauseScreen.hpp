#ifndef _PAUSE_SCREEN_HPP
#define _PAUSE_SCREEN_HPP
#include "stdafx.h"

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\Text.hpp"
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "ResourceManager.hpp"

/**
*	@class
*	@brief
*/
class PauseScreen {
private:
	int m_item_count;
	string s_splash, s_title, s_banner;
	sf::Sprite m_splash_sprt, m_title_sprt, m_banner_sprt;
	string s_font;
	bool m_is_pause;
	sf::Vector2f m_begin_list_pos;
	sf::Vector2f m_list_pos;
	int m_y_spacing;
	int m_items_pos;
	vector<sf::Text> m_items;
	sf::Text m_title;
	sf::Vector2f m_title_pos;
	std::vector<sf::Text>::iterator m_current_item;

	string s_move_down;
	string s_move_up;
	string s_select;
	string s_bump;
	sf::Sound m_move_down;
	sf::Sound m_move_up;
	sf::Sound m_select;
	sf::Sound m_bump;
	bool m_key_pressed;
public:
	enum RESULT { NA, RESUME, QUIT};
	RESULT m_result;
	/**
	*	@brief
	*/
	PauseScreen();
	/**
	*	@brief
	*/
	~PauseScreen();

	/**
	*	@brief
	*/
	void addItem(string name);
	/**
	*	@brief
	*/
	bool isPaused();
	/**
	*	@brief
	*/
	void setPaused(bool b);
	/**
	*	@brief
	*/
	void loadMedia();

	/**
	*	@brief
	*/
	void select();
	/**
	*	@brief
	*/
	void moveUp();
	/**
	*	@brief
	*/
	void moveDown();
	/**
	*	@brief
	*/
	RESULT& getResult();

	/**
	*	@brief
	*/
	void update();
	/**
	*	@brief
	*/
	void render(sf::RenderWindow &w, sf::Time &framse);
};
#endif