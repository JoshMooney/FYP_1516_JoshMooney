#ifndef _ENTITY_CREATOR_HPP
#define _ENTITY_CREATOR_HPP
#include "stdafx.h"
#include "Entity.hpp"
#include <vector>

#include "Player.hpp"
#include "Key.hpp"

class EntityCreator {
private:
	float update_dist;
	b2World *m_world;
	vector<Entity *> m_entities;

public:
	//!This enum keeps track of all the different types of enemies the spawner can create.
	enum SPAWN_TYPE {
		KEY, 		//!<
		NPC, 		//!<
		SIGN, 		//!<
	};

	EntityCreator();
	EntityCreator(b2World *world);
	~EntityCreator();

	b2Body* generateBody(SPAWN_TYPE type, sf::Vector2f pos);
	void spawnKey(sf::Vector2f pos, string type, string id, string door);
	/**
	*	@brief 
	*/
	void Cull();
	/**
	*	@brief Calls the update in the Enemy units
	*	@param FTS Fixed Time Step of the game.
	*	@param Player* Pointer to the player.
	*/
	void update(FTS fts, Player *p);
	/**
	*	@brief Renders all of the enemies and blocks in the game world.
	*	@param sf::RenderWindow This is the SFML window to draw to.
	*	@param sf::Time This is the elapse time which is used for animations.
	*/
	void render(sf::RenderWindow *w, sf::Time frames);
	/**
	*	@brief This clears both the enemy list and the block list to get ready for the next level.
	*/
	void clear();
	/**
	*	@brief 
	*/
	Entity* back() {
		return --m_entities.back();
	}
};

#endif