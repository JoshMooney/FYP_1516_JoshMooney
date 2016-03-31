#pragma once
#ifndef GAME_HPP
#define GAME_GPP

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "Scene.hpp"
#include "LevelScene.hpp"
#include "WorldScene.hpp"
#include "MenuScene.hpp"
#include "Player.hpp"
#include "XBOXController.hpp"
#include "STP\TMXLoader.hpp"
#include "XMLLoader.hpp"
#include <memory>

#include "SFMLDebugDraw.h"

/**
*	@class Game
*	@brief This is the base Game class that is used for creating and running
*	an instance of the game.
*/
class Game {
private:
	SFMLDebugDraw dd;
	shared_ptr<XBOXController> m_xbox_controller;
	XMLLoader *m_loader;
	bool controller_connected, previous_connected;

	Player *m_player;

	sf::Clock m_delta_clock;
	sf::Time m_delta_time;
	sf::Time m_time_per_frame;
	sf::Time m_frame_time;
public:
	//!These are the multiple states the game can possibly be in.
	enum STATE { 
	MENU, 				//!<MENU which represents the MenuScene
	LEVEL, 				//!<LEVEL which represents the LevelScene
	WORLD 				//!<WORLD which represents the WorldScene
	};
	STATE m_current_state;		//!This is the current state of the Game this variable is responcible for managing the state.

	bool isRunning;				//!<If the game is running or not
	sf::RenderWindow* m_window;	//!<This is the window the game will be drawn to.

	//Scenes
	MenuScene *m_menu_scene;		//!<A pointer to the menu scene.
	LevelScene *m_level_scene;      //!<A pointer to the level scene.
	WorldScene *m_world_scene;      //!<A pointer to the world scene.
	Scene *m_current_scene;         //!<This contains the current scene of the game.

	Game();			//!<Default constructor for the game.
	~Game();        //!<Deconstructor for the game.

	void run();		//!<This is the main game loop that the game runs and calls all the methods for running the game.
	void render();	//!<This is the main render method that the game renders all of its entities.

	void createPlayer();		//!<
	bool checkController(); 	//!<Qureries the XBOXController class and checks if the controller is connected.
	void checkSceneChange();	//!<Checks the active scene for completion and if so class goToNextScene
	void goToNextScene(); 		//!<Change States and initalise them appropratly.
};

#endif