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
//#include "STP\TMXLoader.hpp"

#include <tmx\MapLoader.h>
#include <tmx\MapObject.h>
#include <tmx/tmx2box2d.h>

#include <memory>

class LevelScene : public Scene{
private:
	shared_ptr<tmx::MapLoader> ml;
	//shared_ptr<tmx::TileMap> tiled_map;
	Player *m_player;
	bool m_level_active;
	//vector<Platform> m_platform;
	Platform m_plat1;
	Platform m_plat2;
	vCamera m_camera;
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
	
};

#endif