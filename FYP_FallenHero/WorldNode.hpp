#ifndef WORLD_NODE_HPP
#define WORLD_NODE_HPP
#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "ResourceManager.hpp"

#include <string>
#include <map>

/**
*	@class WorldNode
*	@brief This is a world node to be used by the world map to make the overworld level select.
*	A node is responcable for knowing about it neighbours, what is unlocked after finishing the
*	level and an ID to identify the level the node is associated with.
*/
class WorldNode : public sf::Sprite {
public:
	map<string, WorldNode*> m_neighbouring_nodes;	//!<A map of directions to WorldNodes will identify the neighboursing nodes of the current node. 
	WorldNode* m_next_lvl;                          //!<The next level to be unlocked after this one is complete.
	string s_texture;                               //!<A string to the path of the texture which will be used by the resourcemanager to load the asset.
	string m_lvl_id;                                //!<String for level id, the name of the level.
	bool m_is_locked;                               //!<Whether or not the level is locked.
	bool m_is_complete;                             //!<Whether or not the level is complete.

	/**
	*	@brief This is the default constructor for the world node taking the bare minimum of
	*	requirements for the world node creation.
	*	@param id The Name of the level doubles up as an identifier
	*	@param pos The position to spawn the Node at.
	*	@param locked if the level is locked or not.
	*/
	WorldNode(string id, sf::Vector2f pos, bool locked){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = false;
		setPosition(pos);
		loadMedia();
	}
	/**
	*	@brief This is the overloaded constructor for the world node taking the bare minimum of
	*	requirements for the world node creation, in addition to the completion bool.
	*	@param id The Name of the level doubles up as an identifier
	*	@param pos The position to spawn the Node at.
	*	@param locked if the level is locked or not.
	*	@param complete if the level is complete or not.
	*/
	WorldNode(string id, sf::Vector2f pos, bool locked, bool complete){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = complete;
		setPosition(pos);
		loadMedia();
	}
	/**
	*	@brief This is another overloaded constructor for the world node taking the all of
	*	requirements for the world node creation.
	*	@param id The Name of the level doubles up as an identifier
	*	@param pos The position to spawn the Node at.
	*	@param locked if the level is locked or not.
	*	@param complete if the level is complete or not.
	*	@param text The file path to the texture for loading custom textures for levels.
	*/
	WorldNode(string id, sf::Vector2f pos, bool locked, bool complete, string text){
		m_lvl_id = id;
		m_is_locked = locked;
		m_is_complete = complete;
		setPosition(pos);
		s_texture = text;
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	}

	/**
	*	@brief This unlocks the node and loads any new media it might need.
	*/
	void unlock() {
		m_is_locked = false;
		loadMedia();
	}
	/**
	*	@brief Loads a texture depending on if the level is locked or not.
	*/
	void loadMedia(){
		if (m_is_locked) {
			s_texture = "Assets/World/node_locked.png";
			setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		}
		else {
			s_texture = "Assets/World/node.png";
			setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		}

	}
	/**
	*	@brief This checks for neightbouring nodes in the direction passed in.
	*	@param string of the direction to check for.
	*	@return bool if the neightbour exists or not.
	*/
	bool checkNeighbout(string n){
		if (m_neighbouring_nodes[n] != nullptr)
			return true;
		return false;
	}
	/**
	*	@brief This fetches the neighbouring node of the current node with a string for identifying
	*	the direction.
	*	@param string The direction of the neightbouring node
	*	@return WorldNode The neighbouring node. 
	*/
	WorldNode* getNeightbourNode(string s){
		return m_neighbouring_nodes[s];
	}
	/**
	*	@brief This fetches the center of the current node.
	*	@return sf::Vector2f The Center of the node. 
	*/
	sf::Vector2f getCenter()	{
		s_texture = "Assets/World/node.png";
		sf::Vector2u size =	ResourceManager<sf::Texture>::instance()->get(s_texture).getSize();
		return sf::Vector2f(getPosition().x + size.x / 2, getPosition().y + size.y / 2);
	}
};

#endif