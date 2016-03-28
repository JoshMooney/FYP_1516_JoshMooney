#include "stdafx.h"
#include "Level.hpp"
#include <string>
#include "vHelper.hpp"

#include <iostream>

Level::Level() {
	cLog::inst()->print(3, "Level", "Default constructor of level called");
}
Level::Level(string s, b2World *world, Spawner *spawner, PlatformCreator *p) {
	path = "Assets/Levels/";
	format = ".tmx";
	tile_size = 32;

	m_point_map = PointMap();

	scene = ParallaxSprite(path + "Backgrounds/Mountains.png", sf::Vector3f(0, 0, 0.5f));

	loadMap(s);
	scenery = Scenery();
	ParseMapLayers(world, spawner, p);
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

void Level::ParseMapLayers(b2World * world, Spawner *s, PlatformCreator *p) {
	//map.GetObjectLayer("Layer Name");
	//Load size of the Map
	int tile_size = 32;
	int w = tiled_map->GetWidth();
	int h = tiled_map->GetHeight();
	
	bounds = { (float)0, (float)0, (float)w * tile_size, (float)h * tile_size };

	tmx::ObjectGroup lay;
	//** Put all of this level loading onto threads to speed up the process **//
	lay = tiled_map->GetObjectGroup("Terrain");
	CreateTerrain(world, lay);
	tiled_map->GetObjectGroup("Terrain").visible = false;

	lay = tiled_map->GetObjectGroup("Player_Data");
	GeneratePlayerItems(world, lay);
	tiled_map->GetObjectGroup("Player_Data").visible = false;

	lay = tiled_map->GetObjectGroup("BG");
	GenerateSceneryBG(world, lay);
	tiled_map->GetObjectGroup("BG").visible = false;

	lay = tiled_map->GetObjectGroup("FG");
	GenerateSceneryFG(world, lay);
	tiled_map->GetObjectGroup("FG").visible = false;

	lay = tiled_map->GetObjectGroup("Enemy_Data");
	GenerateEnemies(world, lay, s);
	tiled_map->GetObjectGroup("Enemy_Data").visible = false;

	lay = tiled_map->GetObjectGroup("Blocks");
	GenerateBlocks(world, lay, s);
	tiled_map->GetObjectGroup("Blocks").visible = false;

	lay = tiled_map->GetObjectGroup("Platform");
	CreatePlatforms(world, lay, p);
	tiled_map->GetObjectGroup("Platform").visible = false;

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Level_Data"));
	//GenerateLevelItems(world, layer);


}
void Level::CreateTerrain(b2World * world, tmx::ObjectGroup &layer) {
	int lenght = layer.objects_.size();
	Terrain *terrain;

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
		sf::Vector2f ter_pos = object.getCenter();

		myBodyDef.position.Set(ter_pos.x / vHelper::B2_SCALE, ter_pos.y / vHelper::B2_SCALE);		//set the starting position
		myBodyDef.angle = 0;				//set the starting angle
		
		b2Body* box_body = world->CreateBody(&myBodyDef);

		//Define the shape of the body
		b2PolygonShape shape;
		shape.SetAsBox((object.width / vHelper::B2_SCALE) / 2, (object.height / vHelper::B2_SCALE) / 2);

		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 0.0f;
		myFixtureDef.friction = 0.5f;
		myFixtureDef.shape = &shape;
		myFixtureDef.userData = "Terrain";

		box_body->CreateFixture(&myFixtureDef);

		terrain = new Terrain();
		terrain->body = box_body;
		terrain->geometry = sf::FloatRect{ (float)object.x, (float)object.y, (float)object.width, (float)object.height };
		terrain_data.push_back(terrain);
		terrain_data.back()->body->SetUserData(terrain_data.back());
	}
}
void Level::CreatePlatforms(b2World * world, tmx::ObjectGroup & layer, PlatformCreator *p) {
	string x, y;
	string type, id;
	sf::Vector2f position;
	int lenght = layer.objects_.size();

	for (int i = 0; i < lenght; i++) {
		string type = layer.objects_[i].GetPropertyValue("type");
		if (type == "Platform") {
			x = layer.objects_[i].GetPropertyValue("x");
			y = layer.objects_[i].GetPropertyValue("y");
			position = sf::Vector2f(atoi(x.c_str()), atoi(y.c_str()));
			
			//id = layer.objects_[i].GetPropertyValue("id");
			p->SpawnPlatform(position);
		}
		if (type == "FadePlatform") {
			x = layer.objects_[i].GetPropertyValue("x");
			y = layer.objects_[i].GetPropertyValue("y");
			position = sf::Vector2f(atoi(x.c_str()), atoi(y.c_str()));

			string in = layer.objects_[i].GetPropertyValue("i");
			string out = layer.objects_[i].GetPropertyValue("o");
			sf::Vector2f fade;
			if(in != "" && out != "")
				fade = sf::Vector2f(std::stof(in.c_str()), std::stof(out.c_str()));

			string alive = layer.objects_[i].GetPropertyValue("a");
			string dead = layer.objects_[i].GetPropertyValue("d");
			sf::Vector2f timing;
			if (alive != "" && dead != "")
				timing = sf::Vector2f(std::stof(alive.c_str()), std::stof(dead.c_str()));

			if (!(timing == sf::Vector2f(0.0f, 0.0f)) && !(fade == sf::Vector2f(0.0f, 0.0f))) {
				p->SpawnFade(position, fade, timing);
			}
			else if (!(fade == sf::Vector2f(0.0f, 0.0f))) {
				p->SpawnFade(position, fade);
			}
			else {
				p->SpawnFade(position);
			}
			

			//id = layer.objects_[i].GetPropertyValue("id");
			
		}
		if (type == "OneWayPlatform") {
			x = layer.objects_[i].GetPropertyValue("x");
			y = layer.objects_[i].GetPropertyValue("y");
			position = sf::Vector2f(atoi(x.c_str()), atoi(y.c_str()));

			//id = layer.objects_[i].GetPropertyValue("id");
			p->SpawnOneWay(position);
		}
		if (type == "NodePlatform") {
			x = layer.objects_[i].GetPropertyValue("x");
			y = layer.objects_[i].GetPropertyValue("y");
			position = sf::Vector2f(atoi(x.c_str()), atoi(y.c_str()));

			id = layer.objects_[i].GetPropertyValue("id");
			p->SpawnNodePlatform(position, id, true);
		}
		if (type == "Node") {
			string next, previous, id;
			x = layer.objects_[i].GetPropertyValue("x");
			y = layer.objects_[i].GetPropertyValue("y");
			position = sf::Vector2f(atoi(x.c_str()), atoi(y.c_str()));

			id = layer.objects_[i].GetPropertyValue("id");
			next = layer.objects_[i].GetPropertyValue("n");
			//previous = layer.objects_[i].GetPropertyValue("p");
			m_point_map.append(id, make_shared<PointNode>(position, next));
		}
	}

	p->linkNodes(&m_point_map);
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
void Level::GenerateEnemies(b2World *world, tmx::ObjectGroup &layer, Spawner* s){
	int lenght = layer.objects_.size();
	sf::Vector2f position;
	string num;
	for (int i = 0; i < lenght; i++) {
		string type = layer.objects_[i].GetPropertyValue("type");
		if (type == "Skeleton") {
			num = layer.objects_[i].GetPropertyValue("x");
			position.x = atoi(num.c_str());

			num = layer.objects_[i].GetPropertyValue("y");
			position.y = atoi(num.c_str());			
			
			s->SpawnSkeleton(position);
		}
	}
}
void Level::GenerateBlocks(b2World * world, tmx::ObjectGroup & layer, Spawner * spawner) {
	int lenght = layer.objects_.size();
	sf::Vector2f position;
	string num;
	CrumbleBlock::TYPE block_type;
	CrumbleBlock::SIZE block_size;
	for (int i = 0; i < lenght; i++) {
		string type = layer.objects_[i].GetPropertyValue("type");
		//Find the type of Block
		if (type == "rock")
			block_type = CrumbleBlock::ROCK;
		else if (type == "sand")
			block_type = CrumbleBlock::SAND;
		else if (type == "dirt")
			block_type = CrumbleBlock::DIRT;

		string size = layer.objects_[i].GetPropertyValue("w");
		if (size == "64")
			block_size = CrumbleBlock::LARGE;
		else if (size == "32")
 			block_size = CrumbleBlock::SMALL;

		sf::Vector2f position = sf::Vector2f();
		num = layer.objects_[i].GetPropertyValue("x");
		position.x = atoi(num.c_str());

		num = layer.objects_[i].GetPropertyValue("y");
		position.y = atoi(num.c_str());

		spawner->SpawnBlock(position, block_type, block_size);
	}
}

void Level::Destroy(b2World *world) {
	int i;
	
	//Destroy Terrain
	for (i = 0; i < terrain_data.size(); i++) {
		world->DestroyBody(terrain_data[i]->body);
		delete terrain_data[i];
	}
	terrain_data.clear();
}
void Level::loadMap(string lvl_name) {
	tiled_map = make_shared<tmx::TileMap>(path + lvl_name + format);
	tiled_map->ShowObjects(true);
	
}