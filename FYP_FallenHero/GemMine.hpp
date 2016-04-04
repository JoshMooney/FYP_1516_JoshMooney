#ifndef _GEM_MINE_HPP
#define _GEM_MINE_HPP
#include "stdafx.h"
#include "Gem.hpp"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "Player.hpp"
#include <map>
#include "CrumbleBlock.hpp"

/**
*	@class GemMine
*	@brief This is the Factory for generating Gems for the levels. From 
*	here the Gems box bodies are created here and passed into the Gem objects
*	which are also updated and rendered here. This is similar to the Spawner 
*	class for the Enemies
*	@see Spawner
*/
class GemMine {
private:
	float distanceToPlayer(sf::Vector2f entity, sf::Vector2f player);
	float update_dist;
	b2World *m_world;
	vector<Gem *> m_cart;
	vector<Gem::TYPE> m_ore;
	map<Gem::TYPE, sf::IntRect> m_gem_chart;
	map<Gem::TYPE, float> m_gem_probablity;
public:
	//!This is the default constructor for the gem mine 
	GemMine()	{		}
	/**
	*	@brief The overloaded constructor for the Gem Spawner
	*	@param b2World The box2d world for creating bodues.
	*/
	GemMine(b2World *world);

	/**
	*	@brief This function creates a gem for a block when it is destroyed it uses the information of
	*	the block to generate the approprate gem. The spawner will use this to create gems for blocks.
	*	@param CrumbleBlock::TYPE The Type of block the gem comes from.
	*	@param CrumbleBlock::SIZE size The size of the gem can be used and taken into account when spawning
	*	@param sf::Vector2f The posiiton of the block
	*	@see Spawner
	*/
	void SpawnBlock(CrumbleBlock::TYPE type, CrumbleBlock::SIZE size, sf::Vector2f pos);
	/**
	*	@brief 
	*	@param 
	*/
	void SpawnChest(sf::Vector2f pos);
	/**
	*	@brief This is the default spawn gem method. The Parse Level_data method in the Level class
	*	will use this method for spawning inital gems.
	*	@param Gem::TYPE The type of gem to be.
	*	@param sf::Vector2f The position of the gem
	*	@param bool Whether its effected by gravity
	*	@see Level::GenerateLevelItems
	*/
	void SpawnGem(Gem::TYPE type, sf::Vector2f pos, bool grav);
	/**
	*	@brief This is the default spawn gem method. The Parse Level_data method in the Level class
	*	will use this method for spawning inital gems.
	*	@param Gem::TYPE The type of gem to be.
	*	@param sf::Vector2f The position of the gem
	*	@param bool Whether its effected by gravity
	*	@see Level::GenerateLevelItems
	*/
	void SpawnGem(Gem::TYPE type, sf::Vector2f pos, bool grav, bool dir);
	/**
	*	@brief Takes a type of unit to spawn and creates the appropreate body for that class
	*	and returns it.
	*	@param SPAWN_TYPE The type of body to spawn.
	*	@return b2Body* The body post generation.
	*/
	b2Body* GenerateBody(Gem::TYPE type, bool grav);
	/**
	*	@brief If the despawn flag is rasied then the object is no longer used and does not need
	*	to be rendered and updated these Blocks will be destroyed
	*/
	void DespawnObject();
	/**
	*	@brief If the despawn flag is rasied then the object is no longer used and does not need
	*	to be rendered and updated these units will be destroyed
	*/
	void CullInActiveGems();
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