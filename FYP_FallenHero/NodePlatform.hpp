#ifndef _NODE_PLATFORM_HPP
#define _NODE_PLATFORM_HPP
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

#include "ResourceManager.hpp"
#include "PointNode.hpp"

class NodePlatform : public sf::Sprite {
private:
	b2Body *m_box_body;
	bool m_body_active;
	string s_texture;
	sf::Vector2u m_size;
	//sf::FloatRect m_geometry;
	PointNode* m_nextNode;
	bool m_direction;
	float m_speed;
	float m_speed_factor;
	bool m_is_moving;
public:
	NodePlatform(b2Body *b, PointNode* n, bool d);
	NodePlatform(b2Body *b, PointNode* n, bool d, float speed);
	~NodePlatform();

	virtual void update(FTS fts);
	virtual void render(sf::RenderWindow &w, sf::Time frames);

	sf::Vector2f& calculateVelocity();
	void alineSprite();

	void setNode(PointNode* n) { m_nextNode = n; }
	PointNode* getNode() const { return m_nextNode; }

	bool isMoving() { return m_is_moving; }
	void setMoving(bool b) { m_is_moving = b; }
	b2Body* getBody() { return m_box_body; }
};

#endif