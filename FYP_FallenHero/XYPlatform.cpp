#include "stdafx.h"
#include "XYPlatform.hpp"
#include "XYPlatform.hpp"

//XY Tile
XYTile::XYTile()	{	}
XYTile::XYTile(b2Body* b) {
	m_box_body = b;
	m_body_active = true;
	
}
XYTile::~XYTile()	{	}
void XYTile::loadMedia() {
	s_texture = "Assets/Game/xy_platform.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(s_texture);
	m_size = sf::Vector2u(32, 32);
	setOrigin(m_size.x / 2, m_size.y / 2);
}
void XYTile::update(FTS fts) {

}
void XYTile::move() {

}
void XYTile::alineSprite() {
	setPosition(vHelper::toSF(m_box_body->GetPosition()));
}

//XY Platforms
XYPlatform::XYPlatform() {

}
XYPlatform::XYPlatform(b2Body *b) {
	//m_world = w;
	//m_box_body = b;
	//m_box_body->SetUserData(this);

	//loadMedia();
	//createNeighbours();
	//m_root_tile = XYTile(b);

}
XYPlatform::XYPlatform(b2Body * b, b2BodyDef bodDef, b2PolygonShape xy_shape, b2FixtureDef xyFix) {
	b->SetUserData(this);
	m_root_tile = XYTile(b);

	m_bod_def = bodDef;
	m_bod_shape = xy_shape;
	m_bod_fix = xyFix;

	createNeighbours();
	alineSprite();
}
XYPlatform::~XYPlatform() {		}
void XYPlatform::update(FTS fts) {
	for (XYTile t : m_neighbour_tile) {
		t.update(fts);
	}
}
void XYPlatform::render(sf::RenderWindow & w, sf::Time frames) {
	for (XYTile t : m_neighbour_tile) {
		w.draw(t);
	}
}
void XYPlatform::alineSprite() {
	for (XYTile t : m_neighbour_tile) {
		t.alineSprite();
	}
}
void XYPlatform::createNeighbours() {
	sf::Vector2f root_pos = vHelper::toSF(m_root_tile.getBody()->GetPosition());
	b2World *l_world = m_root_tile.getBody()->GetWorld();
	sf::Vector2f seperation = sf::Vector2f(32, 32);

	for (int i = 0; i < 5; i++) {
		b2Body *body;
		sf::Vector2f spawn_pos = root_pos;
		if (i == 0) {
			spawn_pos.x = root_pos.x + (seperation.x * 1);
			m_bod_def.position = vHelper::toB2(spawn_pos);
			body = l_world->CreateBody(&m_bod_def);
			body->CreateFixture(&m_bod_fix);
		}
		// if the integer when divided by 2 has no remainder then it's even.
		else if (i % 2 == 0) {
			spawn_pos.x = root_pos.x + (seperation.x * i);
			m_bod_def.position = vHelper::toB2(spawn_pos);
			body = l_world->CreateBody(&m_bod_def);
			body->CreateFixture(&m_bod_fix);
		}
		else {
			spawn_pos.x = root_pos.x - (seperation.x * i);
			m_bod_def.position = vHelper::toB2(spawn_pos);
			body = l_world->CreateBody(&m_bod_def);
			body->CreateFixture(&m_bod_fix);
		}

		m_neighbour_tile.push_back(XYTile(body));
	}
}
