#ifndef WORLD_SCENE_HPP
#define WORLD_SCENE_HPP
#include "stdafx.h"
#include "Scene.hpp"

#include "SFML\Graphics.hpp"
#include "WorldMap.hpp"
#include "PlayerIcon.hpp"
#include "vCamera.hpp"
#include "SimpleGUI.hpp"

class WorldScene : public Scene{
private:
	WorldMap *m_world_map;
	string s_main_bg_text, s_player_icon_text;
	sf::Sprite m_main_bg_sprt, m_player_icon_sprt;
	PlayerIcon m_player_icon;
	bool m_key_pressed;
	bool has_selected;
	vCamera m_camera;
	std::shared_ptr<SimpleGUI> m_gui;
public:
	enum STATE {MAP, EXIT};
	STATE m_current_state;

	WorldScene();
	~WorldScene();

	void update();
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);
	void handleInput(XBOXController &controller);

	void movePlayer(string direction);
	void select();
	bool LevelSelected() { return has_selected; }
	string getCurrentLevel() { return m_player_icon.getTag(); }
	void reset(string s);
	void checkUnlocks(string lvl_name);
};

#endif