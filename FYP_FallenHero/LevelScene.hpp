#ifndef LEVEL_SCENE_HPP
#define LEVEL_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"

#include <string>
#include <vector>

#include "Player.hpp"
//#include "Platform.hpp"
#include "PauseScreen.hpp"
#include "XBOXController.hpp"
#include "vCamera.hpp"
#include "Exit.hpp"
#include "STP\TMXLoader.hpp"
#include "vHelper.hpp"
#include "Level.hpp"
#include <memory>
#include "Box2D\Box2D.h"
#include <chrono>
#include "Command.hpp"

#include "ContactListener.hpp"
#include "Spawner.hpp"
#include "Skeleton.hpp"
#include "SFMLDebugDraw.h"
#include "SFML\Audio.hpp"
#include "HUD.hpp"
#include "CrumbleBlock.hpp"

#include "GemMine.hpp"

/**
*	@class LevelScene
*	@brief This is the inheriting sub class of Scene and as such overloads the appropratie methods (e.g. handleEvent, render).
*	This class is responcable for updating and rendering everything in the scene while also handlingEvents from the keyboard or
*	input from the controller. The LevelScene has a Level object and is responcible for loading it into memory. The Level scene
*	controls the fixed time step and handling the box2d world.
*/
class LevelScene : public Scene{
private:
	ContactListener contact_listener;
	std::chrono::steady_clock game_clock;
	const std::chrono::duration<long long, std::micro> timePerTick = std::chrono::microseconds(16);
	FTS timeOfLastTick = game_clock.now();

	Player *m_player;
	HUD m_player_HUD;
	bool m_level_complete;
	vCamera m_camera;
	string path, format;
	shared_ptr<Level> m_level;
	sf::Vector2u player_size;
	string level_id;

	const float B2_TIMESTEP = 1.0f / 60.0f;
	const sf::Vector2f GRAVITY = sf::Vector2f(0, 9.81f);
	const int VEL_ITER = 6;
	const int POS_ITER = 2;

	bool isPaused;
	GemMine m_gem_mine;
	Spawner m_spawner;
	sf::Clock m_animation_clock;
	sf::Time frame_elapse;
	string s_background_music;
	bool m_key_pressed;
	bool m_level_quit;
public:

	PauseScreen *m_pause_menu;

	sf::Music m_background_music;		//!<This is the levels background music this is loaded and played from in game. Need some smart way of loading this for the next sprint
	Command* buttonX_;					//!<This is the command class that responds when the X event is needed.
	Command* buttonY_;					//!<This is the command class that responds when the Y event is needed.
	Command* buttonB_;					//!<This is the command class that responds when the B event is needed.
	Command* buttonA_;					//!<This is the command class that responds when the Jump event is needed.

	b2World* m_world;					//!<The box2d world is responsible for handling all of the box2d physics in the game. It also has the ablitity to create and delete box bodies.

	LevelScene();						//!<the default constructor for the level scene
	LevelScene(XBOXController *controller);		//!<Construct the LevelScene and pass it access to the Xbox Controller being used. I believe this has been deprecated.
	LevelScene(string lvl_name, Player *p);		//!<Construct the LevelScene with the level name and player this was a sprint 2 feature that has since been removed.
	~LevelScene();						//!<Deconstructor for the LevelScene

	/**
	*	@brief Is responsible for loading, looping and setting the volume of the background music
	*/
	void loadMedia();
	/**
	*	@brief Updates the player and spawner and calculates the Fixed Time Step(FTS). Also updates the camera to keep it aligned
	*	with the player and checks for the level over state.
	*/
	void update();			
	/**
	*	@brief Draws the scenes objects such as player, blocks and enemies including the foreground and background.
	*	@param sf::RenderWindow is the games render window for drawing to.
	*/	
	void render(sf::RenderWindow &w);
	/**
	*	@brief Handles the keyboard events passed in from the poll event in the main game loop and class the appropratie
	*	command for the key.
	*	@param sf::Event This is the event passed in for interpreting key presses
	*/
	void handleEvent(sf::Event &e);		//Deprecated due to addition of delta time
	/**
	*	@brief Handles the keyboard events passed in from the poll event in the main game loop and class the appropratie
	*	command for the key. This has the addition of delta time used for moving entities
	*	@param sf::Event This is the event passed in for interpreting key presses
	*	@param sf::Time The delta time used for updating
	*/
	void handleEvent(sf::Event &e, sf::Time dt);
	/**
	*	@brief Handles the controller input passed down from the XBOXController class to the scene for interpreting 
	*	from the main Game loop.
	*	@param XBOXController The Xinput wrapper class for interpreting controller input.
	*/
	void handleInput(XBOXController &controller);

	/**
	*	@brief Initalises the Level and calls the appropratie load functions to intialise the level from the string passed in.
	*	@param string The ID of the level name which will be loaded.
	*/
	void loadLevel(string lvl_name);

	bool hasQuit() { return m_level_quit; }

	void setPlayer(Player* p)	{ m_player = p; }		//!<Set the player pointer to the player object passed in.
	vCamera* getCamera()	{ return &m_camera; }       //!<Fetches the Scenes Camera
	string getLevelName() { return level_id; }          //!<Gets the ID associated with the current level.
	void respawnPlayer();                               //!<Resets the player and respawns them at the closes checkpoint
                                                        
	bool isComplete() { return m_level_complete; }      //!<Call to check if the level has finished.
	/**
	*	@brief Refreshes the camera, restarts the game music and repositiions the player.
	*/
	void reset();
};

#endif