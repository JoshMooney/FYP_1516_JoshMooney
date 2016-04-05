#ifndef _ONE_WAY_PLATFORM_HPP
#define _ONE_WAY_PLATFORM_HPP
#include "stdafx.h"
#include "Platform.hpp"

class OneWayPlatform : public Platform {
private:

public:
	OneWayPlatform() {

	}
	OneWayPlatform(b2Body* b) {
		m_box_body = b;
		m_box_body->SetUserData(this);
		m_body_active = true;

		loadMedia();
		alineSprite();
	}

	void update(FTS fts) override {
	
	}
	void render(sf::RenderWindow &w, sf::Time frames) override {
		w.draw(*this);
	}
	void loadMedia() override {
		s_texture = "Assets/Game/semi_platform.png";
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		m_size = sf::Vector2u(160, 16);
		sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(s_texture);
		setOrigin(m_size.x / 2, m_size.y / 2);
	}
	void destroyBody() {
		m_box_body->GetWorld()->DestroyBody(m_box_body);
	}
};

#endif