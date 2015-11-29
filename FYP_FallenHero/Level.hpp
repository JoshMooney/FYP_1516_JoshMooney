#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "STP\TMXLoader.hpp"
/*
#include "tmx\MapLoader.h"
#include "tmx\tmx2box2d.h"
#include <tmx/DebugShape.h>*/
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
	//shared_ptr<tmx::TileMap> tiled_map;
	int tile_size;
	//shared_ptr<tmx::MapLoader> ml;

	vector<Platform> m_platform_data;
public:
	Level();
	Level(string s, b2World *world);
	~Level();

	void render(sf::RenderWindow &w);
	void ParseMapLayers(b2World *world);
	//void CreateTerrain(b2World *world, tmx::MapLayer layer);

	void loadMap(string lvl_name);
	//shared_ptr<tmx::TileMap> tiledMap() { return tiled_map; }
};

#endif