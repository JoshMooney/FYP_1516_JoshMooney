#ifndef WORLD_NODE_HPP
#define WORLD_NODE_HPP
#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "ResourceManager.hpp"

#include <string>
#include <map>

struct WorldNode {
	static const int NORTH = 0;
	static const int SOUTH = 1;
	static const int EAST = 2;
	static const int WEST = 3;

	map<string, WorldNode*> m_neighbouring_nodes;
	string s_texture;
	sf::Sprite m_sprite;
	string m_lvl_id;
	bool m_is_locked;
	bool m_is_complete;

	WorldNode(string id, sf::Vector2f pos, bool locked){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = false;
		m_sprite.setPosition(pos);
		loadMedia();
	}
	WorldNode(string id, sf::Vector2f pos, bool locked, bool complete){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = complete;
		m_sprite.setPosition(pos);
		loadMedia();
	}
	WorldNode(string id, sf::Vector2f pos, bool locked, bool complete, string text){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = complete;
		m_sprite.setPosition(pos);
		s_texture = text;
		m_sprite.setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	}

	void loadMedia(){
		s_texture = "Assets/World/node.png";
		m_sprite.setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	}
	void addNeighbour(string s, WorldNode* n)	{
		m_neighbouring_nodes[s] = n;
	}
	void addNeighbours(vector<WorldNode*> list){
		m_neighbouring_nodes["NORTH"] = list[NORTH];
		if (list[NORTH] != NULL)
			list[NORTH]->addNeighbour("SOUTH", this);

		m_neighbouring_nodes["SOUTH"] = list[SOUTH];
		if (list[SOUTH] != NULL)
			list[SOUTH]->addNeighbour("NORTH", this);

		m_neighbouring_nodes["EAST"] = list[EAST];
		if (list[EAST] != NULL)
			list[EAST]->addNeighbour("WEST", this);

		m_neighbouring_nodes["WEST"] = list[WEST];
		if (list[WEST] != NULL)
			list[WEST]->addNeighbour("EAST", this);
	}

	void render(sf::RenderWindow &w){
		w.draw(m_sprite);
	}
};

#endif