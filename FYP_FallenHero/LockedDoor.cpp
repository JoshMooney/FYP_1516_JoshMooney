#include "stdafx.h"
#include "LockedDoor.hpp"

Door::Door() {		}
Door::Door(b2Body * b) {
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	m_dis_to_player = 250;

	e_sword_col = false;
	e_can_despawn = false;

	m_prompt_active = false;
	loadMedia();
	alineSprite();
	m_prompt_pos = sf::Vector2f(0, -50);
}
Door::~Door() {		}

void Door::update(FTS fts, Player * p) {
	if (vHelper::distance(p->getPosition(), getPosition()) < m_dis_to_player)
		m_prompt_active = true;
	else
		m_prompt_active = false;

	if (m_prompt_active) {
		sf::Vector2f p_pos = p->getPosition();
		m_prompt_spt.setPosition(p_pos + m_prompt_pos);
	}
}

void Door::render(sf::RenderWindow & w, sf::Time frames) {
	//m_animator.update(frames);
	//m_animator.animate(*this);

	if (m_prompt_active)
		w.draw(m_prompt_spt);
}

void Door::loadMedia() {
	s_prompt_spt = "Assets/Game/prompt.png";
	m_prompt_spt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_prompt_spt));
	setOrigin(32 / 2, 32 / 2);

	e_texture = "Assets/Game/locked_door.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_size = sf::Vector2u(32, 160);
	setOrigin(m_size.x / 2, m_size.y / 2);

	/*addFrames(frame_close, 0, 0, 1, 37, 18, 1.0f);
	addFrames(frame_open, 18, 0, 1, 42, 23, 1.0f);
	m_animator.addAnimation(OPEN, frame_open, sf::seconds(1.0f));
	m_animator.addAnimation(CLOSE, frame_close, sf::seconds(1.0f));*/

	/*s_locked = "Assets/Audio/Cannon/cannon_fire.wav";
	m_locked.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_locked));
	s_unlock = "Assets/Audio/Cannon/cannon_tud.wav";
	m_unlock.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_unlock));
	s_hit = "Assets/Audio/Cannon/cannon_tud.wav";
	m_hit.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_hit));*/
}

void Door::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}
void Door::TakeDamage() {
	if (!is_hit) {


		is_hit = true;
	}
}
void Door::Die() {		}
void Door::attack() {		}
