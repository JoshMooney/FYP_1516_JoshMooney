#ifndef _PLATFORM_CREATOR_HPP
#define _PLATFORM_CREATOR_HPP
#include "stdafx.h"
#include "NodePlatform.hpp"
#include "Platform.hpp"
#include "PointMap.hpp"

class PlatformCreator {
private:
	b2World* m_world;
	std::vector<shared_ptr<Platform>> m_platforms;
	std::vector<shared_ptr<NodePlatform>> m_platforms_node;
public:
	PlatformCreator() {

	}
	PlatformCreator(b2World* w);

	b2Body* generateBody(sf::Vector2f position);
	void SpawnPlatform(sf::Vector2f pos);
	void SpawnNodePlatform(sf::Vector2f pos, std::pair<string, string> nodes, bool dir);

	void linkNodes(PointMap *map);

	void update(FTS fts);
	void render(sf::RenderWindow& w, sf::Time frames);
	void clear();
};

#endif