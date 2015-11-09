#include "stdafx.h"
#include "Platform.hpp"

Platform::Platform(){}
Platform::Platform(sf::Vector2f position, sf::Vector2f size, b2World &m_world) {
	m_size = size;
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody; //this will be a static body
	myBodyDef.position = b2Vec2(position.x + (m_size.x * 0.5f), position.y + (m_size.y * 0.5f)); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.userData = this;
	m_body_active = true;
	m_box_body = m_world.CreateBody(&myBodyDef);

	//Define the shape 
	b2PolygonShape shape;
	shape.SetAsBox(m_size.x * 0.5f, m_size.y * 0.5f);
	m_box_body->CreateFixture(&shape, 0.0f);

	s_texture = "Assets/Game/platform.png";
	m_sprite.setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));

	sf::Vector2<int> l_int_size = sf::Vector2<int>((int)m_size.x, (int)m_size.y);
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2<int>(0, 0), l_int_size));
	m_sprite.setPosition(sf::Vector2f(position.x, position.y));
	m_sprite.setColor(sf::Color::Green);
}

void Platform::render(sf::RenderWindow &w){
	w.draw(m_sprite);
}
