#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"
#include "XMLLoader.hpp"
#include "SaveSlot.hpp"
#include <memory>

class MenuScene : public Scene{
private:
	string s_splash, s_main_bg, s_logo, s_save_gui;
	sf::Sprite m_splash_sprt, m_main_bg_sprt, m_logo_sprt, m_save_gui;
	sf::Font m_font;
	vector<sf::Text> menu_text;
	sf::Vector2f m_item_position;
	sf::Vector2f m_item_spacing;
	vector<string> buttons;
	bool m_key_pressed;
	XMLLoader *loader;
	
public:
	SaveSlot *selected_slot;
	enum STATE { SPLASH, MAIN, SAVE_SELECT, OPTIONS, GAME, GAMEOVER, CLOSE};
	enum M_ITEM { M_CONTINUE, M_NEW, M_OPTIONS, M_EXIT };
	enum O_ITEM { O_VOLUME };
	enum SAVESLOTS	{ SLOT_1, SLOT_2, SLOT_3 };

	STATE m_current_state;
	M_ITEM m_current_menu_item;
	O_ITEM m_current_options_item;
	SAVESLOTS m_current_slot;

	MenuScene();
	~MenuScene();

	void update();
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);
	void handleInput(XBOXController &controller);

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void select();
	void back();

	void loadMedia();
	void loadText();
	void setLoader(XMLLoader *l);
	void changeState(STATE s);

	STATE getState()	{ return m_current_state; }
	M_ITEM getMenuPosition()	{ return m_current_menu_item; }
	O_ITEM getOptionsPosition()	{ return m_current_options_item; }

};

#endif