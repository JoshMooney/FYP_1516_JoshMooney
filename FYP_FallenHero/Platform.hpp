#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

#include "ResourceManager.hpp"

class Platform {
public:
	b2Body *m_box_body;
	bool m_body_active;
	sf::Sprite m_sprite;
	string s_texture;
	sf::Vector2f m_size;
	sf::FloatRect m_geometry;

	Platform();
	Platform(sf::FloatRect geo);
	Platform(sf::Vector2f position, sf::Vector2f size);
	Platform(sf::Vector2f position, sf::Vector2f size, b2World &m_world);
	void setBody(b2Body* b) { m_box_body = b; }
	void render(sf::RenderWindow &w);
};

#endif