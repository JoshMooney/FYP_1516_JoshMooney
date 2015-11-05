#include "stdafx.h"
#include "Player.hpp"

Player::Player(b2World &m_world){
	m_jump_force = 15.0f;
	m_is_moving = false;
	m_is_jumping = false;
	m_speed = 5.0f;
	m_direction = 1;	//true = 1 = Looing right and vice versa

	if (!e_texture.loadFromFile("Assets/Game/player.png"))
		cLog::inst()->print(2, "Player", "Texture Failed to load");
	setTexture(e_texture);
	m_text_size = e_texture.getSize();
	m_acceleration = 1200;
	m_deceleration = 180;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(200, 0); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.userData = this;

	e_body_active = true;
	e_box_body = m_world.CreateBody(&myBodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	shape.SetAsBox(m_text_size.x * 0.5f, m_text_size.y * 0.5f);
	e_box_body->CreateFixture(&shape, 0.0f);

	alineSprite();
}
Player::~Player(){
	//Destroys the Box2D body component of the Player
	e_box_body->GetWorld()->DestroyBody(e_box_body);
	e_box_body = nullptr;


}

void Player::update(sf::Time dt){
	alineSprite();
}
void Player::moveLeft(){
	m_direction = 0;

	float newXVel = clamp(e_box_body->GetLinearVelocity().x - (m_acceleration * DELTA_TIME.asSeconds()), -m_speed, m_speed);
	e_box_body->SetLinearVelocity(b2Vec2(newXVel, e_box_body->GetLinearVelocity().y));
	m_is_moving = true;
}
void Player::moveRight(){
	m_direction = 1;

	float newXVel = clamp(e_box_body->GetLinearVelocity().x + (m_acceleration * DELTA_TIME.asSeconds()), -m_speed, m_speed);
	e_box_body->SetLinearVelocity(b2Vec2(newXVel, e_box_body->GetLinearVelocity().y));
	m_is_moving = true;
}
void Player::jump(){
	float newYVel = clamp(e_box_body->GetLinearVelocity().y + (m_acceleration * DELTA_TIME.asSeconds()), -m_jump_force, m_jump_force);
	//e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x, m_acceleration * DELTA_TIME.asSeconds()), -m_jump_force, m_jump_force);
	e_box_body->SetLinearVelocity(b2Vec2(e_box_body->GetLinearVelocity().x, e_box_body->GetLinearVelocity().y - newYVel));
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