#include "stdafx.h"
#include "Level.hpp"
#include <string>

Level::Level() {
	cLog::inst()->print(3, "Level", "Default constructor of level called");
}

Level::Level(string s, b2World *world) {
	path = "Assets/Levels/";
	format = ".tmx";
	tile_size = 32;

	loadMap(s);
	ParseMapLayers(world);
}

/*TEMP*/
struct OBJ {
	int width;
	int height;
	int x;
	int y;

	sf::Vector2f getCenter() { return sf::Vector2f(x + width / 2, y + height / 2); }
};

Level::~Level() {
	
}

void Level::render(sf::RenderWindow &w){
	w.draw(*tiled_map);
	w.draw(m_exit);
}

void Level::ParseMapLayers(b2World * world) {
	//map.GetObjectLayer("Layer Name");
	
	tmx::ObjectGroup lay;

	lay = tiled_map->GetObjectGroup("Terrain");
	CreateTerrain(world, lay);
	tiled_map->GetObjectGroup("Terrain").visible = false;

	lay = tiled_map->GetObjectGroup("Player_Data");
	GeneratePlayerItems(world, lay);

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Platform"));
	//CreatePlatforms(world, layer);

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Level_Data"));
	//GenerateLevelItems(world, layer);


}

void Level::CreateTerrain(b2World * world, tmx::ObjectGroup &layer) {
	int lenght = layer.objects_.size();
	
	for (int i = 0; i < lenght; i++) {
		OBJ object;
		//Dont even ask!!
		string s = layer.objects_[i].GetPropertyValue("x");
		object.x = atoi(s.c_str()) * 32;		//By tile size

		s = layer.objects_[i].GetPropertyValue("y");
		object.y = atoi(s.c_str()) * 32;		//By tile size

		s = layer.objects_[i].GetPropertyValue("w");
		object.width = atoi(s.c_str()) * 32;		//By tile size

		s = layer.objects_[i].GetPropertyValue("h");
		object.height = atoi(s.c_str()) * 32;		//By tile size
		
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody;		//this will be a dynamic body
		sf::Vector2f b2Pos = object.getCenter();

		myBodyDef.position.Set(b2Pos.x, b2Pos.y);		//set the starting position
		myBodyDef.angle = 0;				//set the starting angle
		myBodyDef.userData = "Terrain";
		
		b2Body* box_body = world->CreateBody(&myBodyDef);

		//Define the shape of the body
		b2PolygonShape shape;
		shape.SetAsBox(object.width/2, object.height/2);

		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 0.0f;
		myFixtureDef.friction = 0.0f;
		myFixtureDef.shape = &shape;

		box_body->CreateFixture(&myFixtureDef);
		terrain_data.push_back(box_body);
	}
}

void Level::GeneratePlayerItems(b2World * world, tmx::ObjectGroup & layer) {
	int lenght = layer.objects_.size();
	//for (int i = 0; i < lenght; i++) {
		//if ( TYPE == Checkpoint)	{
		//string type = layer.objects_[i].type_;	//Make this work when recompiling the STP .dll 
		//if (type == "Exit") {
		/*string x = layer.objects_[i].GetPropertyValue("x");
			string y = layer.objects_[i].GetPropertyValue("y"); */
			string x = layer.objects_[1].GetPropertyValue("x");
			string y = layer.objects_[1].GetPropertyValue("y");
			m_exit = Exit(sf::Vector2f(atoi(x.c_str()) * tile_size, atoi(y.c_str()) * tile_size));
		//}
		//if (type == "Spawn") {
			string x1 = layer.objects_[0].GetPropertyValue("x");
			string y2 = layer.objects_[0].GetPropertyValue("y");
			m_player_spawn = sf::Vector2f(atoi(x1.c_str()) * tile_size, atoi(y2.c_str()) * tile_size);
		//}
	//}
}


void Level::loadMap(string lvl_name) {
	tiled_map = make_shared<tmx::TileMap>(path + lvl_name + format);
	tiled_map->ShowObjects(true);
}
