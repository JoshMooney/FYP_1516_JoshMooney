#include "stdafx.h"
#include "XYPlatform.hpp"
#include "XYPlatform.hpp"

//XY Tile
XYTile::XYTile()	{	}
XYTile::XYTile(b2Body* b, sf::Vector2f root_pos) {
	m_box_body = b;
	m_body_active = true;
	m_root_pos = root_pos;
	m_spawn_pos = vHelper::toSF(m_box_body->GetPosition());
	m_destin_pos = m_spawn_pos;

	loadMedia();
	alineSprite();
}
XYTile::~XYTile()	{	}

void XYTile::loadMedia() {
	if(m_root_pos == m_spawn_pos)
		s_texture = "Assets/Game/xy_platform.png";
	else
		s_texture = "Assets/Game/xy_platform_root.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(s_texture);
	m_size = sf::Vector2u(32, 32);
	setOrigin(m_size.x / 2, m_size.y / 2);
}
void XYTile::update(FTS fts) {
	alineSprite();

}
void XYTile::move() {
	
}
void XYTile::alineSprite() {
	setPosition(vHelper::toSF(m_box_body->GetPosition()));
}

//XY Platforms
XYPlatform::XYPlatform() {

}
XYPlatform::XYPlatform(b2Body *b, sf::Vector2f spawn) {
	//m_world = w;
	//m_box_body = b;
	//m_box_body->SetUserData(this);

	//loadMedia();
	//createNeighbours();
	//m_root_tile = XYTile(b);

}
XYPlatform::XYPlatform(b2Body * b, sf::Vector2f spawn, b2BodyDef bodDef, b2PolygonShape xy_shape, b2FixtureDef xyFix) {
	b->SetUserData(this);
	m_root_tile = make_unique<XYTile>(b, spawn);
	m_spawn_pos = spawn;

	m_current_state = OPEN;
	m_previous_state = m_current_state;

	m_bod_def = bodDef;
	m_bod_shape = xy_shape;
	m_bod_fix = xyFix;

	createNeighbours();
	alineSprite();
}
XYPlatform::~XYPlatform() {		}

void XYPlatform::update(FTS fts) {
	for (auto const &t : m_neighbour_tile) {
		t->update(fts);
	}
	m_root_tile->update(fts);
}
void XYPlatform::render(sf::RenderWindow & w, sf::Time frames) {
	for (auto const &t : m_neighbour_tile)
		w.draw(*t);
	w.draw(*m_root_tile);
}
void XYPlatform::alineSprite() {
	for (auto const &t : m_neighbour_tile)
		t->alineSprite();
	m_root_tile->alineSprite();
}
void XYPlatform::createNeighbours() {
	sf::Vector2f root_pos = vHelper::toSF(m_root_tile->getBody()->GetPosition());
	b2World *l_world = m_root_tile->getBody()->GetWorld();
	sf::Vector2f seperation = sf::Vector2f(32, 32);

	for (int i = 0; i < 4; i++) {
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
			int j = i;
			if (j == 3)
				j = 2;
			spawn_pos.x = root_pos.x - (seperation.x * j);
			m_bod_def.position = vHelper::toB2(spawn_pos);
			body = l_world->CreateBody(&m_bod_def);
			body->CreateFixture(&m_bod_fix);
		}

		m_neighbour_tile.push_back(make_shared<XYTile>(body, m_spawn_pos));
	}
}

void XYPlatform::destroyBody() {
	b2World* l_world;

	l_world = m_root_tile->getBody()->GetWorld();

	for (auto const &t : m_neighbour_tile) {
		l_world->DestroyBody(t->getBody());
	}
	l_world->DestroyBody(m_root_tile->getBody());
}

sf::Vector2f& XYPlatform::calculateVelocity(XYTile &tile) {
	sf::Vector2f position = vHelper::toSF(m_box_body->GetPosition());
	
	sf::Vector2f dir = sf::Vector2f(tile.getDestination().x - getPosition().x, tile.getDestination().y - getPosition().y);

	//Normalise direction Vector
	float mag = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (mag > 0)	dir = sf::Vector2f(dir.x / mag, dir.y / mag);
	else			dir = sf::Vector2f(0, 0);

	return dir;
}
