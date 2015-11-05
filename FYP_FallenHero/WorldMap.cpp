#include "stdafx.h"
#include "WorldMap.hpp"
#include <vector>

WorldMap::WorldMap(){}
WorldMap::WorldMap(sf::Vector2f origin_pos){
	m_map_origin = origin_pos;
	loadMedia();
	createMap();

	if (!t_player_icon.loadFromFile("Assets/World/player_icon.png"))
		cLog::inst()->print(1, "WorldMap", "Player Icon texture could not be loaded");
	s_player_icon.setScale(.25f, .25f);
	s_player_icon.setTexture(t_player_icon);
	s_player_icon.setPosition(200, 200);
}
WorldMap::WorldMap(sf::Vector2f origin_pos, sf::Texture node){
	m_map_origin = origin_pos;
	loadMedia();
	createMap();

	if (!t_player_icon.loadFromFile("Assets/World/player_icon.png"))
		cLog::inst()->print(1, "WorldMap", "Player Icon texture could not be loaded");
	s_player_icon.setScale(.25f, .25f);
	s_player_icon.setTexture(node);
	s_player_icon.setPosition(200, 200);
}

void WorldMap::loadMedia(){
	if (!t_horz_arc.loadFromFile("Assets/World/arc_horz.png"))
		cLog::inst()->print(1, "WorldMap", "Arc texture could not be loaded");
	if (!t_vert_arc.loadFromFile("Assets/World/arc_vert.png"))
		cLog::inst()->print(1, "WorldMap", "Arc texture could not be loaded");

}
void WorldMap::createMap(){/*
	m_map.push_back(WorldNode("lvl_1", sf::Vector2f(0 + m_map_origin.x, 0 + m_map_origin.y), false));
	m_map.push_back(WorldNode("lvl_2", sf::Vector2f(75 + m_map_origin.x, 0 + m_map_origin.y), false));
	m_map.push_back(WorldNode("lvl_3b", sf::Vector2f(75 + m_map_origin.x, -75 + m_map_origin.y), false));
	m_map.push_back(WorldNode("lvl_3a", sf::Vector2f(75 + m_map_origin.x, 75 + m_map_origin.y), false));
	m_map.push_back(WorldNode("lvl_4", sf::Vector2f(150 + m_map_origin.x, 75 + m_map_origin.y), false));
	m_map.push_back(WorldNode("lvl_5", sf::Vector2f(150 + m_map_origin.x, 0 + m_map_origin.y), false));
	m_map.push_back(WorldNode("lvl_6", sf::Vector2f(225 + m_map_origin.x, 0 + m_map_origin.y), false));
	m_map.push_back(WorldNode("lvl_7", sf::Vector2f(300 + m_map_origin.x, 0 + m_map_origin.y), false));
	*/
	addArcs();
}
sf::Vector2f WorldMap::findArcPosition(WorldNode* node){
	sf::Vector2f arc_pos;
	sf::Vector2f node_pos = node->m_sprite.getPosition();
	sf::Vector2u node_size = node->m_texture.getSize();
	arc_pos = sf::Vector2f(node_pos.x + (node_size.x / 2), node_pos.y + (node_size.y / 2));

	return arc_pos;
}
void WorldMap::addArcs(){/*
	vector<WorldNode *> l_arcs, l_default_arcs;
	sf::Sprite l_sprite;
	sf::Vector2f l_pos;

	l_arcs.push_back(NULL);
	l_arcs.push_back(NULL);
	l_arcs.push_back(NULL);
	l_arcs.push_back(NULL);
	l_default_arcs = l_arcs;
	
	//Set up Neighbouring Nodes
	l_arcs[WorldNode::NORTH] = NULL;
	l_arcs[WorldNode::SOUTH] = NULL;
	l_arcs[WorldNode::EAST] = &m_map[LVL_2];
	l_arcs[WorldNode::WEST] = NULL;
	//Add and push Arc
	m_map[LVL_1].addNeighbours(l_arcs);
	l_sprite.setTexture(t_horz_arc);
	l_sprite.setPosition(findArcPosition(&m_map[LVL_1]));
	m_arcs.push_back(l_sprite);
	//Clear Arcs to Default
	l_arcs = l_default_arcs;

	l_arcs[WorldNode::NORTH] = &m_map[LVL_3B];
	l_arcs[WorldNode::SOUTH] = &m_map[LVL_3A];
	l_arcs[WorldNode::EAST] = NULL;
	l_arcs[WorldNode::WEST] = NULL;
	m_map[LVL_2].addNeighbours(l_arcs);
	l_sprite.setTexture(t_vert_arc);
	l_sprite.setPosition(findArcPosition(&m_map[LVL_2]));
	m_arcs.push_back(l_sprite);

	l_sprite.setTexture(t_vert_arc);
	l_sprite.setPosition(findArcPosition(&m_map[LVL_2]));
	m_arcs.push_back(l_sprite);
	l_arcs = l_default_arcs;

	l_arcs[WorldNode::NORTH] = NULL;
	l_arcs[WorldNode::SOUTH] = NULL;
	l_arcs[WorldNode::EAST] = &m_map[LVL_4];
	l_arcs[WorldNode::WEST] = NULL;
	m_map[LVL_3A].addNeighbours(l_arcs);
	l_sprite.setTexture(t_horz_arc);
	l_sprite.setPosition(findArcPosition(&m_map[LVL_3A]));
	m_arcs.push_back(l_sprite);
	l_arcs = l_default_arcs;

	l_arcs[WorldNode::NORTH] = &m_map[LVL_5];
	l_arcs[WorldNode::SOUTH] = NULL;
	l_arcs[WorldNode::EAST] = NULL;
	l_arcs[WorldNode::WEST] = NULL;
	m_map[LVL_4].addNeighbours(l_arcs);
	l_sprite.setTexture(t_vert_arc);
	l_sprite.setPosition(findArcPosition(&m_map[LVL_4]));
	m_arcs.push_back(l_sprite);
	l_arcs = l_default_arcs;

	l_arcs[WorldNode::NORTH] = NULL;
	l_arcs[WorldNode::SOUTH] = NULL;
	l_arcs[WorldNode::EAST] = &m_map[LVL_6];
	l_arcs[WorldNode::WEST] = NULL;
	m_map[LVL_5].addNeighbours(l_arcs);
	l_sprite.setTexture(t_horz_arc);
	l_sprite.setPosition(findArcPosition(&m_map[LVL_5]));
	m_arcs.push_back(l_sprite);
	l_arcs = l_default_arcs;
	*/
	/* Notes
	l_arcs[WorldNode::DIRECTION::NORTH] = NULL;
	l_arcs[WorldNode::DIRECTION::SOUTH] = NULL;
	l_arcs[WorldNode::DIRECTION::EAST] = NULL;
	l_arcs[WorldNode::DIRECTION::WEST] = NULL;
	m_map[LVL_1].addNeighbours(l_arcs);
	l_arcs.clear();
	*/

}
WorldNode* WorldMap::getNode(LEVEL lvl){
	return &(m_map[lvl]);
}
vector<WorldNode>* WorldMap::getNodes(){
	return &m_map;
}

void WorldMap::render(sf::RenderWindow &w){
	/*
	for (int i = 0; i < m_arcs.size() - 1; i++){
		w.draw(m_arcs[i]);
	}

	for (int i = 0; i < m_map.size() - 1; i++){
		w.draw(m_map[i]);
	}
	*/

	w.draw(s_player_icon);
	m_test_node.render(w);
}