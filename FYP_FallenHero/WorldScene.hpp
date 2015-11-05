#ifndef WORLD_SCENE_HPP
#define WORLD_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"

#include "SFML\Graphics.hpp"
#include "WorldMap.hpp"

class WorldScene : public Scene{
private:
	WorldMap m_world_map;
	sf::Texture t_main_bg, t_player_icon;
	sf::Sprite s_main_bg, s_player_icon;
	bool m_key_pressed;
public:
	enum STATE {MAP, EXIT};
	STATE m_current_state;

	WorldScene();
	~WorldScene();

	void update();
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);
	void handleInput();
};

#endif