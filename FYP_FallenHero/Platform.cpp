#include "stdafx.h"
#include "Platform.hpp"

Platform::Platform(b2Body * b) : m_box_body(b){
	m_box_body->SetUserData(this);
	m_body_active = true;
	
	loadMedia();

	alineSprite();
}
Platform::~Platform() {

}

void Platform::update(FTS fts) {
	//alineSprite();
}

void Platform::render(sf::RenderWindow & w, sf::Time frames) {
	w.draw(*this);
}

void Platform::loadMedia() {
	s_texture = "Assets/Game/platform.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(s_texture);
	m_size = sf::Vector2u(160, 16);
	setOrigin(m_size.x / 2, m_size.y / 2);
}

void Platform::alineSprite() {
	setPosition(vHelper::toSF(m_box_body->GetPosition()));
}
