#ifndef _XY_PLATFORM_HPP
#define _XY_PLATFORM_HPP
#include "stdafx.h"
#include "Platform.hpp"
#include <vector>
#include <memory>

/**
*	@class XYTile
*	@brief
*/
class XYTile : public sf::Sprite {
private:
	sf::Vector2f m_root_pos;
	sf::Vector2f m_spawn_pos;
	sf::Vector2f m_destin_pos;
	b2Body *m_box_body;
	string s_texture;
	sf::Vector2u m_size;
	bool m_body_active;
	bool m_stage;

public:
	XYTile();
	XYTile(b2Body* b, sf::Vector2f root_pos);
	~XYTile();

	void loadMedia();
	void update(FTS fts);
	void move();
	void alineSprite();
	b2Body* getBody() { return m_box_body; }
	sf::Vector2f getDestination() { return m_destin_pos; }
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

	unique_ptr<XYTile> m_root_tile;
	vector<shared_ptr<XYTile>> m_neighbour_tile;

	sf::Vector2f m_spawn_pos;
	b2BodyDef m_bod_def;
	b2PolygonShape m_bod_shape;
	b2FixtureDef m_bod_fix;
public:
	enum STATE {
		IDLE,
		OPEN,
		CLOSE
	};
	STATE m_current_state;
	STATE m_previous_state;
	XYPlatform();
	XYPlatform(b2Body *b, sf::Vector2f spawn);
	XYPlatform(b2Body* b, sf::Vector2f spawn, b2BodyDef bodDef, b2PolygonShape xy_shape, b2FixtureDef xyFix);
	~XYPlatform();

	void update(FTS fts);
	void render(sf::RenderWindow &w, sf::Time frames);

	void alineSprite();
	void createNeighbours();
	void destroyBody() override;
	sf::Vector2f& calculateVelocity(XYTile &tile);

	sf::FloatRect geometry() {
		sf::Vector2f position(m_box_body->GetPosition().x - (m_size.x / 2), m_box_body->GetPosition().y - (m_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
	}
};

#endif