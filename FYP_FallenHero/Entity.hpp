#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include <string>
#include "ResourceManager.hpp"

/**
*	@struct Entity
*	@brief Base class for anything in the game that is an entity and might need
*	hp and a box body e.g. Player and NPC
*/
struct Entity : public sf::Sprite {
	/**
	*	@brief An abstract virtual function meaning this method will have to be overrided
	*	in any inheriting classes
	*/
	virtual void update(FTS fts) = 0;	

	float e_hp;				//!<The Health points of the entity
	float e_max_hp;         //!<The Maximum Health points of the entity
	string e_texture;       //!<A string to the name of the resource and its path location
	bool e_body_active;     //!<A bool to stay if the body is alive or
	b2Body *e_box_body;     //!<The Box2D Body associated with the Entity
};

#endif