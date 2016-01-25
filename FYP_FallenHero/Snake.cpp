#include "stdafx.h"
#include "Snake.hpp"

Snake::Snake() {
	init();
}
Snake::Snake(b2Body *b, sf::Vector2f pos, bool dir) {
	b->SetUserData(this);
	b->SetTransform(vHelper::toB2(pos), 0.0f);
	e_box_body = b;
	init();

	//After Default initalisation
	e_direction = dir;
}
Snake::Snake(b2World * world) {
	/*
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(200, 100); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.userData = this;

	e_body_active = true;
	e_box_body = world->CreateBody(&myBodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
	shape.SetAsBox(m_text_size.x / 2.0f, m_text_size.y / 2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.5f;
	myFixtureDef.shape = &shape;

	e_box_body->CreateFixture(&myFixtureDef);
	*/
}

void Snake::init() {
	m_speed = 25.0f;
	e_direction = 1;	//true = 1 = Looing right and vice versa
	speedFactor = 0;

	m_current_state = WALKING;
	ai = GREEN;

	e_texture = "Assets/Game/enemy.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(e_texture);
	m_text_size = l_texture.getSize();
	m_acceleration = 1200;
	m_deceleration = 800;
}

void Snake::update(FTS fts) {
	move();

	alineSprite();
}
void Snake::render(sf::RenderWindow &w) {

}

void Snake::move() {
	if (e_direction) {
		if (speedFactor < 1.f)
			speedFactor += 0.02f;
		else if (speedFactor > 1.f)
			speedFactor = 1.f;

		e_box_body->SetLinearVelocity(b2Vec2(m_speed * speedFactor, e_box_body->GetLinearVelocity().y));
	}
	else {
		if (speedFactor > -1.f)
			speedFactor -= 0.02;
		else if (speedFactor < -1.f)
			speedFactor = -1.f;

		e_box_body->SetLinearVelocity(b2Vec2(m_speed * speedFactor, e_box_body->GetLinearVelocity().y));
	}
}

void Snake::attack() {

}

void Snake::alineSprite() {
	b2Vec2 box_pos = e_box_body->GetPosition();
	sf::Vector2f sf_box_pos = sf::Vector2f(box_pos.x - (m_text_size.x * 0.5f), box_pos.y - (m_text_size.y * 0.5f));
	setPosition(sf_box_pos);
}
