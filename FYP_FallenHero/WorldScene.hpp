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
public:
	bool m_key_pressed;
	SaveSlot *m_current_slot;
	enum STATE {MAP, EXIT};
	STATE m_current_state;

	WorldScene();
	~WorldScene();

	void loadMedia();
	void update();
	void render(sf::RenderWindow &w);
	void handleEvent(sf::Event &e);
	void handleInput(XBOXController &controller);

	void movePlayer(string direction);
	void select();
	bool LevelSelected() { return has_selected; }
	string getCurrentLevel() { return m_player_icon.getTag(); }
	void reset();
	void checkUnlocks(string lvl_name);
	void generateMapData();
	void loadSaveSlot(SaveSlot * ss);
};

#endif