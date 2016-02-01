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
	string s_splash, s_main_bg, s_logo, s_save_gui, s_save_banner, s_erase_banner, s_options_gui;
	sf::Sprite m_splash_sprt, m_main_bg_sprt, m_logo_sprt, m_save_gui, m_save_banner, m_erase_banner, m_options_gui;
	sf::Font m_font;						//!<
	vector<sf::Text> menu_text;             //!<
	sf::Vector2f m_item_position;           //!<
	sf::Vector2f m_item_spacing;            //!<
	vector<string> buttons;                 //!<
	bool m_key_pressed;                     //!<
	XMLLoader *loader;						//!<Loader for the save_data.xml
	sf::Sound move_sound;					//!<
	sf::Vector2f m_banner_pos;				//!<The (Currently) Yellow banner that surronds the highlighted save slot
	sf::Vector2f m_banner_sep;				//!<
	vector<SaveText> m_save_text;			//!<The SaveSlot Translated into sf::Text basicly
	sf::Text m_save_select_text;			//!<
	sf::Text m_erase_select_text;			//!<

	string s_move_down;
	string s_move_up;
	string s_select;
	string s_bump;
	string s_background_music;
	sf::Sound m_move_down;
	sf::Sound m_move_up;
	sf::Sound m_select;
	sf::Sound m_bump;
	
public:
	sf::Music m_background_music;
/**
	*	@brief 
	*/
	SaveSlot *selected_slot;
	/**
	*	@brief 
	*	@var STATE::SPLASH
	*	
	*	@var STATE::MAIN
	*
	*	@var STATE::SAVE_SELECT
	*
	*	@var STATE::NEW
	*
	*	@var STATE::OPTIONS
	*
	*	@var STATE::GAME
	*
	*	@var STATE::GAMEOVER
	*
	*	@var STATE::CLOSE
	*
	*/
	enum STATE { SPLASH, MAIN, SAVE_SELECT, NEW, OPTIONS, GAME, GAMEOVER, CLOSE};
	/**
	*	@brief 
	*	@var M_ITEM::M_CONTINUE
	*
	*	@var M_ITEM::M_NEW
	*
	*	@var M_ITEM::M_OPTIONS
	*
	*	@var M_ITEM::M_EXIT
	*
	*/
	enum M_ITEM { M_CONTINUE, M_NEW, M_OPTIONS, M_EXIT };
	/**
	*	@brief 
	*	@var O_ITEM::O_VOLUME
	*
	*/
	enum O_ITEM { O_VOLUME };
	/**
	*	@brief 
	*/
	enum SAVESLOTS	{ 
	SLOT_1, 			//!<
	SLOT_2,             //!<
	SLOT_3              //!<
	};

	STATE m_current_state;
	M_ITEM m_current_menu_item;
	O_ITEM m_current_options_item;
	SAVESLOTS m_current_slot;

	/**
	*	@brief 
	*/
	MenuScene();
	/**
	*	@brief 
	*/
	~MenuScene();

	/**
	*	@brief 
	*/
	void update();
	/**
	*	@brief 
	*/
	void render(sf::RenderWindow &w);
	/**
	*	@brief 
	*/
	void handleEvent(sf::Event &e);
	/**
	*	@brief 
	*/
	void handleInput(XBOXController &controller);

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
	void moveRight();
	/**
	*	@brief 
	*/
	void moveLeft();
	/**
	*	@brief 
	*/
	void select();
	/**
	*	@brief 
	*/
	void back();

	/**
	*	@brief 
	*/
	void loadMedia();
	/**
	*	@brief 
	*/
	void loadText();
	/**
	*	@brief 
	*/
	void setLoader(XMLLoader *l);
	/**
	*	@brief 
	*/
	void changeState(STATE s);

	STATE getState()	{ return m_current_state; }						//!<
	M_ITEM getMenuPosition()	{ return m_current_menu_item; }         //!<
	O_ITEM getOptionsPosition()	{ return m_current_options_item; }      //!<
	void generateSaveText();
};

#endif