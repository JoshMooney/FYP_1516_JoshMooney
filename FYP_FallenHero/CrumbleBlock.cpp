#include "stdafx.h"
#include "CrumbleBlock.hpp"

CrumbleBlock::CrumbleBlock() {

}
CrumbleBlock::CrumbleBlock(b2Body *b, sf::Vector2f pos, TYPE t, SIZE s) {
	b->SetUserData(this);

	gemCount = 1;
	m_type = t;
	m_size = s; 

	loadMedia();

	sf::Vector2f pos_offset = sf::Vector2f(pos.x + (m_text_size.x / 2), pos.y + (m_text_size.y / 2));
	b->SetTransform(vHelper::toB2(pos_offset), 0.0f);
	e_box_body = b;
	alineSprite();

	e_body_active = true;
	e_can_despawn = false;
	e_sword_col = false;
	
	if (m_type == ROCK)	e_hp = 20;
	else e_hp = 10;

	m_current_state = ALIVE;
}
CrumbleBlock::~CrumbleBlock() {

}

void CrumbleBlock::loadMedia() {
	//Audio Stuff
	//s_hit = "Assets/Audio/Game/Player/jump.wav";
	//m_hit.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_hit));

	//Texture Stuff!
	switch (m_type) {
	case SAND:
		if (m_size == LARGE) {
			e_texture = "Assets/Game/block_sand_large.png";
			m_text_size = sf::Vector2u(64, 64);
		}
		else {
			e_texture = "Assets/Game/block_sand_small.png";
			m_text_size = sf::Vector2u(32, 32);
		}
		break;
	case ROCK:
		if (m_size == LARGE) {
  			e_texture = "Assets/Game/block_rock_large.png";
			m_text_size = sf::Vector2u(64, 64);
		}
		else {
			e_texture = "Assets/Game/block_rock_small.png";
			m_text_size = sf::Vector2u(32, 32);
		}
		break;
	case DIRT:
		if (m_size == LARGE) {
			e_texture = "Assets/Game/block_dirt_large.png";
			m_text_size = sf::Vector2u(64, 64);
		}
		else {
			e_texture = "Assets/Game/block_dirt_small.png";
			m_text_size = sf::Vector2u(32, 32);
		}
		break;
	}
	//Load and apply Texture
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);

	//Animation Stuff
	addFrames(frame_alive, ALIVE, 0, 1, m_text_size.x, m_text_size.y, 1.0f);
	m_animator.addAnimation(ALIVE, frame_alive, sf::seconds(1.0f));

	if (m_size == LARGE)	addFrames(frame_dead, DEAD, 0, 3, 90, 76, 1.0f);
	if (m_size == SMALL)	addFrames(frame_dead, DEAD, 0, 3, 48, 38, 1.0f);
  	m_animator.addAnimation(DEAD, frame_dead, sf::seconds(0.3f));

	if (m_type == ROCK) {
		addFrames(frame_crumble, CRUMBLE, 0, 1, m_text_size.x, m_text_size.y, 1.0f);
		m_animator.addAnimation(CRUMBLE, frame_crumble, sf::seconds(1.0f));
	}
}

void CrumbleBlock::checkAnimation() {
	if (m_current_state != m_previous_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}

	if (m_current_state == DEAD && !m_animator.isPlayingAnimation()) {
		Die();
	}
	else if (m_current_state != DEAD && !m_animator.isPlayingAnimation()) {
		m_animator.playAnimation(m_current_state);
	}
}
void CrumbleBlock::addFrames(thor::FrameAnimation & animation, STATE s, int xFirst, int xLast, int xSep, int ySep, float duration) {
	int y;
	if (s == ALIVE)
		y = 0;
	else if (s == CRUMBLE)	{
		if (m_size == LARGE)		y = 140;
		if (m_size == SMALL)		y = 70;
	}
	else if (s == DEAD) {
		if (m_size == LARGE)		y = 64;
		if (m_size == SMALL)		y = 32;
	}

	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep), sf::Vector2f(xSep / 2, ySep / 2));
}

void CrumbleBlock::alineSprite() {
	sf::Vector2f pos = vHelper::toSF(e_box_body->GetPosition());
	setPosition(pos);
}

void CrumbleBlock::TakeDamage() {
	e_hp -= 10;
	if (e_hp <= 0) {
		m_current_state = DEAD;
		e_box_body->GetFixtureList()->SetSensor(true);
		e_body_active = false;
	}
	else if (e_hp <= 10 && m_type == ROCK) {
		m_current_state = CRUMBLE;
	}
}

void CrumbleBlock::Die() {
	e_can_despawn = true;
}

void CrumbleBlock::update(FTS fts, Player* p) {
	checkAnimation();
}

void CrumbleBlock::render(sf::RenderWindow &w, sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);
}
