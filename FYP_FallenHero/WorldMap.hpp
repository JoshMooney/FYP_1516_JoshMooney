#ifndef WORLD_MAP_HPP
#define WORLD_MAP_HPP
#include "stdafx.h"

#include <map>
#include <vector>
#include "WorldNode.hpp"
#include "ResourceManager.hpp"
#include "vCamera.hpp"

class WorldMap{
private:
	vector<WorldNode> m_map;
	string s_horz_arc, s_vert_arc;
	vector<sf::Sprite> m_arcs;
	float m_arc_height;
	sf::Vector2f m_map_origin;
	sf::Texture t_player_icon;
	sf::Sprite s_player_icon;
	float m_seperator;
	vCamera m_camera;
	WorldNode m_test_node = WorldNode("TEST", sf::Vector2f(500, 500), false);
	sf::Sprite m_test_arc;
	sf::FloatRect m_bounds;
public:
	enum LEVEL { LVL_1, LVL_2, LVL_3A, LVL_3B, LVL_4, LVL_5, LVL_6 };
	WorldMap();
	WorldMap(sf::Vector2f origin_pos);

	sf::Vector2f getCenter();
	void generateBounds();
	void loadMedia();
	void createMap();
	void createMap(map<string, bool> map_data);
	void addArcs();
	sf::Sprite PlotArc(LEVEL l1, LEVEL l2);
	vector<WorldNode>* getNodes();

	void render(sf::RenderWindow &w);
	WorldNode* getNode(LEVEL l)	{	return &m_map[l];	}
	WorldNode* getNode(string l)	{ return &m_map[strtolvl(l)]; }
	LEVEL strtolvl(string s)	{
		if (s == "LVL_1"){
			return LVL_1;
		}
		else if (s == "LVL_2"){
			return LVL_2;
		}
		else if (s == "LVL_3A"){
			return LVL_3A;
		}
		else if (s == "LVL_3B"){
			return LVL_3B;
		}
		else if (s == "LVL_4"){
			return LVL_4;
		}
		else if (s == "LVL_5"){
			return LVL_5;
		}
		else if (s == "LVL_6"){
			return LVL_6;
		}
		else{
			cLog::inst()->print(2, "WorldMap", "Invaild string to LEVEL conversion, default to LVL_1");
			return LVL_1;
		}
	}
	string lvltostr(LEVEL l)	{
		switch (l){
		case LVL_1:
			return "LVL_1";
		case LVL_2:
			return "LVL_2";
		case LVL_3A:
			return "LVL_3A";
		case LVL_3B:
			return "LVL_3B";
		case LVL_4:
			return "LVL_4";
		case LVL_5:
			return "LVL_5";
		case LVL_6:
			return "LVL_6";
		}
	}
};

#endif