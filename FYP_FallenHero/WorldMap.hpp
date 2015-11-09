#ifndef WORLD_MAP_HPP
#define WORLD_MAP_HPP
#include "stdafx.h"

#include <vector>
#include "WorldNode.hpp"
#include "ResourceManager.hpp"

class WorldMap{
private:
	enum LEVEL {LVL_1, LVL_2, LVL_3A, LVL_3B, LVL_4, LVL_5, LVL_6};
	vector<WorldNode> m_map;
	string s_horz_arc, s_vert_arc;
	vector<sf::Sprite> m_arcs;
	sf::Vector2f m_map_origin;
	sf::Texture t_player_icon;
	sf::Sprite s_player_icon;

	WorldNode m_test_node = WorldNode("TEST", sf::Vector2f(500, 500), false);
	sf::Sprite m_test_arc;
public:
	WorldMap();
	WorldMap(sf::Vector2f origin_pos);
	WorldMap(sf::Vector2f origin_pos, sf::Texture node);

	void loadMedia();
	void createMap();
	void addArcs();
	sf::Vector2f findArcPosition(WorldNode* node);
	WorldNode* getNode(LEVEL lvl);
	vector<WorldNode>* getNodes();

	void render(sf::RenderWindow &w);
};

#endif