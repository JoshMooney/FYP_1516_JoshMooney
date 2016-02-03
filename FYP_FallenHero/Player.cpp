#include "stdafx.h"
#include "Player.hpp"
#include "vHelper.hpp"

Player::Player(b2World &m_world){
	m_alive = true;
	e_hp = 100;
	e_max_hp = 100;
	m_xp = 100;
	m_max_xp = 100;
	m_gold = 9001;

	loadMedia();

	m_jump_force = 1.5f;
	m_is_moving = false;
	m_is_jumping = false;
	m_is_attacking = false;
	m_speed = 1.5f;
	m_direction = 1;	//true = 1 = Looing right and vice versa
	speedFactor = 0;

	m_acceleration = 1200;
	m_deceleration = 800;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position = vHelper::toB2(sf::Vector2f(200, 0)); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.userData = this;
	myBodyDef.fixedRotation = true;
	//myBodyDef.gravityScale = 0.0f;

	e_body_active = true;
	e_box_body = m_world.CreateBody(&myBodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
	shape.SetAsBox((m_text_size.x / vHelper::B2_SCALE) / 2, (m_text_size.y / vHelper::B2_SCALE) / 2);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.5f;
	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Player";
	

	e_box_body->CreateFixture(&myFixtureDef);
	//e_box_body->CreateFixture(&shape, 0.0f);

	//Create Fixture for the Attack swing 
	b2PolygonShape sword_shape;
	sword_shape.SetAsBox((104 / vHelper::B2_SCALE) / 2, (60 / vHelper::B2_SCALE) / 2, vHelper::toB2(sf::Vector2f(0, -8)), 0.0f);

	b2FixtureDef mySwordDef;
	mySwordDef.density = 1.0f;
	mySwordDef.friction = 1.5f;
	mySwordDef.shape = &sword_shape;
	mySwordDef.userData = "Player_Sword";
	mySwordDef.isSensor = true;

	e_box_body->CreateFixture(&mySwordDef);

	alineSprite();

	m_current_state = IDLE;
}
Player::~Player(){
	//Destroys the Box2D body component of the Player
	e_box_body->GetWorld()->DestroyBody(e_box_body);
	e_box_body = nullptr;


}

void Player::checkAnimation() {
	if (m_is_attacking && m_current_state != HIT)		//Attack if the state is attacking
		m_current_state = ATTACK;
	else if (m_is_jumping && m_current_state != HIT)
		m_current_state = JUMP;
	else if (m_is_moving && m_current_state != HIT)		//Run if m_moving is true
		m_current_state = RUN;
	else if (!m_is_moving && !m_is_attacking && !m_is_jumping && m_current_state != HIT)	//Idle if not moving or attacking or jumping and not hit
		m_current_state = IDLE;
	
	if (m_current_state != m_previous_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}

	if (m_current_state == RUN && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(RUN);
	if (m_current_state == JUMP && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(JUMP);
	if (m_current_state == IDLE && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(IDLE);
	if (m_current_state == ATTACK && !m_animator.isPlayingAnimation()) {
		m_is_attacking = false;
		m_current_state = IDLE;
	}
	if (m_current_state == HIT && !m_animator.isPlayingAnimation()) {
		m_current_state = IDLE;
	}
}
void Player::addFrames(thor::FrameAnimation & animation, STATE s, int xFirst, int xLast, int xSep, int ySep, float duration) {
	int y = 0;
	sf::Vector2f o;
	if (s == ATTACK) {
		y = 0;
		o = sf::Vector2f(16, 40);
	}
	else if (s == RUN)	{
		y = 60;
		o = sf::Vector2f(19, 31);
	}
	else if (s == IDLE) {
		y = 164;
		o = sf::Vector2f(16, 20);
	}
	else if (s == HIT) {
		y = 208;
		o = sf::Vector2f(19, 24);
	}
	else if (s == JUMP) {
		y = 112;
		o = sf::Vector2f(30, 24);
	}


	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep), o);

}
void Player::render(sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);
}
void Player::loadMedia() {
	s_jump = "Assets/Audio/Game/Player/jump.wav";
	m_jump.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_jump));
	s_death = "Assets/Audio/Game/Player/death.wav";
	m_death.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_death));
	s_finish_level = "Assets/Audio/Game/Player/finish_level.wav";
	m_finish_level.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_finish_level));
	s_fall = "Assets/Audio/Game/Player/fall.wav";
	m_fall.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_fall));
	s_hit = "Assets/Audio/Game/Player/player_hit.wav";
	m_hit.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_hit));
	s_swing = "Assets/Audio/Game/Player/swing.wav";
	m_swing.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_swing));


	//Texture Stuff!
	e_texture = "Assets/Game/player.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(e_texture);
	m_text_size = sf::Vector2u(36, 44);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);
	attack_frame_size = sf::Vector2i(68, 60);

	addFrames(frame_run,	RUN,	0, 4, 36, 52, 1.0f);
	addFrames(frame_idle,	IDLE,	0, 3, 32, 44, 1.0f);
	addFrames(frame_attack, ATTACK, 0, 3, 68, 60, 1.0f);
	addFrames(frame_jump,	JUMP,	0, 4, 36, 52, 1.0f);
	addFrames(frame_hit,	HIT,	0, 1, 46, 44, 1.0f);

	m_animator.addAnimation(ATTACK, frame_attack,	sf::seconds(0.15f));
	m_animator.addAnimation(RUN,	frame_run,		sf::seconds(0.5f));
	m_animator.addAnimation(IDLE,	frame_idle,		sf::seconds(1.5f));
	m_animator.addAnimation(JUMP,	frame_jump,		sf::seconds(1.2f));
	m_animator.addAnimation(HIT,	frame_hit,		sf::seconds(1.2f));
}

void Player::update(FTS fts){
	checkAnimation();
	alineSprite();
	Idle();
}
void Player::Idle() {
	if (!m_is_moving) {
		if (speedFactor > 0)
			speedFactor -= 0.02f;
		if (speedFactor < 0)
			speedFactor += 0.02f;
		e_box_body->SetLinearVelocity(b2Vec2(0, e_box_body->GetLinearVelocity().y));
	}
}
void Player::moveLeft(){
	if (!m_is_attacking && m_current_state != HIT) {
		setDirection(false);
		if (speedFactor > -1.f)
			speedFactor -= 0.02;
		else if (speedFactor < -1.f)
			speedFactor = -1.f;

		e_box_body->SetLinearVelocity(b2Vec2(m_speed * speedFactor, e_box_body->GetLinearVelocity().y));
		//float newXVel = clamp(e_box_body->GetLinearVelocity().x - (m_acceleration * DELTA_TIME.asSeconds()), -m_speed, m_speed);
		//float newXVel = clamp(e_box_body->GetLinearVelocity().x - (m_speed * DELTA_TIME.asSeconds()), -m_deceleration, m_acceleration);
		//e_box_body->SetLinearVelocity(b2Vec2(newXVel, e_box_body->GetLinearVelocity().y));
		m_is_moving = true;
	}
}
void Player::moveRight(){
	if (!m_is_attacking && m_current_state != HIT) {
		setDirection(true);
		if (speedFactor < 1.f)
			speedFactor += 0.02f;
		else if (speedFactor > 1.f)
			speedFactor = 1.f;

		e_box_body->SetLinearVelocity(b2Vec2(m_speed * speedFactor, e_box_body->GetLinearVelocity().y));
		//float newXVel = clamp(e_box_body->GetLinearVelocity().x + (m_speed * DELTA_TIME.asSeconds()), -m_deceleration, m_acceleration);
		//e_box_body->SetLinearVelocity(b2Vec2(newXVel, e_box_body->GetLinearVelocity().y));
		m_is_moving = true;
	}
}

void Player::jump() {
	if (!m_is_jumping && !m_is_attacking && m_current_state != HIT) {
		m_jump.play();
		e_box_body->GetFixtureList()->SetFriction(0.0f);
		float newYVel = clamp(e_box_body->GetLinearVelocity().y + (m_acceleration * DELTA_TIME.asSeconds()), -m_jump_force, m_jump_force);
		//e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x, m_acceleration * DELTA_TIME.asSeconds()), -m_jump_force, m_jump_force);
		e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x, e_box_body->GetLinearVelocity().y - newYVel));
		m_is_jumping = true;
	}
}
void Player::reset(sf::Vector2f pos) {
	e_hp = 100;
	m_alive = true;
	m_direction = 1;	//true = 1 = Looing right and vice versa
	speedFactor = 0;
	e_box_body->SetLinearVelocity(b2Vec2(0, 0));
	moveTo(pos);
}

void Player::FallOffMap(sf::Vector2f pos) {
	reset(pos);
	m_fall.play();
}

void Player::attack() {
	if (!m_is_attacking && m_current_state != HIT) {
		//cLog::inst()->print("Player Attacked");
		m_swing.play();
		m_is_attacking = true;
	}
}

void Player::ChangeDirection() {
	m_direction = !m_direction;
	if (m_direction)	setScale(1, 1);
	else setScale(-1, 1);
}

void Player::setDirection(bool b) {
	m_direction = b;
	if (m_direction)	setScale(1, 1);
	else setScale(-1, 1);
}

void Player::TakeDamage(bool knock_dir) {
	if (m_current_state != HIT) {
		e_box_body->SetLinearVelocity(b2Vec2(0, 0));
		if (knock_dir) {
			float newXVel = clamp(e_box_body->GetLinearVelocity().x + (m_acceleration * DELTA_TIME.asSeconds()), 0, knock_back_factor.x);
			float newYVel = clamp(e_box_body->GetLinearVelocity().y + (m_acceleration * DELTA_TIME.asSeconds()), 0, knock_back_factor.y);
			e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x + newXVel, e_box_body->GetLinearVelocity().y - newYVel));
		}
		else {
			float newXVel = clamp(e_box_body->GetLinearVelocity().x + (m_acceleration * DELTA_TIME.asSeconds()), 0, knock_back_factor.x);
			float newYVel = clamp(e_box_body->GetLinearVelocity().y + (m_acceleration * DELTA_TIME.asSeconds()), 0, knock_back_factor.y);
			e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x - newXVel, e_box_body->GetLinearVelocity().y - newYVel));
		}
		m_hit.play();
		m_current_state = HIT;
		e_hp -= 25;
		if (e_hp <= 0) {
			m_alive = false;
		}
	}
}

void Player::alineSprite(){
	sf::Vector2f pos = vHelper::toSF(e_box_body->GetPosition());
	setPosition(pos);
}

//clamp a value to a range
inline float Player::clamp(float x, float min, float max)
{
	return x < min ?	//check x less than min
	min : (x > max ?	//check x greater than max
	  max : x);
}