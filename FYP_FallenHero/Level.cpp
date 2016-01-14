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

	scene = ParallaxSprite(path + "Backgrounds/Mountains.png", sf::Vector3f(0, 0, 0.5f));

	loadMap(s);
	scenery = Scenery();
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

void Level::render(sf::RenderWindow &w, vCamera *cam){	
	//float x = cam->getX() * scene.getDefaultPosition().z;
	//scene.setPosition(sf::Vector2f(x, scene.getDefaultPosition().y));

	w.draw(*tiled_map);				//Render Tiled Map
	w.draw(m_exit);					//Render Exit point
}

void Level::ParseMapLayers(b2World * world) {
	//map.GetObjectLayer("Layer Name");
	
	tmx::ObjectGroup lay;
	//** Put all of this level loading onto threads to speed up the process **//
	lay = tiled_map->GetObjectGroup("Terrain");
	CreateTerrain(world, lay);
	tiled_map->GetObjectGroup("Terrain").visible = false;

	lay = tiled_map->GetObjectGroup("Player_Data");
	GeneratePlayerItems(world, lay);
	tiled_map->GetObjectGroup("Player_Data").visible = true;

	lay = tiled_map->GetObjectGroup("BG");
	GenerateSceneryBG(world, lay);
	tiled_map->GetObjectGroup("BG").visible = false;

	lay = tiled_map->GetObjectGroup("FG");
	GenerateSceneryFG(world, lay);
	tiled_map->GetObjectGroup("FG").visible = true;

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Platform"));
	//CreatePlatforms(world, layer);

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Level_Data"));
	//GenerateLevelItems(world, layer);


}
void Level::CreateTerrain(b2World * world, tmx::ObjectGroup &layer) {
	int lenght = layer.objects_.size();
	Terrain terrain;

	for (int i = 0; i < lenght; i++) {
		OBJ object;
		string s = layer.objects_[i].GetPropertyValue("x");
		object.x = atoi(s.c_str());		

		s = layer.objects_[i].GetPropertyValue("y");
		object.y = atoi(s.c_str());		

		s = layer.objects_[i].GetPropertyValue("w");
		object.width = atoi(s.c_str());		

		s = layer.objects_[i].GetPropertyValue("h");
		object.height = atoi(s.c_str());		
		
		//terrain->geometry. = sf::FloatRect{}

		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody;		//this will be a dynamic body
		sf::Vector2f b2Pos = object.getCenter();

		myBodyDef.position.Set(b2Pos.x, b2Pos.y);		//set the starting position
		myBodyDef.angle = 0;				//set the starting angle
		myBodyDef.userData = "Terrain";
		
		b2Body* box_body = world->CreateBody(&myBodyDef);

		//Define the shape of the body
		b2PolygonShape shape;
		shape.SetAsBox(object.width / 2, object.height / 2);

		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 0.0f;
		myFixtureDef.friction = 0.0f;
		myFixtureDef.shape = &shape;

		box_body->CreateFixture(&myFixtureDef);

		terrain.body = box_body;
		terrain.geometry = sf::FloatRect{ (float)object.x, (float)object.y, (float)object.width, (float)object.height };
		terrain_data.push_back(terrain);
	}
}
void Level::GeneratePlayerItems(b2World * world, tmx::ObjectGroup &layer) {
	string x, y;
	string type;
	int lenght = layer.objects_.size();

	for (int i = 0; i < lenght; i++) {
		//if (type == "Checkpoint")	{
		string type = layer.objects_[i].GetPropertyValue("label"); 	
		if (type == "Exit") {
			x = layer.objects_[1].GetPropertyValue("x");
			y = layer.objects_[1].GetPropertyValue("y");
			m_exit = Exit(sf::Vector2f(atoi(x.c_str()), atoi(y.c_str())));
		}
		if (type == "Spawn") {
			x = layer.objects_[0].GetPropertyValue("x");
			y = layer.objects_[0].GetPropertyValue("y");
			m_player_spawn = sf::Vector2f(atoi(x.c_str()), atoi(y.c_str()));
		}
	}
}
void Level::GenerateSceneryBG(b2World *world, tmx::ObjectGroup &layer) {
	int lenght = layer.objects_.size();
	string path = "Assets/Levels/Backgrounds/";
	string format = ".png";
	string num;

	for (int i = 0; i < lenght; i++) {
		sf::Vector3f vec3;
		num = layer.objects_[i].GetPropertyValue("x");
		vec3.x = atoi(num.c_str());

		num = layer.objects_[i].GetPropertyValue("y");
		vec3.y = atoi(num.c_str());

		num = layer.objects_[i].GetPropertyValue("z");
		vec3.z = atoi(num.c_str());
		vec3.z /= 10;

		string texture;
		texture = layer.objects_[i].GetPropertyValue("filename");
		scenery.insertBG(ParallaxSprite(path + texture + format, vec3));
	}

	scenery.sortBG();
}
void Level::GenerateSceneryFG(b2World *world, tmx::ObjectGroup &layer) {
	int lenght = layer.objects_.size();
	string path = "Assets/Levels/Foregrounds/";
	string format = ".png";
	string num;

	for (int i = 0; i < lenght; i++) {
		sf::Vector3f vec3;
		num = layer.objects_[i].GetPropertyValue("x");
		vec3.x = atoi(num.c_str());

		num = layer.objects_[i].GetPropertyValue("y");
		vec3.y = atoi(num.c_str());

		num = layer.objects_[i].GetPropertyValue("z");
		vec3.z = atoi(num.c_str());
		vec3.z /= 10;

		string texture;
		texture = layer.objects_[i].GetPropertyValue("filename");
		scenery.insertFG(ParallaxSprite(path + texture + format, vec3));
	}

	scenery.sortFG();
}

void Level::Destroy(b2World *world) {
	int i;
	
	//Destroy Terrain
	for (i = 0; i < terrain_data.size(); i++) {
		world->DestroyBody(terrain_data[i].body);
	}
	terrain_data.clear();
}
void Level::loadMap(string lvl_name) {
	tiled_map = make_shared<tmx::TileMap>(path + lvl_name + format);
	tiled_map->ShowObjects(true);
	
}

void Level::destroy(b2World *world) {
	int i;
	
	//Destroy Each of the B2Bodies assocatied with the Terrain
	for (i = 0; i < terrain_data.size(); i++) {
		world->DestroyBody(terrain_data[i].body);
	}
}
