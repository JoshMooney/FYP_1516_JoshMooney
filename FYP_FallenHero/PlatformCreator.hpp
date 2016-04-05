#ifndef _PLATFORM_CREATOR_HPP
#define _PLATFORM_CREATOR_HPP
#include "stdafx.h"
#include "NodePlatform.hpp"
#include "Platform.hpp"
#include "PointMap.hpp"
#include "OneWayPlatform.hpp"
#include "FadePlatform.hpp"
#include "XYPlatform.hpp"

/**
*	@class 
*	@brief
*/
class PlatformCreator {
private:
	b2World* m_world;
	std::vector<shared_ptr<Platform>> m_platforms;
	std::vector<shared_ptr<NodePlatform>> m_platforms_node;
	PointMap* m_point_map;
public:
	/**
	*	@brief
	*/
	PlatformCreator() {

	}
	/**
	*	@brief
	*	@param
	*/
	PlatformCreator(b2World* w);

	/**
	*	@brief
	*	@param
	*	@param
	*/
	b2Body* generateBody(sf::Vector2f position, string type);
	/**
	*	@brief
	*	@param
	*/
	void SpawnPlatform(sf::Vector2f pos);
	/**
	*	@brief
	*	@param
	*/
	void SpawnOneWay(sf::Vector2f pos);
	/**
	*	@brief
	*	@param
	*/
	void SpawnFade(sf::Vector2f pos);
	/**
	*	@brief
	*	@param
	*/
	void SpawnFade(sf::Vector2f pos, sf::Vector2f fade);
	/**
	*	@brief
	*	@param
	*/
	void SpawnFade(sf::Vector2f pos, sf::Vector2f fade, sf::Vector2f timing);
	/**
	*	@brief
	*	@param
	*/
	void SpawnNodePlatform(sf::Vector2f pos, string id_node, bool dir);
	/**
	*	@brief
	*	@param
	*/
	void SpawnXY(sf::Vector2f pos);

	/**
	*	@brief
	*	@param
	*/
	void linkNodes(PointMap *map);

	/**
	*	@brief
	*	@param
	*/
	void update(FTS fts);
	/**
	*	@brief
	*	@param
	*/
	void render(sf::RenderWindow& w, sf::Time frames);
	/**
	*	@brief
	*	@param
	*/
	void clear();
};

#endif