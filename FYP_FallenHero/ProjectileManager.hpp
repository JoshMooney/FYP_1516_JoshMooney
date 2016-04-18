#ifndef _PROJECTILE_MANAGER_HPP
#define _PROJECTILE_MANAGER_HPP
#include "stdafx.h"
#include "Projectile.hpp"

/**
*	@class Projectile Manager
*	@brief
*/
class ProjectileManager {
private:
	b2World *m_world;
	vector<Projectile *> m_projectiles;
public:
	/**
	*	@brief
	*	@param
	*/
	ProjectileManager();
	/**
	*	@brief
	*	@param
	*/
	ProjectileManager(b2World *world);
	/**
	*	@brief
	*	@param
	*/
	~ProjectileManager();

	/**
	*	@brief
	*	@param
	*/
	b2Body* GenerateBody(sf::Vector2f pos);
	/**
	*	@brief
	*	@param
	*/
	b2Body* GenerateBossBody(sf::Vector2f pos);
	/**
	*	@brief
	*	@param
	*/
	void fireBullet(sf::Vector2f pos, sf::Vector2f dir);
	/**
	*	@brief
	*	@param
	*/
	void fire(sf::Vector2f pos, sf::Vector2f dir, Projectile::STATE type);
	/**
	*	@brief
	*	@param
	*/
	void shootBoss(sf::Vector2f pos, sf::Vector2f dir, string type);

	/**
	*	@brief
	*	@param
	*/
	void cull();
	/**
	*	@brief Calls the update in the Projectile unit
	*	@param FTS Fixed Time Step of the game.
	*/
	void update(FTS fts);
	/**
	*	@brief Renders all of the projectiles in the game world.
	*	@param sf::RenderWindow This is the SFML window to draw to.
	*	@param sf::Time This is the elapse time which is used for animations.
	*/
	void render(sf::RenderWindow &w, sf::Time frames);
	/**
	*	@brief This clears both the enemy list and the block list to get ready for the next level.
	*/
	void clear();
};

#endif