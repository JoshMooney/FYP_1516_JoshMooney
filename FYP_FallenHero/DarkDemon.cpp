#include "stdafx.h"
#include "DarkDemon.hpp"

DarkDemon::DarkDemon() {

}
DarkDemon::DarkDemon(b2Body * b, ProjectileManager* pm, bool dir) : m_projectile_mgr(pm) {
	b->SetUserData(this);
	e_box_body = b;

	m_current_state = IDLE;
	m_previous_state = m_current_state;

	loadMedia();
	alineSprite();

	e_body_active = true;
	e_sword_col = false;
	e_can_despawn = false;
	setDirection(dir);
	e_direction = dir;

	m_speed = 0.35f;
	speedFactor = 0;
	e_hp = 100;
	m_ai = make_shared<DemonAI>();
	m_can_take_damage = true;
}
DarkDemon::~DarkDemon() {

}

void DarkDemon::ChangeState(STATE s) {
	
}
void DarkDemon::loadMedia() {
	e_texture = "Assets/Game/boss_temp.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_text_size = sf::Vector2u(35, 44);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);
	
	//Add all the regular frames
	addFrames(frame_idle,			0, 0, 3, 35, 40, 1.0f);
	addFrames(frame_dash,			1, 0, 3, 30, 40, 1.0f);
	addFrames(frame_hurt,			2, 0, 1, 33, 40, 1.0f);
	addFrames(frame_recover,		3, 0, 1, 30, 47, 1.0f);
	addFrames(frame_ready,			4, 0, 2, 39, 40, 1.0f);
	addFrames(frame_attack,			5, 0, 3, 58, 36, 1.0f);
	addFrames(frame_transform,		6, 0, 3, 51, 44, 1.0f);
	addFrames(frame_attack_trans,	7, 0, 1, 66, 44, 1.0f);
	addFrames(frame_transform_dash, 8, 0, 3, 66, 36, 1.0f);
	addFrames(frame_attack_dash,	9, 0, 3, 66, 36, 1.0f);
	addFrames(frame_die,		   10, 0, 5, 56, 36, 1.0f);

	//Add the transforming frames but only backwards.
	int i = 0;
	for (i = 3 - 1; i > 0; i -= 1)
		frame_rev_transform.addFrame(1.0f, sf::IntRect(51 * i, 236, 51, 44));
	for (i = 3 - 1; i > 0; i -= 1)
		frame_rev_transform_dash.addFrame(1.0f, sf::IntRect(66 * i, 324, 66, 36));

	//Attach frame to the animator
	m_animator.addAnimation(IDLE,				frame_idle,					sf::seconds(1.5f));
	m_animator.addAnimation(DASH,				frame_dash,					sf::seconds(1.5f));
	m_animator.addAnimation(HURT,				frame_hurt,					sf::seconds(1.5f));
	m_animator.addAnimation(RECOVER,			frame_recover,				sf::seconds(1.5f));
	m_animator.addAnimation(READY,				frame_ready,				sf::seconds(1.5f));
	m_animator.addAnimation(ATTACK,				frame_attack,				sf::seconds(1.5f));
	m_animator.addAnimation(TRANS,				frame_transform,			sf::seconds(1.5f));
	m_animator.addAnimation(REV_TRANS,			frame_rev_transform,		sf::seconds(1.5f));
	m_animator.addAnimation(ATTACK_TRANS,		frame_attack_trans,			sf::seconds(1.5f));
	m_animator.addAnimation(TRANS_DASH,			frame_transform_dash,		sf::seconds(1.5f));
	m_animator.addAnimation(REV_TRANS_DASH,		frame_rev_transform_dash,	sf::seconds(1.5f));
	m_animator.addAnimation(ATTACK_DASH,		frame_attack_dash,			sf::seconds(1.5f));
	m_animator.addAnimation(DIE,				frame_die,					sf::seconds(1.5f));

	/*
	s_death = "Assets/Audio/Game/skeleton_kill.wav";
	m_death.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_death));*/
}
void DarkDemon::checkAnimation() {
	/*if (m_previous_state != m_current_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}

	if(!m_animator.isPlayingAnimation() && (m_current_state == IDLE ||
			m_current_state == ATTACK || m_current_state == REV_TRANS ||
			m_current_state == READY))

	if (m_current_state == IDLE && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(IDLE);*/
}
void DarkDemon::addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
	if (y == 0)
		y = 0;
	else if (y == 1)
		y = 40;
	else if (y == 2)
		y = 80;
	else if (y == 3)
		y = 120;
	else if (y == 4)
		y = 160;
	else if (y == 5)
		y = 200;
	else if (y == 6)
		y = 236;
	else if (y == 7)
		y = 280;
	else if (y == 8)
		y = 324;
	else if (y == 9)
		y = 360;
	else if (y == 10)
		y = 396;

	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));
}

void DarkDemon::update(FTS fts, Player * p) {
	checkAnimation();
	alineSprite();

	if (p->getPosition().x > getPosition().x)
		setDirection(1);
	else
		setDirection(0);

	if (/*ai_think &&*/ m_clock.getElapsedTime().asSeconds() > 4) {
		m_ai->think(p, getPosition(), e_hp);
		takeAction();
		m_clock.restart();
	}
	//cLog::inst()->print("" + std::to_string(m_action));
}
void DarkDemon::render(sf::RenderWindow & w, sf::Time frames) {
	/*m_animator.update(frames);
	m_animator.animate(*this);*/
}

void DarkDemon::TakeDamage() {
	if (!is_hit && m_can_take_damage) {
		is_hit = true;
		e_hp -= 10;
		if (e_hp <= 0)
			Die();
	}
}
void DarkDemon::Die() {
	e_box_body->GetFixtureList()->SetSensor(true);
	e_body_active = false;
}
void DarkDemon::move() {
	switch (m_type) {
	#pragma region HUMAN
	case Form::TYPE::HUMAN:
		if (Form::MOVE == m_action) {

		}
		break;
	#pragma endregion
	#pragma region SLIME
	case Form::TYPE::SLIME:
		if (Form::MOVE == m_action) {

		}
		break;
	#pragma endregion
	#pragma region DEMON
	case Form::TYPE::DEMON:
		if (Form::MOVE == m_action) {

		}
		break;
	#pragma endregion
	}
}
void DarkDemon::attack() {
	switch (m_type) {
	#pragma region HUMAN
	case Form::TYPE::HUMAN:
		if (Form::ATTACK == m_action && !m_has_attacked) {
			m_has_attacked = true;
		}
		break;
	#pragma endregion
	#pragma region SLIME
	case Form::TYPE::SLIME:
		if (Form::ATTACK == m_action && !m_has_attacked) {
			m_has_attacked = true;
		}
		break;
	#pragma endregion
	#pragma region DEMON
	case Form::TYPE::DEMON:
		if (Form::ATTACK == m_action && !m_has_attacked) {
			m_has_attacked = true;
		}
		break;
	#pragma endregion
	}
}
void DarkDemon::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}
void DarkDemon::ChangeDirection() {
	e_direction = !e_direction;
	if (e_direction)	setScale(1, 1);
	else setScale(-1, 1);
}
void DarkDemon::setDirection(bool dir) {
	e_direction = dir;
	if (e_direction)	setScale(1, 1);
	else setScale(-1, 1);
}
void DarkDemon::ReachedWall() {

}
void DarkDemon::ReachPlayer() {

}
void DarkDemon::takeAction() {
	m_action = m_ai->getAction();
	m_type = m_ai->getForm();

	switch (m_type) {
	#pragma region HUMAN
	case Form::TYPE::HUMAN:
		switch (m_action) {
		case Form::MOVE:
			//Play Dash
			m_animator.playAnimation(DASH);
			break;
		case Form::ATTACK:
			//Play Attack
			m_animator.playAnimation(ATTACK);
			break;
		case Form::SHOOT:
			//Play Shoot
			m_animator.playAnimation(READY);
			break;
		case Form::TRANS:
			//Play Transform

			break;
		case Form::TAUNT:
			//Play Taunt
			break;
		}
		break;
		#pragma endregion
	#pragma region SLIME
	case Form::TYPE::SLIME:
		switch (m_action) {
		case Form::MOVE:
			m_animator.playAnimation(DASH);
			break;
		case Form::ATTACK:
			break;
		case Form::SHOOT:
			break;
		case Form::TRANS:
			break;
		case Form::TAUNT:
			break;
		}
		break;
		#pragma endregion
	#pragma region DEMON
	case Form::TYPE::DEMON:
		switch (m_action) {
		case Form::MOVE:
			m_animator.playAnimation(DASH);
			break;
		case Form::ATTACK:
			break;
		case Form::SHOOT:
			break;
		case Form::TRANS:
			break;
		case Form::TAUNT:
			break;
		}
		break;
		#pragma endregion
	}
}
