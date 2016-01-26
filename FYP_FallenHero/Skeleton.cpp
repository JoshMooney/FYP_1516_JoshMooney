#include "stdafx.h"
#include "Skeleton.hpp"
#include "vHelper.hpp"

Skeleton::Skeleton() {
	init();
}
Skeleton::Skeleton(b2Body *b, sf::Vector2f pos, bool dir) {
	b->SetUserData(this);
	b->SetTransform(vHelper::toB2(pos), 0.0f);
	e_box_body = b;
	init();

	//After Default initalisation
	e_direction = dir;
}
Skeleton::Skeleton(b2World * world) {
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

void Skeleton::init() {
	m_speed = 0.5f;
	e_direction = 1;	//true = 1 = Looing right and vice versa
	speedFactor = 0;
	e_can_despawn = false;

	m_current_state = WALKING;
	ai = GREEN;

	e_texture = "Assets/Game/enemy.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(e_texture);
	m_text_size = l_texture.getSize();
	m_acceleration = 1200;
	m_deceleration = 800;

	//Entity Initalisation
	e_hp = 10;
	e_body_active;
}

void Skeleton::update(FTS fts) {
	move();

	alineSprite();
}
void Skeleton::render(sf::RenderWindow &w) {

}

void Skeleton::TakeDamage() {
	e_hp -= 10;
	if (e_hp <= 0)
		Die();
}

void Skeleton::Die() {
	e_body_active = false;
	e_can_despawn = true;
}

void Skeleton::move() {
	if (touching_terr == nullptr) {
		//In the air
	}
	else {
		sf::FloatRect b = getBounds();
		if (e_direction) {
			if (touching_terr->geometry.left + touching_terr->geometry.width > b.left + b.width) {
				if (speedFactor < 1.f)
					speedFactor += 0.02f;
				else if (speedFactor > 1.f)
					speedFactor = 1.f;

				e_box_body->SetLinearVelocity(b2Vec2(m_speed * speedFactor, e_box_body->GetLinearVelocity().y));
			}
			else
				ReachedEdge();
		}
		else {
			if (touching_terr->geometry.left < b.left) {
				if (speedFactor > -1.f)
					speedFactor -= 0.02;
				else if (speedFactor < -1.f)
					speedFactor = -1.f;

				e_box_body->SetLinearVelocity(b2Vec2(m_speed * speedFactor, e_box_body->GetLinearVelocity().y));
			}
			else
				ReachedEdge();
		}
	}
}

void Skeleton::attack() {

}

void Skeleton::alineSprite() {
	sf::Vector2f box_pos = vHelper::toSF(e_box_body->GetPosition());
	sf::Vector2f sf_box_pos = sf::Vector2f(box_pos.x - (m_text_size.x * 0.5f), box_pos.y - (m_text_size.y * 0.5f));
	setPosition(sf_box_pos);
}

void Skeleton::ReachedEdge() {
	e_direction = !e_direction;
}

void Skeleton::ReachPlayer() {
	e_direction = !e_direction;
	move();
}

void Skeleton::ReachWall(){
	e_direction = !e_direction;
}
