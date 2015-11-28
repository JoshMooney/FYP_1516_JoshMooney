#ifndef WORLD_NODE_HPP
#define WORLD_NODE_HPP
#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "ResourceManager.hpp"

#include <string>
#include <map>

class WorldNode : public sf::Sprite {
public:
	map<string, WorldNode*> m_neighbouring_nodes;
	string s_texture;
	string m_lvl_id;
	bool m_is_locked;
	bool m_is_complete;

	WorldNode(string id, sf::Vector2f pos, bool locked){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = false;
		setPosition(pos);
		loadMedia();
	}
	WorldNode(string id, sf::Vector2f pos, bool locked, bool complete){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = complete;
		setPosition(pos);
		loadMedia();
	}
	WorldNode(string id, sf::Vector2f pos, bool locked, bool complete, string text){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = complete;
		setPosition(pos);
		s_texture = text;
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	}

	void loadMedia(){
		s_texture = "Assets/World/node.png";
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	}
	bool checkNeighbout(string n){
		if (m_neighbouring_nodes[n] != nullptr)
			return true;
		return false;
	}
	WorldNode* getNeightbourNode(string s){
		return m_neighbouring_nodes[s];
	}
	sf::Vector2f getCenter()	{
		s_texture = "Assets/World/node.png";
		sf::Vector2u size =	ResourceManager<sf::Texture>::instance()->get(s_texture).getSize();
		return sf::Vector2f(getPosition().x + size.x / 2, getPosition().y + size.y / 2);
	}
};

#endif