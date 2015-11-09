#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"

class MenuScene : public Scene{
private:
	string s_splash, s_main_bg, s_logo;
	sf::Sprite m_splash_sprt, m_main_bg_sprt, m_logo_sprt;
	sf::Font m_font;
	sf::Text m_play_text, m_options_text, m_exit_text;
	sf::Vector2f m_item_position;
	sf::Vector2f m_item_spacing;
	bool m_key_pressed;
public:
	enum STATE { SPLASH, MAIN, OPTIONS, GAME, GAMEOVER, CLOSE};
	enum M_ITEM { M_PLAY, M_OPTIONS, M_EXIT };
	enum O_ITEM { O_VOLUME };

	STATE m_current_state;
	M_ITEM m_current_menu_item;
	O_ITEM m_current_options_item;

	MenuScene();
	~MenuScene();

	void update();
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);
	void handleInput();

	void moveUp();
	void moveDown();
	void select();

	void loadMedia();
	void loadText();

	STATE getState()	{ return m_current_state; }
	M_ITEM getMenuPosition()	{ return m_current_menu_item; }
	O_ITEM getOptionsPosition()	{ return m_current_options_item; }

};

#endif