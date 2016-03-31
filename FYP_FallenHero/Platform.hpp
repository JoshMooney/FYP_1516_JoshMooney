#ifndef _PLATFORM_HPP
#define _PLATFORM_HPP
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

#include "ResourceManager.hpp"

class Platform : public sf::Sprite {
private:
	
public:
	b2Body *m_box_body;
	string s_texture;
	sf::Vector2u m_size;
	bool m_body_active;

	Platform() {

	}
	Platform(b2Body* b);
	~Platform();

	virtual void update(FTS fts);
	virtual void render(sf::RenderWindow &w, sf::Time frames);
	virtual void loadMedia();

	void alineSprite();
	b2Body* getBody() { return m_box_body; }
	sf::FloatRect geometry() {
		sf::Vector2f position(getPosition().x - (m_size.x / 2), getPosition().y - (m_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
	}
};

#endif