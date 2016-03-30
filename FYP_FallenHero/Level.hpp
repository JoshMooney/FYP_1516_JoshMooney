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

#include "vCamera.hpp"
#include "Exit.hpp"
#include "Terrain.hpp"
#include "Scenery.hpp"
#include "Spawner.hpp"
#include "ParallaxSprite.hpp"

class Level {
private:
	string path;
	string format;
	int tile_size;
	
	ParallaxSprite scene;

	shared_ptr<tmx::TileMap> tiled_map;
	Exit m_exit;

	vector<Terrain *> terrain_data;			//Terrain of the level
	//vector<Platform> platform_data;			//Platform Data
	vector<ParallaxSprite> scenery_data;			//Platform Data
	//vector<LevelItem> player_data;		//Player Level Data Spawn, Exit, checkpoints.
	//vector<Collectible> level_data;		//Coins, collectibles
	sf::Vector2f m_player_spawn;
	sf::FloatRect bounds;			//This is the bounds of the level
public:
	Scenery scenery;

	Level();
	Level(string s, b2World *world, Spawner *spawner);
	~Level();

	void render(sf::RenderWindow &w, vCamera *cam);

	void ParseMapLayers(b2World *world, Spawner *spawner);
	void CreateTerrain(b2World *world, tmx::ObjectGroup &layer);
	void CreatePlatforms(b2World *world, tmx::ObjectGroup &layer);
	void GeneratePlayerItems(b2World *world, tmx::ObjectGroup &layer);
	void GenerateLevelItems(b2World *world, tmx::ObjectGroup &layer);
	void GenerateSceneryBG(b2World *world, tmx::ObjectGroup &layer);
	void GenerateSceneryFG(b2World *world, tmx::ObjectGroup &layer);

	void GenerateEnemies(b2World *world, tmx::ObjectGroup &layer, Spawner* spawner);
	void GenerateBlocks(b2World *world, tmx::ObjectGroup &layer, Spawner* spawner);

	void Destroy(b2World *world);

	void loadMap(string lvl_name);
	shared_ptr<tmx::TileMap> tiledMap() { return tiled_map; }
	bool hasEnded(sf::FloatRect player) { return m_exit.isCollided(player); }
	sf::Vector2f getSpawn() { return m_player_spawn; }
	void destroy(b2World *world);
	sf::FloatRect Bounds() { return bounds; }
};

#endif