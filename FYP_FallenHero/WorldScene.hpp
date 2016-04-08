#ifndef WORLD_SCENE_HPP
#define WORLD_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "WorldMap.hpp"
#include "PlayerIcon.hpp"
#include "vCamera.hpp"
#include "SimpleGUI.hpp"
#include "SaveSlot.hpp"
#include "Player.hpp"
#include "Achievement.hpp"

/**
*	@class WorldScene
*	@brief This class is responcable for creating, managing of the map as well as
*	save the game, move the player around the map and loads changes state.
*/

class WorldScene : public Scene{
private:
	WorldMap *m_world_map;
	string s_main_bg_text, s_player_icon_text;
	sf::Sprite m_main_bg_sprt, m_player_icon_sprt;
	PlayerIcon m_player_icon;
	bool has_selected;
	vCamera m_camera;
	std::shared_ptr<SimpleGUI> m_gui;
	map<string, bool> m_map_data;
	string s_bump;
	string s_run_away;
	string s_select;
	string s_background_music;
	sf::Sound m_bump;
	sf::Sound m_run_away;
	sf::Sound m_select;
	sf::Music m_background_music;
	shared_ptr<Achievements> m_achievement_ob;
public:
	bool m_key_pressed;
	SaveSlot *m_current_slot;		//!<This is the current save slot loaded into the game for pulling information for the map and saving to.
	//!The state the map is in, whather a selection has been made or not.
	enum STATE {
		MAP, 						//!<The World Scene is currently on the map and moving around.
		EXIT						//!<The World Scene is currently exiting and needs to change scene.
		};
	STATE m_current_state;			//!<The the current state of the game


	/**
	*	@brief This is the default constructor for the world scene.
	*/
	WorldScene();
	/**
	*	@brief This is the deconstructor for the world scene.
	*/
	~WorldScene();

	/**
	*	@brief This loads all the assets the scene requires for use such as the background image
	*	and all the sounds effects required by the scene.
	*/
	void loadMedia();
	/**
	*	@brief Currently blank the WorldScene doesnt get updated in any way.
	*/
	void update();
	/**
	*	@brief This renders all the assets in the scene, aswell as sets the view of the camera
	*	to the window and reset it before exiting the function.
	*	@param sf::RenderWindow This is the SFML window to render to.
	*/
	void render(sf::RenderWindow &w);
	/**
	*	@brief Handle the keyboard input for the scene
	*	@param sf::Event This is the event to read the keyboard for input
	*/
	void handleEvent(sf::Event &e);
	/**
	*	@brief Handle the Controller input for the scene
	*	@param XBOXController This is the controller to read for input
	*/
	void handleInput(XBOXController &controller);

	/**
	*	@brief Move the player idol in the direction passed into the funtion.
	*	@param string The direction to move the player to.
	*/
	void movePlayer(string direction);
	/**
	*	@brief Select the current level the player idol is standing on, also play the select sound.
	*/
	void select();
	bool LevelSelected() { return has_selected; }					//!<Returns the level thats been selected for changing scenes.
	string getCurrentLevel() { return m_player_icon.getTag(); }     //!<Get the ID of the level the player is standing on.
	void reset();													//!<Resets any variables required for resetting the scene to be used again.
	/**
	*	@brief This function checks the level name as askes the WorldNode if it has a unlock or not.
	*	@param lvl_name This is the name of the level just complete
	*/
	void checkUnlocks(string lvl_name, Player *p, sf::Time lvl_time);
	/**
	*	@brief This generates the new Map data of srings to bool to save the game data when new levels
	*	have been unlocked.
	*/
	void generateMapData();		
	/**
	*	@brief The method takes a SaveSlot and creates a map depending on the information in the save.
	*	@param SaveSlot This is the save slot that needs to be loaded into the map
	*/	
	void loadSaveSlot(SaveSlot * ss);
	/**
	*	@brief 
	*/
	void addLevelTime(sf::Time time);
};

#endif