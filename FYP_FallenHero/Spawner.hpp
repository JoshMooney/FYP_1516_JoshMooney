#ifndef _SPAWNER_HPP
#define _SPAWNER_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "Enemy.hpp"
#include "Skeleton.hpp"
#include "CrumbleBlock.hpp"

#include "Player.hpp"

/**
*	@class Spawner
*	@brief This class is responible for creating the enemies in the game. These enemies
*	are pushed back onto a list and are updated and rendered from inside here. This class 
*	currently also creates the CrumbleBlock objects also.
*	@see CrumbleBlock
*	@see Skeleton
*	@see Weed
*	@see Flyer
*/
class Spawner {
private:
	float distanceToPlayer(sf::Vector2f entity, sf::Vector2f player);
	float update_dist;
	b2World *m_world;

	Skeleton* prototype_Skeleton;
	vector<Enemy *> m_enemies;
	vector<CrumbleBlock *> m_blocks;

public:
	//!This enum keeps track of all the different types of enemies the spawner can create.
	enum SPAWN_TYPE { 
	SKELETON 		//!<Spawn type of a Skeleton
	};
	//!Default constructor for the spawner class
	Spawner()	{		}
	/**
	*	@brief Creates the Spawner with a pointer to the world for creating all of the 
	*	required boxbodies.
	*	@param b2World* The Box2D world.
	*/
	Spawner(b2World *world);
	//!Default constructor for the spawner class
	~Spawner();

	/**
	*	@brief Takes a type of unit to spawn and creates the appropreate body for that class
	*	and returns it.
	*	@param SPAWN_TYPE The type of body to spawn.  
	*	@return b2Body* The body post generation.
	*/
	b2Body* GenerateBody(SPAWN_TYPE type);

	/**
	*	@brief Calls the generate body function and pushes the new body onto the entity list
	*	@param sf::Vector2f The position to spawn the Skeleton.
	*/
	void SpawnSkeleton(sf::Vector2f pos);
	/**
	*	@brief Creates the appropreate body for the Block and pushes it onto a vector of blocks
	*	@param sf::Vector2f This position to spawn the Skeleton at.
	*	@param CrumbleBlock::TYPE The Type of block to spawn. 
	*	@param CrumbleBlock::SIZE The 
	*/
	void SpawnBlock(sf::Vector2f pos, CrumbleBlock::TYPE t, CrumbleBlock::SIZE s);

	/**
	*	@brief Checks for any dead body flags in the entity list and destructs them with 
	*	the box2d world.
	*/
	void CullBodies();
	/**
	*	@brief If the despawn flag is rasied then the object is no longer used and does not need
	*	to be rendered and updated these Blocks will be destroyed
	*/
	void DespawnObject();
	/**
	*	@brief If the despawn flag is rasied then the object is no longer used and does not need
	*	to be rendered and updated these units will be destroyed
	*/
	void CullInActiveEnemies();

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
	void render(sf::RenderWindow &w, sf::Time frames);
	/**
	*	@brief This clears both the enemy list and the block list to get ready for the next level.
	*/
	void clear();
};

#endif
