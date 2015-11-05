#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

class Platform {
public:
	b2Body *m_box_body;
	bool m_body_active;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_size;

	Platform();
	Platform(sf::Vector2f position, sf::Vector2f size, b2World &m_world);
	void render(sf::RenderWindow &w);
};

#endif