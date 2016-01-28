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
	ai = WHITE;

	loadMedia();

	//Entity Initalisation
	e_hp = 10;
	e_body_active;
}

void Skeleton::loadMedia(){
	e_texture = "Assets/Game/Skeleton_Walk.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(e_texture);
	//m_text_size = l_texture.getSize();
	m_text_size = sf::Vector2u(41, 64);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);

	addFrames(frame_walk, 0, 0, 4, m_text_size.x, m_text_size.y, 0.25f);

	m_animator.addAnimation(WALKING, frame_walk, sf::seconds(0.5f));
	//frame_attack;
	//frame_idle;
	//frame_death;
}

void Skeleton::addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration)
{
	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, ySep * y, xSep, ySep));
}

void Skeleton::update(FTS fts) {
	move();
	// If no other animation is playing, play idle animation
	if (!m_animator.isPlayingAnimation())
		m_animator.playAnimation(WALKING);

	alineSprite();
}
void Skeleton::render(sf::RenderWindow &w, sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);
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
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}

void Skeleton::ChangeDirection() {
	e_direction = !e_direction;
	if (e_direction)	setScale(1, 1);
	else setScale(-1, 1);
}

void Skeleton::setDirection(bool b) {
	e_direction = b;
	if (e_direction)	setScale(1, 1);
	else setScale(-1, 1);
}

void Skeleton::ReachedEdge() {
	ChangeDirection();

}

void Skeleton::ReachPlayer() {
	ChangeDirection();
	move();
}

void Skeleton::ReachWall(){
	ChangeDirection();

}
