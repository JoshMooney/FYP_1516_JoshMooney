#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"
#include "XMLLoader.hpp"
#include "SaveSlot.hpp"
#include <memory>

#define SaveText vector<sf::Text>

/**
*	@class MenuScene
*	@brief This is the Menu scene for the rendering, updating and mangaing 
*	the menu state of the game
*/
class MenuScene : public Scene{
private:
	string s_splash, s_main_bg, s_logo, s_save_gui, s_save_banner, s_erase_banner, s_options_gui;
	sf::Sprite m_splash_sprt, m_main_bg_sprt, m_logo_sprt, m_save_gui, m_save_banner, m_erase_banner, m_options_gui;
	sf::Font m_font;						
	vector<sf::Text> menu_text;             
	sf::Vector2f m_item_position;           
	sf::Vector2f m_item_spacing;            
	vector<string> buttons;                 
	bool m_key_pressed;                     
	XMLLoader *loader;						
	sf::Sound move_sound;					
	sf::Vector2f m_banner_pos;				
	sf::Vector2f m_banner_sep;				
	vector<SaveText> m_save_text;			
	sf::Text m_save_select_text;			
	sf::Text m_erase_select_text;			

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
	sf::Music m_background_music;		//!<This is the background music for the menu state of the game.
	/**
	*	@brief This is the currently highlighted save slot the player 
	*	has selected
	*/
	SaveSlot *selected_slot;
	//!This is all the different states the menu can be in.
	enum STATE { 
	SPLASH, 		//!<The Splash screen of the game
	MAIN,           //!<The main menu or the menu class
	SAVE_SELECT,    //!<The menu is in the save select view.
	NEW, 			//!<The New game has been choosen and must be initalized
	OPTIONS,   		//!<The menu is in the options screen.
	GAME,           //!<The menu is inactive and the game is running
	GAMEOVER,       //!<The game is over and the menu must display this
	CLOSE           //!<The game needs to be closed
	};
	
	//!All the possible menu items on the main menu
	enum M_ITEM { 
	M_CONTINUE, 	//!<Continue menu item
	M_NEW, 	    	//!<New menu item
	M_OPTIONS, 		//!<Options menu item
	M_EXIT 	    	//!<Exit menu item
	};
	
	//!All the possible menu items on the options menu
	enum O_ITEM { 
	O_VOLUME 		//!<Volume bar options.
	};

	//!All the possile save slots for the player
	enum SAVESLOTS	{ 
	SLOT_1, 			//!<This is save slot 1
	SLOT_2,             //!<This is save slot 2
	SLOT_3              //!<This is save slot 3
	};

	STATE m_current_state;			//!<This is the current state of the Menu
	M_ITEM m_current_menu_item;     //!<Current Menu Item state of the menu
	O_ITEM m_current_options_item;  //!<Current Menu Options state of the menu
	SAVESLOTS m_current_slot;       //!<Current Saveslot state of the menu

	/**
	*	@brief Default constructor of the Menu Class.
	*/
	MenuScene();
	/**
	*	@brief Deconstructor of the Menu scene
	*/
	~MenuScene();

	/**
	*	@brief This updates the menu and keeps it within step of the main Game class
	*/
	void update();
	/**
	*	@brief This renders the scene for the menu
	*	@param sf::RenderWindow This is the SFML window to render to.
	*/
	void render(sf::RenderWindow &w);
	/**
	*	@brief This handles and registers all keyboard input for this scene and responds
	*	appropreatly.
	*	@param sf::Event The Event with the key presses stored within it.
	*/
	void handleEvent(sf::Event &e);
	/**
	*	@brief This handles and registers all XBOXController input for this scene and responds
	*	appropreatly.
	*	@param XBOXController The Controller with the button presses stored within it.
	*/
	void handleInput(XBOXController &controller);

	/**
	*	@brief Move the menu indicator up one, play the appropreate sounds effect and change
	*	change the animation state.
	*/
	void moveUp();
	/**
	*	@brief Move the menu indicator down one, play the appropreate sounds effect and change
	*	change the animation state.
	*/
	void moveDown();
	/**
	*	@brief Move the menu indicator right one, play the appropreate sounds effect and change
	*	change the animation state.
	*/
	void moveRight();
	/**
	*	@brief Move the menu indicator left one, play the appropreate sounds effect and change
	*	change the animation state.
	*/
	void moveLeft();
	/**
	*	@brief This selects the currently hightlighted menu indicator.
	*/
	void select();
	/**
	*	@brief This cchanged the menu scene to the previous scene for backing through menus.
	*/
	void back();

	/**
	*	@brief This loads all the media for the scene into memory for the menu to display there 
	*	textures and sounds.
	*/
	void loadMedia();
	/**
	*	@brief This loads all the sf::Text required for the scene.
	*/
	void loadText();
	/**
	*	@brief Sets the loader the menu should use to load and save the .xml save slots.
	*	@param XMLLoader The loader for saving and loading .xml files.
	*/
	void setLoader(XMLLoader *l);
	/**
	*	@brief This changes the state of the Menu scene for intitalising events and what not.
	*	@param STATE The state to change to.
	*/
	void changeState(STATE s);

	STATE getState()	{ return m_current_state; }						//!<Fetches the current state of the menu 
	M_ITEM getMenuPosition()	{ return m_current_menu_item; }         //!<Fetches the menu position of the current menu item.
	O_ITEM getOptionsPosition()	{ return m_current_options_item; }      //!<Fetches the options menu position of the current options menu item.
	
	/**
	*	@brief This creates the appropreate save data in raw code to save into the .xml file
	*/
	void generateSaveText();
};

#endif