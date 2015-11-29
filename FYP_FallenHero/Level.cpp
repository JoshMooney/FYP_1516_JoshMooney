#include "stdafx.h"
#include "Level.hpp"

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
Level::~Level() {
	
}

void Level::render(sf::RenderWindow &w){
	//w.draw(*tiled_map);
	//w.draw(*ml);
}

void Level::ParseMapLayers(b2World * world) {
	/*const std::vector<tmx::MapLayer>& layers = ml->GetLayers();

	for (const auto& l : layers){		//Foreach loop
		if (l.name == "Bodies") {
			CreateTerrain(world, l);
		}
	}*/

}

//void Level::CreateTerrain(b2World * world, tmx::MapLayer layer) {
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
//}


void Level::loadMap(string lvl_name) {
	//ml = make_shared<tmx::MapLoader>("Assets/Levels/");
	//ml->Load(lvl_name + format);
}
