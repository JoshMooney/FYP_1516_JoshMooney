#ifndef _NODE_PLATFORM_HPP
#define _NODE_PLATFORM_HPP
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

#include "ResourceManager.hpp"
#include "Platform.hpp"
#include "PointNode.hpp"

class NodePlatform : public Platform {
private:
	string s_texture;
	sf::Vector2u m_size;
	PointNode* m_nextNode;
	bool m_direction;
	float m_speed;
	float m_speed_factor;
	bool m_is_moving;
	string m_node_id;
	bool m_new_node;
public:
	NodePlatform(b2Body *b, string id, bool d);
	NodePlatform(b2Body *b, string id, bool d, float speed);
	~NodePlatform();

	void update(FTS fts);
	void render(sf::RenderWindow &w, sf::Time frames);
	void loadMedia();

	sf::Vector2f& calculateVelocity();
	void destroyBody() {
		m_box_body->GetWorld()->DestroyBody(m_box_body);
	}

	void setNode(PointNode* n) {
		m_nextNode = n;
		m_new_node = false;
	}
	PointNode* getNode() const { return m_nextNode; }

	bool isMoving() { return m_is_moving; }
	void setMoving(bool b) { m_is_moving = b; }
	string getNodeID() const { return m_node_id; }
	void setNodeID(string s) { m_node_id = s; }
	bool needsNode() { return m_new_node; }
};

#endif