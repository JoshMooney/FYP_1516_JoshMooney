#include "stdafx.h"
#include "Player.hpp"

Player::Player(b2World &m_world){
	m_jump_force = 50.0f;
	m_is_moving = false;
	m_is_jumping = false;
	m_speed = 50.0f;
	m_direction = 1;	//true = 1 = Looing right and vice versa
	speedFactor = 0;

	e_texture = "Assets/Game/player.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(e_texture);
	m_text_size = l_texture.getSize();
	m_acceleration = 1200;
	m_deceleration = 800;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(200, 0); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.userData = this;

	e_body_active = true;
	e_box_body = m_world.CreateBody(&myBodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
	shape.SetAsBox(m_text_size.x / 2.0f, m_text_size.y /2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.5f;
	myFixtureDef.shape = &shape;

	e_box_body->CreateFixture(&myFixtureDef);
	//e_box_body->CreateFixture(&shape, 0.0f);

	alineSprite();
}
Player::~Player(){
	//Destroys the Box2D body component of the Player
	e_box_body->GetWorld()->DestroyBody(e_box_body);
	e_box_body = nullptr;


}

void Player::update(FTS fts){
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
	m_direction = 0;
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
void Player::moveRight(){
	m_direction = 1;
	if (speedFactor < 1.f)
		speedFactor += 0.02f;
	else if (speedFactor > 1.f)
		speedFactor = 1.f;

	e_box_body->SetLinearVelocity(b2Vec2(m_speed * speedFactor, e_box_body->GetLinearVelocity().y));
	//float newXVel = clamp(e_box_body->GetLinearVelocity().x + (m_speed * DELTA_TIME.asSeconds()), -m_deceleration, m_acceleration);
	//e_box_body->SetLinearVelocity(b2Vec2(newXVel, e_box_body->GetLinearVelocity().y));
	m_is_moving = true;
}
void Player::jump(){
	float newYVel = clamp(e_box_body->GetLinearVelocity().y + (m_acceleration * DELTA_TIME.asSeconds()), -m_jump_force, m_jump_force);
	//e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x, m_acceleration * DELTA_TIME.asSeconds()), -m_jump_force, m_jump_force);
	e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x, e_box_body->GetLinearVelocity().y - newYVel));
}
void Player::reset(sf::Vector2f pos) {
	m_direction = 1;	//true = 1 = Looing right and vice versa
	speedFactor = 0;
	e_box_body->SetLinearVelocity(b2Vec2(0, 0));
	moveTo(pos);
}

void Player::alineSprite(){
	b2Vec2 box_pos = e_box_body->GetPosition();
	sf::Vector2f sf_box_pos = sf::Vector2f(box_pos.x - (m_text_size.x * 0.5f), box_pos.y - (m_text_size.y * 0.5f));
	setPosition(sf_box_pos);
}

//clamp a value to a range
inline float Player::clamp(float x, float min, float max)
{
	return x < min ?	//check x less than min
	min : (x > max ?	//check x greater than max
	  max : x);
}