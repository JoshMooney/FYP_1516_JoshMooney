#ifndef LEVEL_SCENE_HPP
#define LEVEL_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"

#include <string>
#include <vector>
#include "Player.hpp"
#include "Platform.hpp"

class LevelScene : public Scene{
private:
	Player *m_player;
	bool m_level_active;
	//vector<Platform> m_platform;
	Platform m_plat1;
	Platform m_plat2;
public:
	LevelScene();
	LevelScene(string lvl_name, Player *p);
	~LevelScene();

	void update();			//Deprecated due to addition of delta time
	void update(sf::Time dt);			
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);		//Deprecated due to addition of delta time
	void handleEvent(sf::Event &e, sf::Time dt);
	void handleInput();

	void loadLevel(string s);
	void setPlayer(Player* p)	{ m_player = p; }

	void createPlatforms(b2World *l_world);
};

#endif