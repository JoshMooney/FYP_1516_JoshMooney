#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "STP\TMXLoader.hpp"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include "cLog.hpp"
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "vCamera.hpp"
#include "Platform.hpp"
#include "Sensor.hpp"
#include "Checkpoint.hpp"

#include "PlatformCreator.hpp"
#include "PointMap.hpp"
#include "NodePlatform.hpp"
#include "Terrain.hpp"
#include "Scenery.hpp"
#include "Spawner.hpp"
#include "GemMine.hpp"
#include "ParallaxSprite.hpp"
#include "ProjectileManager.hpp"

/**
*	@class Level
*	@brief This is a level in raw data. This class is ment to encapsulate all the information required for 
*	a level and makes it avaible to the LevelScene. This class holds the Sceney aka the background and 
*	forground items as well as loads key information for the level from the .tmx file such as Enemies
*	Gold and the CrumbleBlock.
*/
#include <queue>
class Level {
private:
	b2World* m_world;
	string path;
	string format;
	int tile_size;
	
	ParallaxSprite scene;

	shared_ptr<tmx::TileMap> tiled_map;

	vector<Terrain *> terrain_data;			//Terrain of the level
	PointMap m_point_map;
	vector<ParallaxSprite> scenery_data;			//Platform Data
	sf::Vector2f m_player_spawn;
	sf::FloatRect bounds;			//This is the bounds of the level
public:
	Sensor *m_exit;
	//queue<Checkpoint*> m_checkpoints;
	list<Checkpoint*> m_checkpoints_HC;
	list<Checkpoint*> m_checkpoint_list;
	Checkpoint *m_checkpoint;  

	/**
	*	@brief This is the levels scenery this will be loaded into memory from the GenerateSceneryBG 
	*	and GenerateSceneryFG methods respectivly. This data can later be drawn to the screen when
	*	playing the level
	*/
	Scenery scenery;

	Level();					//!<The levels default constructor which has been deprecated 
	/**
	*	@brief The overloaded constructor for the Level class which assignes the level, calls loadMap, initalises the scenery and 
	*	calls the ParseMapLayers method to fully intialise the Level.
	*	@param string is the name of the level.
	*	@param b2World a pointer to the box 2d world for creating bodies.
	*	@param Spawner Entity spawner.
	*/
	Level(string s, b2World *world, Spawner *spawner, GemMine *mine, PlatformCreator *p);
	~Level();					//!<Deconstructor for the Level class

	/**
	*	@brief This method renders the levels components such as the tiled map and the levels exit.
	*	@param sf::RenderWindow The Games render window to be drawn to
	*	@param vCamera The Scenes current camera used for applying parallax effect
	*/
	void render(sf::RenderWindow &w, vCamera *cam, sf::Time frames);

	/**
	*	@brief This is the highest stage of loading the map from .tmx. This method calls the rest
	*	of the parse methods to allow for the method to cycle through the different map layers. Loading 
	*	information into the Level class where appropriate.
	*	@param b2World Is the box2d world, this is needed here as we will be doing alot of boxbody creation here.
	*	@param Spawner This is the handler class for creating and managing the entites and blocks in the level.
	*/
	void ParseMapLayers(b2World *world, Spawner *spawner, GemMine *mine, PlatformCreator *p);
	/**
	*	@brief This steps through the object layer reading in each object and translating it into my c++ OBJ
	*	. This reads the X, Y Width and Height creates the box body using this information and pushes the new 
	*	Terrain object to the terrain_data.
	*	@param b2World Is the box2d world, this is needed as the terrains require bodies to be constructed
	*	@param tmx::ObjectGroup The object layer of which the terrains are located on within the .tmx 
	*/
	void CreateTerrain(b2World *world, tmx::ObjectGroup &layer);
	/**
	*	@brief Steps throught the object layer creating Platforms using the information inside the object 
	*	in the .tmx file and push them back onto the platform_data container.
	*	@param b2World Is the box2d world, this is needed as the platforms require bodies to be constructed
	*	@param tmx::ObjectGroup The object layer of which the platforms are located on within the .tmx 
	*/
	void CreatePlatforms(b2World *world, tmx::ObjectGroup &layer, PlatformCreator *p);
	/**
	*	@brief Steps throught the object layer creating Player interactive items using the information inside the object 
	*	in the .tmx file and push them back onto the player_data container.
	*	@param b2World Is the box2d world, this is needed as the player items need bodies to be made for its instances
	*	@param tmx::ObjectGroup The object layer of which the player items are located on within the .tmx 
	*/
	void GeneratePlayerItems(b2World *world, tmx::ObjectGroup &layer);
	/**
	*	@brief Steps throught the object layer creating Level specific items using the information inside the object 
	*	in the .tmx file and push these new objects back onto the level_data container.
	*	@param b2World Is the box2d world, this is needed as the level items need bodies to be made for its instances
	*	@param tmx::ObjectGroup The object layer of which the level items are located on within the .tmx 
	*/
	void GenerateLevelItems(b2World *world, tmx::ObjectGroup &layer, GemMine* mine, Spawner *spawner);
	/**
	*	@brief Steps throught the object layer creating the scenerys background sprites using the information inside the object 
	*	in the .tmx file and push these new objects onto the scenery class.
	*	@param b2World 
	*	@param tmx::ObjectGroup The object layer of which the background are located on within the .tmx 
	*/
	void GenerateSceneryBG(b2World *world, tmx::ObjectGroup &layer);
	/**
	*	@brief Steps throught the object layer creating the scenerys foreground sprites using the information inside the object 
	*	in the .tmx file and push these new objects onto the scenery class. 
	*	@param b2World 
	*	@param tmx::ObjectGroup The object layer of which the foreground are located on within the .tmx 
	*/
	void GenerateSceneryFG(b2World *world, tmx::ObjectGroup &layer);
	/**
	*	@brief Reads through the object layer creating the Enemies and populating the enemy list within the Spawner class
	*	. The spawner is responcable for creating bodies this method is purely for translating from .tmx to code.
	*	@param b2World Is the box2d world, this is needed as the enemies require bodies to be constructed
	*	@param tmx::ObjectGroup The object layer of which the enemies are located on within the .tmx 
	*	@param Spawner This handler class will be needed for creating the enemies
	*/
	void GenerateEnemies(b2World *world, tmx::ObjectGroup &layer, Spawner* spawner);
	/**
	*	@brief Reads through the object layer creating the CrumbleBlocks and populating the block list within the Spawner class
	*	. The spawner is responcable for creating bodies this method is purely for translating from .tmx to code.
	*	@param b2World Is the box2d world, this is needed as the blocks require bodies to be constructed
	*	@param tmx::ObjectGroup The object layer of which the blocks are located on within the .tmx 
	*	@param Spawner This handler class will be needed for creating the blocks
	*/
	void GenerateBlocks(b2World *world, tmx::ObjectGroup &layer, Spawner* spawner);

	/**
	*	@brief This destroyes all the bodies in the level this includes the terrrian and within the Spawner
	*	@param b2World Is required for deleting box bodies
	*/
	void Destroy(b2World *world);

	/**
	*	@brief Uses STP library functions to load the .tmx tiled map.
	*	@param string This is the name of the level that is about to be loaded
	*/
	void loadMap(string lvl_name);
	shared_ptr<tmx::TileMap> tiledMap() { return tiled_map; }					//!<Fetches the tiled map frpm the Level
	bool hasEnded(sf::FloatRect player) { return m_exit->hasTripped();  }   //!<Bool check for if the level has ended or not
	void fetchSpawn();
	sf::Vector2f getSpawn() { 
		fetchSpawn();
		return m_player_spawn; 
	}                          //!<fetches the next spawn for the player.


	sf::FloatRect Bounds() { return bounds; }									//!<Get the bounds of the level in the format of 
};

#endif