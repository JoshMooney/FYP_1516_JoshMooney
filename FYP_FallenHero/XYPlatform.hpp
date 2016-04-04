#ifndef _XY_PLATFORM_HPP
#define _XY_PLATFORM_HPP
#include "stdafx.h"
#include "Platform.hpp"
#include <vector>

/**
*	@class XYTile
*	@brief
*/
class XYTile : public sf::Sprite {
private:
	sf::Vector2f m_rest_pos;
	sf::Vector2f m_tar_pos;
	b2Body *m_box_body;
	string s_texture;
	sf::Vector2u m_size;
	bool m_body_active;
	bool m_stage;

public:
	XYTile();
	XYTile(b2Body* b);
	~XYTile();

	void loadMedia();
	void update(FTS fts);
	void move();
	void alineSprite();
	b2Body* getBody() { return m_box_body; }
};

/**
*	@class XYPlatform
*	@brief 
*/
class XYPlatform : public Platform {
private:
	sf::Clock m_timer;
	//b2Body *m_box_body;
	b2World *m_world;
	string s_texture;
	sf::Vector2u m_size;
	bool m_body_active;

	XYTile m_root_tile;
	vector<XYTile> m_neighbour_tile;

	b2BodyDef m_bod_def;
	b2PolygonShape m_bod_shape;
	b2FixtureDef m_bod_fix;
public:
	XYPlatform();
	XYPlatform(b2Body *b);
	XYPlatform(b2Body* b, b2BodyDef bodDef, b2PolygonShape xy_shape, b2FixtureDef xyFix);
	~XYPlatform();

	void update(FTS fts);
	void render(sf::RenderWindow &w, sf::Time frames);

	void alineSprite();
	void createNeighbours();

	sf::FloatRect geometry() {
		sf::Vector2f position(m_box_body->GetPosition().x - (m_size.x / 2), m_box_body->GetPosition().y - (m_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
	}
};

#endif