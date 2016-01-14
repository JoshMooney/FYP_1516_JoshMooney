#ifndef LEVEL_SCENE_HPP
#define LEVEL_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"

#include <string>
#include <vector>

#include "Player.hpp"
#include "Platform.hpp"
#include "XBOXController.hpp"
#include "vCamera.hpp"
#include "Exit.hpp"
#include "STP\TMXLoader.hpp"
#include "vHelper.hpp"
#include "Level.hpp"
#include <memory>
#include "Box2D\Box2D.h"
#include <chrono>

class LevelScene : public Scene{
private:
	std::chrono::steady_clock game_clock;
	const std::chrono::duration<long long, std::micro> timePerTick = std::chrono::microseconds(16);
	FTS timeOfLastTick = game_clock.now();

	Player *m_player;
	bool m_level_complete;
	vCamera m_camera;
	string path, format;
	shared_ptr<Level> m_level;
	sf::Vector2u player_size;
	string level_id;

	const float B2_TIMESTEP = 1.0f / 60.0f;
	const b2Vec2 GRAVITY = b2Vec2(0, 9.81f);
	const int VEL_ITER = 6;
	const int POS_ITER = 2;

	bool isPaused;

public:
	b2World* m_world;

	LevelScene();
	LevelScene(XBOXController *controller);
	LevelScene(string lvl_name, Player *p);
	~LevelScene();

	void update();			//Deprecated due to addition of delta time		
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);		//Deprecated due to addition of delta time
	void handleEvent(sf::Event &e, sf::Time dt);
	void handleInput(XBOXController &controller);

	void loadLevel(string lvl_name);
	void setPlayer(Player* p)	{ m_player = p; }
	vCamera* getCamera()	{ return &m_camera; }
	string getLevelName() { return level_id; }
	void respawnPlayer();

	bool isComplete() { return m_level_complete; }
	void reset();
};

#endif