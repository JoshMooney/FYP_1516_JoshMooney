#include "stdafx.h"
#include "Key.hpp"

Key::Key() {

}
Key::Key(b2Body * b, Key::TYPE t, string door, string id) {
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;

	e_can_despawn = false;

	m_door = door;
	m_type = t;
	m_id = id;

	e_hp = 0;
	e_max_hp = 0;

	loadMedia();
	alineSprite();
}
Key::~Key() {	}

void Key::init() {

}
void Key::loadMedia() {
	e_texture = "Assets/Game/keys.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));

	m_size = sf::Vector2u(32, 32);
	setOrigin(m_size.x / 2, m_size.y / 2);
	setTextureRect(sf::IntRect{ (int)m_size.x * m_type, 0, (int)m_size.x, (int)m_size.y });

	s_pickup = "Assets/Audio/Game/Door/key_pickup.wav";
	m_pickup.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_pickup));
}
void Key::update(FTS fts) {
	if(!e_body_active && m_pickup.getStatus() == sf::Sound::Status::Stopped)
		e_can_despawn = true;
}
void Key::render(sf::RenderWindow * w, sf::Time frames) {

}
std::pair<string, string> Key::pickup()		{
	e_body_active = false;
	m_pickup.play();
	e_box_body->GetFixtureList()->SetSensor(true);
	
	return std::pair<string, string>(m_id, m_door);
}
void Key::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}

bool Key::canDespawn() {
	if (!e_body_active && m_pickup.getStatus() == sf::Sound::Status::Stopped/*&& Sound not playing*/)
		return true;
	return false;
}

