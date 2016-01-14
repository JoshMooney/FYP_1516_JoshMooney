#include "stdafx.h"
#include "WorldMap.hpp"
#include <vector>

WorldMap::WorldMap(){}
WorldMap::WorldMap(sf::Vector2f origin_pos){
	m_seperator = 100;
	m_arc_height = 10;
	m_map_origin = origin_pos;
	loadMedia();
	createMap();

	generateBounds();
}

sf::Vector2f WorldMap::getCenter(){	
	return sf::Vector2f(m_bounds.top + m_bounds.width/2, m_bounds.left + m_bounds.height / 2);
}

void WorldMap::generateBounds() {
	int i = 0;
	int size = m_map.size();
	float xmin = m_map_origin.x;
	float xmax = m_map_origin.x;
	float ymin = m_map_origin.y;
	float ymax = m_map_origin.y;

	for (; i < size; i++) {
		sf::Vector2f pos = m_map[i].getCenter();
		if (pos.x < xmin)
			xmin = pos.x;
		if(pos.x > xmax)
			xmax = pos.x;
		if (pos.y < ymin)
			ymin = pos.y;
		if (pos.y > ymax)
			ymax = pos.y;
	}
	xmin -= m_seperator;
	xmax += m_seperator;
	ymin -= m_seperator;
	ymax += m_seperator;

	m_bounds = sf::FloatRect{ xmin, ymin, xmax, ymax };
}

void WorldMap::loadMedia(){
	s_horz_arc = "Assets/World/arc_horz.png";
	s_vert_arc = "Assets/World/arc_vert.png";

	ResourceManager<sf::Texture>::instance()->get(s_horz_arc);
	ResourceManager<sf::Texture>::instance()->get(s_vert_arc);
}
void WorldMap::createMap(){
	sf::Vector2f nodePosition = m_map_origin + sf::Vector2f(0,0);	//0 ,0
	m_map.push_back(WorldNode("LVL_1", nodePosition, false));		

	nodePosition += sf::Vector2f(m_seperator, 0);		//100 , 0
	m_map.push_back(WorldNode("LVL_2", nodePosition, true));

	nodePosition += sf::Vector2f(0, m_seperator);	//100 , 100
	m_map.push_back(WorldNode("LVL_3A", nodePosition, true));

	nodePosition += sf::Vector2f(0, -2 * m_seperator);		//100 , -100
	m_map.push_back(WorldNode("LVL_3B", nodePosition, true));

	nodePosition += sf::Vector2f(m_seperator, 2 * m_seperator);		//200 , 100
	m_map.push_back(WorldNode("LVL_4", nodePosition, true));

	nodePosition += sf::Vector2f(0, -m_seperator);		//200 , 0
	m_map.push_back(WorldNode("LVL_5", nodePosition, true));

	nodePosition += sf::Vector2f(m_seperator, 0);		//300 , 0
	m_map.push_back(WorldNode("LVL_6", nodePosition, true));

	//nodePosition += sf::Vector2f(m_seperator, 0);		//400 , 0
	//m_map.push_back(WorldNode("lvl_7", nodePosition, false));
	
	addArcs();
}
sf::Sprite WorldMap::PlotArc(LEVEL l1, LEVEL l2){
	string orientation;
	sf::Sprite sprite;
	if (m_map[l1].getCenter().x < m_map[l2].getCenter().x){
		m_map[l1].m_neighbouring_nodes["RIGHT"] = &m_map[l2];
		m_map[l2].m_neighbouring_nodes["LEFT"] = &m_map[l1];
		orientation = s_vert_arc;	//1 to 2

		sf::Vector2f pos = m_map[l1].getCenter();
		sprite.setPosition(sf::Vector2f(pos.x - m_arc_height / 2, pos.y));
	}
	if (m_map[l1].getCenter().x > m_map[l2].getCenter().x){
		m_map[l1].m_neighbouring_nodes["LEFT"] = &m_map[l2];
		m_map[l2].m_neighbouring_nodes["RIGHT"] = &m_map[l1];
		orientation = s_vert_arc;	//2 to 1

		sf::Vector2f pos = m_map[l2].getCenter();
		sprite.setPosition(sf::Vector2f(pos.x - m_arc_height / 2, pos.y));
	}

	if (m_map[l1].getCenter().y < m_map[l2].getCenter().y){
		m_map[l1].m_neighbouring_nodes["DOWN"] = &m_map[l2];
		m_map[l2].m_neighbouring_nodes["UP"] = &m_map[l1];
		orientation = s_horz_arc;	//1 to 2

		sf::Vector2f pos = m_map[l1].getCenter();
		sprite.setPosition(sf::Vector2f(pos.x, pos.y - m_arc_height / 2));
	}
	if (m_map[l1].getCenter().y > m_map[l2].getCenter().y){
		m_map[l1].m_neighbouring_nodes["UP"] = &m_map[l2];
		m_map[l2].m_neighbouring_nodes["DOWN"] = &m_map[l1];
		orientation = s_horz_arc;	//2 to 1

		sf::Vector2f pos = m_map[l2].getCenter();
		sprite.setPosition(sf::Vector2f(pos.x, pos.y - m_arc_height / 2));
	}
	sprite.setTexture(ResourceManager<sf::Texture>::instance()->get(orientation));

	//If the neighbour has one make that one the next level
	m_map[l1].m_next_lvl = &m_map[l2];

	return sprite;
}
void WorldMap::addArcs(){
	sf::Sprite l_horz, l_vert;
	l_horz.setTexture(ResourceManager<sf::Texture>::instance()->get(s_horz_arc));
	l_vert.setTexture(ResourceManager<sf::Texture>::instance()->get(s_vert_arc));
	
	m_arcs.push_back(PlotArc(LVL_1, LVL_2));
	m_arcs.push_back(PlotArc(LVL_2, LVL_3B));
	m_arcs.push_back(PlotArc(LVL_2, LVL_3A));
	m_arcs.push_back(PlotArc(LVL_3A, LVL_4));
	m_arcs.push_back(PlotArc(LVL_4, LVL_5));
	m_arcs.push_back(PlotArc(LVL_5, LVL_6));

	m_map[LVL_6].m_next_lvl = &m_map[LVL_6];	//Final Level in the map gets its next pointer to itself, This could be built upon to point to the next map in the Game Hence world 2
}
vector<WorldNode>* WorldMap::getNodes(){
	return &m_map;
}

void WorldMap::render(sf::RenderWindow &w){
	
	for (int i = 0; i < m_arcs.size(); i++){
		w.draw(m_arcs[i]);
	}

	for (int i = 0; i < m_map.size(); i++){
			w.draw(m_map[i]);
	}
	

	w.draw(s_player_icon);
	//m_test_node.render(w);
}