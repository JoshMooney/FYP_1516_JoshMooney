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

class Game {
private:
	XBOXController m_xbox_controller;
	const float B2_TIMESTEP = 1.0f / 60.0f;
	const b2Vec2 GRAVITY = b2Vec2(0, 5.0f);
	const int VEL_ITER = 6;
	const int POS_ITER = 2;

	Player *m_player;

	sf::Clock m_delta_clock;
	sf::Time m_delta_time;
	sf::Time m_time_per_frame;
	sf::Time m_frame_time;
public:
	enum STATE { MENU, LEVEL, WORLD };
	STATE m_current_state;

	bool isRunning;
	sf::RenderWindow* m_window;
	b2World* m_world;

	//Scenes
	MenuScene *m_menu_scene;
	LevelScene *m_level_scene;
	WorldScene *m_world_scene;
	Scene *m_current_scene;

	Game();
	~Game();

	void run();
	void render();

	void createPlayer();
};

#endif