#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "stdafx.h"

#include "Player.hpp"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "ResourceManager.hpp"
#include "Thor\Animations.hpp"
#include "cLog.hpp"
#include <string>
#include "vHelper.hpp"

/**
*	@class Enemy
*	@brief This is the base Enemy class for every type of enemy, This class also helps the 
*	CrumbleBlock class possible as it is considered an enemy due to its need to animated and 
*	be hit by player. The Enemy class is abstract due to its pure virtual functions such as
*	update and redner etc. This functions must be overrided in any derived classes.
*/
class Enemy : public sf::Sprite {
public:
	int e_hp;			//!<Health points of the Enemy
	string e_texture;   //!<The string of the texture being loaded in
	bool e_body_active; //!<bool flag for weather the body is alive or not.
	bool e_can_despawn; //!<bool flag for weather the enemey can be despawned or not
	b2Body *e_box_body; //!<The box body attached to the enemy for handling physics
	bool e_direction;   //!<A bool to represent direction if 1 the character is looking right and if 0 the character is looking left
	bool e_sword_col;   //!<This is the flag for weather the enemy is colliding with the players sword box.
	bool is_hit;        //!<If the enemy is hit or not

	/**
	*	@brief This pure virtual function for updating the enemy objects and must be
	*	overloaded in any derived classes.
	*	@param FTS This is the Fixed Time Step passed to the enemy for moving within delta time
	*/
	virtual ~Enemy() {
		cLog::inst()->print("Enemy Deconstructor called");
		//e_box_body->GetWorld()->DestroyBody(e_box_body);
	}

	virtual void update(FTS fts, Player *p) = 0;	
	/**
	*	@brief This pure virtual function for rendering the enemy object and must be
	*	overloaded in any derived classes.
	*	@param sf::RenderWindow This is the SFML window being rendered to.
	*	@param sf::Time This is for updating and rendering the animation component.
	*/
	virtual void render(sf::RenderWindow &w, sf::Time frames) = 0;
	/**
	*	@brief This pure virtual function for alineing the sprite to the box body attached 
	*	to the enemy object and must be	overloaded in any derived classes.
	*/
	virtual void alineSprite() = 0;
	/**
	*	@brief This pure virtual function for taking dameage and losting hp  
	*	and must be	overloaded in any derived classes.
	*/
	virtual void TakeDamage() = 0;
	/**
	*	@brief This pure virtual function for dieing and must be overloaded in any derived 
	*	classes.
	*/
	virtual void Die() = 0;
	/**
	*	@brief This pure virtual function for getting a SFML bounding box representing the enemy
	*/
	virtual sf::FloatRect getBounds() = 0;

	virtual sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }	//!<Fetches the center of the Enemy
	bool isAlive() { return e_body_active; }            //!<Fetch whether the body is active or not
	bool canDespawn() { return e_can_despawn; }         //!<Fetch whether the Enemy can be Despawned or not
	void setActive(bool b) { e_body_active = b; }       //!<Set the Body active flag
	void setCollidingSword(bool b) { e_sword_col = b; } //!<Set the colliding with sword flag
	bool isCollidingSword() { return e_sword_col; }		//!<Returns whether or not the sword is colliding
};

#endif