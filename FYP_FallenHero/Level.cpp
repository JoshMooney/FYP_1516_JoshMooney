#include "stdafx.h"
#include "Level.hpp"

Level::Level() {
	cLog::inst()->print(3, "Level", "Default constructor of level called");
}

Level::Level(string s, b2World *world) {
	path = "Assets/Levels/";
	format = ".tmx";
	tile_size = sf::Vector2u(32, 32);

	loadMap(s);
	ParseMapLayers(world);
}
struct OBJ {
	int width;
	int height;
	int x;
	int y;
};

Level::~Level() {
	
}

void Level::render(sf::RenderWindow &w){
	w.draw(*tiled_map);
}

void Level::ParseMapLayers(b2World * world) {
	//map.GetObjectLayer("Layer Name");
	/*
	shared_ptr<tmx::ObjectGroup> lay;
	lay = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Terrain"));
	OBJ object;
	object.x = lay->objects_[0].x_;
	object.y = lay->objects_[0].y_;
	object.width = lay->objects_[0].width_;
	object.height = lay->objects_[0].height_;
	*/
	

	//CreateTerrain(world, l);

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Platform"));
	//CreatePlatforms(world, layer);

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Player_Data"));
	//GeneratePlayerItems(world, layer);

	//l = make_shared<tmx::ObjectGroup>(tiled_map->GetObjectGroup("Level_Data"));
	//GenerateLevelItems(world, layer);


}

void Level::CreateTerrain(b2World * world, shared_ptr<tmx::ObjectGroup> layer) {
	//for (const auto& o : layer.) {
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody;		//this will be a dynamic body
		myBodyDef.position.Set(0, 0);		//set the starting position
		myBodyDef.angle = 0;				//set the starting angle
		myBodyDef.userData = "Terrain";

		b2Body* box_body = world->CreateBody(&myBodyDef);

		//Define the shape of the body
		b2PolygonShape shape;
		shape.SetAsBox(1, 1);

		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 0.0f;
		myFixtureDef.friction = 0.0f;
		myFixtureDef.shape = &shape;

		box_body->CreateFixture(&myFixtureDef);
		terrain_data.push_back(box_body);
	//}

	/*
	std::vector<std::unique_ptr<sf::Shape>> debugBoxes;
	std::vector<DebugShape> debugShapes;
	std::map<b2Body*, sf::CircleShape> dynamicShapes; //we can use raw pointers because box2D manages its own memory
	//m_platform_data
	//Platform(sf::Vector2f position, sf::Vector2f size, b2World &m_world)
	for (const auto& o : layer.objects)
	{
		//receive a pointer to the newly created body
		b2Body* b = tmx::BodyCreator::Add(o, *world);
		sf::FloatRect body_geo = o.GetAABB();
		m_platform_data.push_back(Platform(body_geo));
		/*
		//iterate over body info to create some visual debugging shapes to help visualise
		debugBoxes.push_back(std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(6.f, 6.f))));
		sf::Vector2f pos = tmx::BoxToSfVec(b->GetPosition());
		debugBoxes.back()->setPosition(pos);
		debugBoxes.back()->setOrigin(3.f, 3.f);

		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			b2Shape::Type shapeType = f->GetType();
			if (shapeType == b2Shape::e_polygon)
			{
				DebugShape ds;
				ds.setPosition(pos);
				b2PolygonShape* ps = (b2PolygonShape*)f->GetShape();

				int count = ps->GetVertexCount();
				for (int i = 0; i < count; i++)
					ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(i)), sf::Color::Green));

				ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(0)), sf::Color::Green));
				debugShapes.push_back(ds);
			}
		}
	}*/
}


void Level::loadMap(string lvl_name) {
	tiled_map = make_shared<tmx::TileMap>(path + lvl_name + format);
	tiled_map->ShowObjects(true);
}
