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

class LevelScene : public Scene{
private:
	Player *m_player;
	bool m_level_complete;
	//vector<Platform> m_platform;
	Platform m_plat1;
	Platform m_plat2;
	vCamera m_camera;
	sf::Time m_time_per_frame;
public:
	LevelScene();
	LevelScene(XBOXController *controller);
	LevelScene(string lvl_name, Player *p);
	~LevelScene();

	void update();			//Deprecated due to addition of delta time
	void update(sf::Time dt);			
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);		//Deprecated due to addition of delta time
	void handleEvent(sf::Event &e, sf::Time dt);
	void handleInput(XBOXController &controller);

	void loadLevel(string s);
	void setPlayer(Player* p)	{ m_player = p; }
	vCamera* getCamera()	{ return &m_camera; }

	void createPlatforms(b2World *l_world);
	bool isComplete() { return m_level_complete; }
};

#endif