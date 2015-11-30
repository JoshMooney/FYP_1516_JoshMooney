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

#include "Platform.hpp"
#include "Exit.hpp"

class Level {
private:
	string path;
	string format;
	sf::Vector2u tile_size;
	shared_ptr<tmx::TileMap> tiled_map;

	vector<b2Body*> terrain_data;			//Terrain of the level
	vector<Platform> platform_data;			//Platform Data
	//vector<LevelItem> player_data;		//Player Level Data Spawn, Exit, checkpoints.
	//vector<Collectible> level_data;		//Coins, collectibles
	
public:
	Level();
	Level(string s, b2World *world);
	~Level();

	void render(sf::RenderWindow &w);
	void ParseMapLayers(b2World *world);
	void CreateTerrain(b2World *world, shared_ptr<tmx::ObjectGroup> layer);
	void CreatePlatforms(b2World *world, shared_ptr<tmx::ObjectGroup> layer);
	void GeneratePlayerItems(b2World *world, shared_ptr<tmx::ObjectGroup> layer);
	void GenerateLevelItems(b2World *world, shared_ptr<tmx::ObjectGroup> layer);

	void loadMap(string lvl_name);
	shared_ptr<tmx::TileMap> tiledMap() { return tiled_map; }
};

#endif