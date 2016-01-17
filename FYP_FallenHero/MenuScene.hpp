#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"
#include "XMLLoader.hpp"
#include "SaveSlot.hpp"
#include <memory>

#define SaveText vector<sf::Text>

class MenuScene : public Scene{
private:
	string s_splash, s_main_bg, s_logo, s_save_gui, s_save_banner, s_erase_banner;
	sf::Sprite m_splash_sprt, m_main_bg_sprt, m_logo_sprt, m_save_gui, m_save_banner, m_erase_banner;
	sf::Font m_font;
	vector<sf::Text> menu_text;
	sf::Vector2f m_item_position;
	sf::Vector2f m_item_spacing;
	vector<string> buttons;
	bool m_key_pressed;
	XMLLoader *loader;				//Loader for the save_data.xml
	sf::Sound move_sound;
	sf::Vector2f m_banner_pos, m_banner_sep;		//The (Currently) Yellow banner that surronds the highlighted save slot
	vector<SaveText> m_save_text;		//The SaveSlot Translated into sf::Text basicly
	sf::Text m_save_select_text, m_erase_select_text;
public:
	SaveSlot *selected_slot;
	enum STATE { SPLASH, MAIN, SAVE_SELECT, NEW, OPTIONS, GAME, GAMEOVER, CLOSE};
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
	void generateSaveText();
};

#endif