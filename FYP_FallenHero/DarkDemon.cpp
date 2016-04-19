#include "stdafx.h"
#include "DarkDemon.hpp"

DarkDemon::DarkDemon() {

}
DarkDemon::DarkDemon(b2Body * b, ProjectileManager* pm, bool dir) : m_projectile_mgr(pm) {
	b->SetUserData(this);
	e_box_body = b;

	shoot_cooldown = 2.0f;
	m_current_state = IDLE;
	m_previous_state = m_current_state;

	loadMedia();
	alineSprite();

	m_animator.playAnimation(m_current_state, true);

	e_body_active = true;
	e_sword_col = false;
	e_can_despawn = false;
	setDirection(dir);
	e_direction = dir;

	m_speed = 10.0f;
	speedFactor = 0;
	e_hp = 10;
	m_cooldown = 2.0f;

	m_ai = make_shared<DemonAI>();
	m_can_take_damage = true;
	m_has_taken_action = false;
	m_has_finished_action = false;
	m_has_dropped_loot = false;
	off_wall = 0;
	max_off_wall = 2;

	m_shoot_prop.push_back(0.01f);
	m_shoot_prop.push_back(0.01f);
	m_shoot_prop.push_back(0.01f);
	m_shoot_prop.push_back(0.01f);
}
DarkDemon::~DarkDemon() {		}

void DarkDemon::ChangeState(STATE s) {
	
}
void DarkDemon::loadMedia() {
	e_texture = "Assets/Game/boss.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_text_size = sf::Vector2u(35, 44);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);
	setScale(1.5, 1.5);
	attack_frame_size = sf::Vector2i(58, 36);
	
	//Add all the regular frames
	addFrames(frame_idle,			0, 0, 3, 35, 40, 1.0f);
	addFrames(frame_dash,			1, 0, 3, 30, 40, 1.0f);
	addFrames(frame_hurt,			2, 0, 1, 33, 40, 1.0f);
	addFrames(frame_recover,		3, 0, 1, 30, 40, 1.0f);
	addFrames(frame_ready,			4, 0, 2, 39, 40, 1.0f);
	addFrames(frame_attack,			5, 0, 3, 58, 36, 1.0f);
	addFrames(frame_transform,		6, 0, 3, 51, 44, 1.0f);
	addFrames(frame_attack_trans,	7, 0, 1, 66, 44, 1.0f);
	addFrames(frame_transform_dash, 8, 0, 3, 66, 36, 1.0f);
	addFrames(frame_attack_dash,	9, 0, 1, 66, 36, 1.0f);
	addFrames(frame_die,		   10, 0, 5, 56, 36, 1.0f);

	//Add the transforming frames but only backwards.
	int i = 0;
	for (i = 2; i > -1; i -= 1)
		frame_rev_transform.addFrame(1.0f, sf::IntRect(51 * i, 236, 51, 44));
	for (i = 2; i > -1; i -= 1)
		frame_rev_transform_dash.addFrame(1.0f, sf::IntRect(66 * i, 324, 66, 36));

	//Attach frame to the animator
	m_animator.addAnimation(IDLE,				frame_idle,					sf::seconds(0.25f));
	m_animator.addAnimation(DASH,				frame_dash,					sf::seconds(1.0f));
	m_animator.addAnimation(HURT,				frame_hurt,					sf::seconds(0.4f));
	m_animator.addAnimation(RECOVER,			frame_recover,				sf::seconds(0.25f));
	m_animator.addAnimation(READY,				frame_ready,				sf::seconds(0.20f));
	m_animator.addAnimation(ATTACK,				frame_attack,				sf::seconds(0.1f));
	m_animator.addAnimation(TRANS,				frame_transform,			sf::seconds(0.25f));
	m_animator.addAnimation(REV_TRANS,			frame_rev_transform,		sf::seconds(1.25f));
	m_animator.addAnimation(ATTACK_TRANS,		frame_attack_trans,			sf::seconds(1.0f));
	m_animator.addAnimation(TRANS_DASH,			frame_transform_dash,		sf::seconds(0.25f));
	m_animator.addAnimation(REV_TRANS_DASH,		frame_rev_transform_dash,	sf::seconds(0.25f));
	m_animator.addAnimation(ATTACK_DASH,		frame_attack_dash,			sf::seconds(1.0f));
	m_animator.addAnimation(DIE,				frame_die,					sf::seconds(1.0f));

	//Load Sound effects
	s_taunt = "Assets/Audio/Game/Boss/laugh.wav";
	m_taunt.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_taunt));
	m_demon_taunt = m_taunt;
	m_demon_taunt.setPitch(0.7f);
	/*
	s_death = "Assets/Audio/Game/skeleton_kill.wav";
	m_death.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_death));*/
}
void DarkDemon::checkAnimation() {
	if (m_previous_state != m_current_state) {
		m_previous_state = m_current_state;
		if(m_current_state == IDLE || m_current_state == ATTACK_TRANS || m_current_state == ATTACK_DASH)
			m_animator.playAnimation(m_current_state, true);
		else
			m_animator.playAnimation(m_current_state, false);
	}

	if (!m_animator.isPlayingAnimation()) {
		if (m_current_state == ATTACK) {
			m_can_take_damage = true;
			m_current_state = RECOVER;
		}
		//Demon
		else if (m_current_state == TRANS) {
			m_current_state = ATTACK_TRANS;
			m_fully_formed = true;
			m_clock.restart();
		}
		else if (m_current_state == REV_TRANS) {
			m_current_state = IDLE;
			m_clock.restart();
			m_fully_formed = true;
			m_can_take_damage = true;
		}
		//Slime
		else if (m_current_state == TRANS_DASH) {
			m_current_state = ATTACK_DASH;
			m_fully_formed = true;
			m_clock.restart();
		}
		else if (m_current_state == REV_TRANS_DASH) {
			m_current_state = IDLE;
			m_clock.restart();
			m_fully_formed = true;
			m_can_take_damage = true;
		}
		//Human
		else if (m_current_state == HURT) {
			m_current_state = RECOVER;
		}
		else if (m_current_state == DASH) {
			m_current_state = RECOVER;
		}
		else if (m_current_state == RECOVER) {
			m_current_state = IDLE;
			m_can_take_damage = true;
			m_clock.restart();
		}
		else if (m_current_state == DIE)
			e_can_despawn = true;
		/*
		if(!m_animator.isPlayingAnimation() && (m_current_state == IDLE ||
				m_current_state == ATTACK || m_current_state == REV_TRANS ||
				m_current_state == READY))

		if (m_current_state == IDLE && !m_animator.isPlayingAnimation())
			m_animator.playAnimation(IDLE);*/
	}
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
	if (e_hp <= 20)
		setColor(sf::Color::Red);
	alineSprite();
	checkAnimation();

	if (e_body_active) {
		if (canThink()) {
			m_prev_action = m_ai->getAction();
			m_ai->think(p, getPosition(), e_hp);
			m_clock.restart();
			m_has_finished_action = false;
			m_has_taken_action = false;
			m_fully_formed = false;

			if (p->getPosition().x > getPosition().x)
				setDirection(1);
			else
				setDirection(0);
		}
		if (canTakeAction() || m_has_finished_action) {
			takeAction();
		}

		if (m_action == Form::ACTIONS::SHOOT && !m_has_finished_action && !is_hit) {
			shoot(p);
		}

		if (m_action == Form::ACTIONS::MOVE && m_type == Form::TYPE::HUMAN && m_current_state != DASH)
			e_box_body->SetTransform(e_box_body->GetPosition(), 0.0f);
		else if (m_action == Form::ACTIONS::MOVE && !is_hit && (m_current_state == DASH || m_current_state == ATTACK_TRANS || m_current_state == ATTACK_DASH))
			move();
	}
	
	//if (m_action != m_prev_action && m_action != Form::ACTIONS::MOVE)
		//e_box_body->SetLinearVelocity(b2Vec2(0, 0));

	//move();
	//cLog::inst()->print("" + std::to_string(m_action));
}
void DarkDemon::render(sf::RenderWindow & w, sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);
}

void DarkDemon::TakeDamage() {
	if (!is_hit && m_can_take_damage) {
		is_hit = true;
		//m_can_take_damage = false;
		//m_has_taken_action = true;
		m_current_state = HURT;
		e_hp -= 10;

		m_cooldown = 3.0 / 100 * e_hp;
		m_has_taken_action = true;

		if (e_hp <= 0)
			Die();
	}
}
void DarkDemon::Die() {
	e_box_body->GetFixtureList()->SetSensor(true);
	e_body_active = false;
	m_current_state = DIE;
}

void DarkDemon::move() {
	if (!is_hit) {
		switch (m_type) {
		case Form::TYPE::HUMAN:
			if (Form::MOVE == m_action) {
				if (touching_terr == nullptr) {
					//In the air
					//m_animator.playAnimation(IDLE);
					//if (e_body_active) {
					//	m_current_state = IDLE;
				}
				else {
					sf::FloatRect b = getBounds();
					m_speed = m_ai->currentForm()->m_speed;
					if (e_direction) {
						if (touching_terr->geometry.left + touching_terr->geometry.width > b.left + b.width) {
							if (speedFactor < 1.f)
								speedFactor += 0.02f;
							else if (speedFactor > 1.f)
								speedFactor = 1.f;

							e_box_body->SetLinearVelocity(b2Vec2(m_speed, e_box_body->GetLinearVelocity().y));
						}
						else
							ReachedWall();
					}
					else {
						if (touching_terr->geometry.left < b.left) {
							if (speedFactor > -1.f)
								speedFactor -= 0.02;
							else if (speedFactor < -1.f)
								speedFactor = -1.f;

							e_box_body->SetLinearVelocity(b2Vec2(-m_speed, e_box_body->GetLinearVelocity().y));
						}
						else
							ReachedWall();
					}
				}
			}
			break;
		case Form::TYPE::SLIME:
			if (Form::MOVE == m_action) {
					if (touching_terr == nullptr) {
						//In the air
						//m_animator.playAnimation(IDLE);
						//if (e_body_active) {
						//	m_current_state = IDLE;
					}
					else {
						m_speed = m_ai->currentForm()->m_speed;
						sf::FloatRect b = getBounds();
						if (e_direction) {
							if (touching_terr->geometry.left + touching_terr->geometry.width > b.left + b.width) {
								if (speedFactor < 1.f)
									speedFactor += 0.02f;
								else if (speedFactor > 1.f)
									speedFactor = 1.f;

								e_box_body->SetLinearVelocity(b2Vec2(m_speed, e_box_body->GetLinearVelocity().y));
							}
							else
								ReachedWall();
						}
						else {
							if (touching_terr->geometry.left < b.left) {
								if (speedFactor > -1.f)
									speedFactor -= 0.02;
								else if (speedFactor < -1.f)
									speedFactor = -1.f;

								e_box_body->SetLinearVelocity(b2Vec2(-m_speed, e_box_body->GetLinearVelocity().y));
							}
							else
								ReachedWall();
						}
					}
				}
			break;
		case Form::TYPE::DEMON:
			if (Form::MOVE == m_action) {
					if (touching_terr == nullptr) {
						//In the air
						//m_animator.playAnimation(IDLE);
						//if (e_body_active) {
						//	m_current_state = IDLE;
					}
					else {
						sf::FloatRect b = getBounds();
						m_speed = m_ai->currentForm()->m_speed;
						if (e_direction) {
							if (touching_terr->geometry.left + touching_terr->geometry.width > b.left + b.width) {
								if (speedFactor < 1.f)
									speedFactor += 0.02f;
								else if (speedFactor > 1.f)
									speedFactor = 1.f;

								e_box_body->SetLinearVelocity(b2Vec2(m_speed, e_box_body->GetLinearVelocity().y));
							}
							else
								ReachedWall();
						}
						else {
							if (touching_terr->geometry.left < b.left) {
								if (speedFactor > -1.f)
									speedFactor -= 0.02;
								else if (speedFactor < -1.f)
									speedFactor = -1.f;

								e_box_body->SetLinearVelocity(b2Vec2(-m_speed, e_box_body->GetLinearVelocity().y));
							}
							else
								ReachedWall();
						}
					}
				}
			break;
		}
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
void DarkDemon::shoot(Player* p) {
	//Make a choose of which type of attack to make
	Prob::B_TYPE type = chooseShoot();
	int j;
	float rotation;
	float adjustment;
	sf::Vector2f between;
	sf::Vector2f new_dir;

	//Take Action
	switch (type) {
	case Prob::B_TYPE::AT_PLAYER:
		m_has_finished_action = true;
		between = p->getPosition() - getPosition();
		rotation = atan2f(between.y, between.x);
		adjustment = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.4));
		j = rand() % 2;
		if (j == 1)	adjustment *-1;
		else        adjustment * 1;

		new_dir = sf::Vector2f(cosf(rotation + adjustment), sinf(rotation + adjustment));
		m_projectile_mgr->shootBoss(getPosition(), new_dir, "At-Player");

		m_shoot_prop[Prob::B_TYPE::AT_PLAYER]	-= 0.02f;
		m_shoot_prop[Prob::B_TYPE::DIRECT]		+= 0.01f;
		m_shoot_prop[Prob::B_TYPE::DIRECT_MORE] += 0.005f;
		m_shoot_prop[Prob::B_TYPE::UP]			+= 0.01f;
		break;
	case Prob::B_TYPE::UP:
		m_projectile_mgr->shootBoss(getPosition(), sf::Vector2f(0, -1), "Up");

		m_shoot_prop[Prob::B_TYPE::AT_PLAYER]	+= 0.015f;
		m_shoot_prop[Prob::B_TYPE::DIRECT]		+= 0.005f;
		m_shoot_prop[Prob::B_TYPE::DIRECT_MORE] += 0.0025f;
		m_shoot_prop[Prob::B_TYPE::UP]			-= 0.005f;
		break;
	case Prob::B_TYPE::DIRECT:
		m_has_finished_action = true;
		m_projectile_mgr->shootBoss(getPosition(), sf::Vector2f(0, 0), "Directional");

		m_shoot_prop[Prob::B_TYPE::AT_PLAYER]	+= 0.02f;
		m_shoot_prop[Prob::B_TYPE::DIRECT]		-= 0.015f;
		m_shoot_prop[Prob::B_TYPE::DIRECT_MORE] += 0.005f;
		m_shoot_prop[Prob::B_TYPE::UP]			+= 0.01f;
		break;
	case Prob::B_TYPE::DIRECT_MORE:
		m_has_finished_action = true;
		m_projectile_mgr->shootBoss(getPosition(), sf::Vector2f(0, 0), "Directional-More");

		m_shoot_prop[Prob::B_TYPE::AT_PLAYER]	+= 0.02f;
		m_shoot_prop[Prob::B_TYPE::DIRECT]		+= 0.005f;
		m_shoot_prop[Prob::B_TYPE::DIRECT_MORE] -= 0.05f;
		m_shoot_prop[Prob::B_TYPE::UP]			+= 0.01f;
		break;
	}

	//Checks the probablity if its gone off scale.
	for (int i = 0; i < m_shoot_prop.size(); i++) {
		if (m_shoot_prop[i] < 0)
			m_shoot_prop[i] = 0;
		else if (m_shoot_prop[i] > 1)
			m_shoot_prop[i] = 1;
	}

	m_shoot_clock.restart();
}

void DarkDemon::alineSprite() {
	m_text_size = sf::Vector2u(35, 44);
	if (m_current_state != m_previous_state) {
		switch (m_current_state) {
		case IDLE:
			setOrigin(m_text_size.x / 2, m_text_size.y / 2);
			break;
		case DASH:
			setOrigin(m_text_size.x / 2, m_text_size.y / 2);
			break;
		case HURT:
			setOrigin(m_text_size.x / 2, m_text_size.y / 2);
			break;
		case RECOVER:
			setOrigin(m_text_size.x / 2, m_text_size.y / 2);
			break;
		case READY:
			setOrigin(m_text_size.x / 2, m_text_size.y / 2);
			break;
		case ATTACK:
			setOrigin(58 / 2, m_text_size.y / 2);
			break;
		case TRANS:
			setOrigin(m_text_size.x + 10 / 2, m_text_size.y / 2);
			break;
		case REV_TRANS:
			setOrigin(m_text_size.x + 10 / 2, m_text_size.y / 2);
			break;
		case ATTACK_TRANS:
			setOrigin(m_text_size.x + 8 / 2, m_text_size.y / 2);
			break;
		case TRANS_DASH:
			setOrigin(m_text_size.x + 6 / 2, m_text_size.y / 2);
			break;
		case REV_TRANS_DASH:
			setOrigin(m_text_size.x / 2, m_text_size.y / 2);
			break;
		case ATTACK_DASH:
			setOrigin(m_text_size.x / 2, m_text_size.y / 2);
			break;
		case DIE:
			setOrigin(m_text_size.x + 6 / 2, m_text_size.y / 2);
			break;
		}
	}
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
	ChangeDirection();
}
void DarkDemon::ReachPlayer() {
	ChangeDirection();
	//e_box_body->SetLinearVelocity(b2Vec2(0, 0));
}

bool DarkDemon::canThink() {
	bool canThink = false;
	m_type = m_ai->getForm();

	if(m_ai->currentForm()->morphin() || m_has_taken_action)
		canThink = true;

	switch (m_type) {
	#pragma region HUMAN
	case Form::TYPE::HUMAN:
		if (m_current_state == IDLE)
			canThink = true;
		break;
	#pragma endregion
	#pragma region SLIME
	case Form::TYPE::SLIME:
		if (m_current_state == ATTACK_DASH)
			canThink = true;
		break;
	#pragma endregion
	#pragma region DEMON
	case Form::TYPE::DEMON:
		if(m_current_state == ATTACK_TRANS)
			canThink = true;
		break;
	#pragma endregion
	}

	if (canThink && (m_clock.getElapsedTime().asSeconds() > m_cooldown || m_fully_formed))
		return true;
	return false;
}
bool DarkDemon::canTakeAction() {
	if (!is_hit && !m_has_taken_action) {
		m_has_taken_action = true;
		return true;
	}
	return false;
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
			m_current_state = DASH;
			break;
		case Form::ATTACK:
			//Play Attack
			m_current_state = ATTACK;
			attack();
			m_can_take_damage = false;
			break;
		case Form::SHOOT:
			//Play Shoot
			//m_current_state = DASH;
			break;
		case Form::TRANS:
			//Play Transform
			m_ai->checkForm();
			m_type = m_ai->getForm();
			if (m_type == Form::TYPE::DEMON) {
				m_current_state = TRANS;
			}
			else if (m_type == Form::TYPE::SLIME) {
				m_current_state = TRANS_DASH;
			}

			m_can_take_damage = false;
			break;
		case Form::TAUNT:
			//Play Taunt
			m_current_state = IDLE;
			m_taunt.play();
			break;
		}
		break;
		#pragma endregion
	#pragma region SLIME
	case Form::TYPE::SLIME:
		switch (m_action) {
		case Form::MOVE:
			m_current_state = ATTACK_DASH;
			break;
		case Form::ATTACK:
			break;
		case Form::SHOOT:
			break;
		case Form::TRANS:
			m_ai->checkForm();
			m_current_state = REV_TRANS_DASH;
			break;
		case Form::TAUNT:
			m_taunt.play();
			break;
		}
		break;
		#pragma endregion
	#pragma region DEMON
	case Form::TYPE::DEMON:
		switch (m_action) {
		case Form::MOVE:
			m_current_state = ATTACK_TRANS;
			break;
		case Form::ATTACK:
			m_current_state = ATTACK_TRANS;
			attack();
			break;
		case Form::SHOOT:
			break;
		case Form::TRANS:
			m_ai->checkForm();
			m_current_state = REV_TRANS;
			break;
		case Form::TAUNT:
			m_demon_taunt.play();
			break;
		}
		break;
		#pragma endregion
	}
}

void DarkDemon::isTouching(Terrain * t) {
	touching_terr = t;
}

Prob::B_TYPE DarkDemon::chooseShoot() {
	float max = 0;
	for (int i = 0; i < m_shoot_prop.size(); i++)
		max += m_shoot_prop[i];

	float result;
	result = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));

	for (int i = m_shoot_prop.size() - 1; i >= 0; i--) {
		max -= m_shoot_prop[i];
		if (result > max)
			return static_cast<Prob::B_TYPE>(i);
	}
}
Prob::A_TYPE DarkDemon::chooseAttack() {
	float max = 0;
	for (int i = 0; i < m_shoot_prop.size(); i++)
		max += m_attack_prop[i];

	float result;
	result = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));

	for (int i = m_shoot_prop.size() - 1; i >= 0; i--) {
		max -= m_shoot_prop[i];
		if (result > max)
			return static_cast<Prob::A_TYPE>(i);
	}
}

void DarkDemon::finishCurrentAciton() {
	if (m_current_state == DASH && m_action == Form::ACTIONS::MOVE) {
		m_has_taken_action = true;
	}
	if (m_current_state == ATTACK_DASH && m_action == Form::ACTIONS::MOVE) {
		m_has_taken_action = true;
	}
	if (m_current_state == ATTACK_TRANS && m_action == Form::ACTIONS::MOVE) {
		m_has_taken_action = true;
	}
}
