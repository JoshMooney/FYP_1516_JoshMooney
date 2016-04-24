#ifndef _PROJECTILE_HPP
#define _PROJECTILE_HPP
#include "stdafx.h"
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "ResourceManager.hpp"
#include "Thor\Animations.hpp"

/**
*	@class Projectile
*	@brief This is the main base class for the projectile type of entity.
*/
class Projectile : public sf::Sprite {
private:
	float m_speed;
	string s_texture;
	sf::Vector2f m_size;
	bool m_body_active;     	 
	sf::Vector2f m_direction;
	bool can_despawn;

	thor::FrameAnimation frame_fire;
	thor::FrameAnimation frame_fire_bu;
	thor::FrameAnimation frame_fire_rd;
	thor::FrameAnimation frame_explode;
	thor::FrameAnimation frame_fire_bk;

	thor::FrameAnimation frame_weed_l1;
	thor::FrameAnimation frame_weed_l2;
	thor::FrameAnimation frame_weed_l3;
	thor::FrameAnimation frame_weed_explode;
public:
	b2Body *m_box_body;
	enum STATE {
		FIRE,
		BLUE,
		RED,
		EXPLODE, 
		BOSS,
		WEED_L1,
		WEED_L2,
		WEED_L3,
		BONE,
	};

	STATE m_current_state, m_previous_state;

	sf::Vector2f m_spawn_point;
	thor::Animator<sf::Sprite, STATE> m_animator;		//!<This is the THOR::Animator for stepping through a sprite sheet

	Projectile();
	Projectile(b2Body* b, bool dir, STATE type);
	Projectile(b2Body* b, sf::Vector2f dir);
	Projectile(b2Body* b, sf::Vector2f dir, STATE type);
	Projectile(b2Body* b, sf::Vector2f dir, STATE type, string type_id);
	~Projectile();

	void init();

	virtual void update();
	void render(sf::RenderWindow &w, sf::Time frames);
	virtual void loadMedia();

	virtual void Die();
	virtual void alineSprite();
	/**
	*	@brief This adds a single thor::FrameAnimation to the animator.
	*	@param thor::FrameAnimation The FrameAnimation to add the custom frame too.
	*	@param STATE The state of the block to find the y offset of the image.
	*	@param xFirst The X of the first frame.
	*	@param xLast The X of the last frame.
	*	@param xSep The X seperation of frames.
	*	@param ySep The Y seperation of frames.
	*	@param duration The duration of the frames.
	*/
	void addFrames(thor::FrameAnimation& animation, int x, int yFirst, int yLast, int xSep, int ySep, float duration);
	void checkAnimation();

	void correctRotation(sf::Vector2f dir);

	bool isAlive() { return m_body_active; }
	void setAlive(bool b) { m_body_active = b; }
	bool canDespawn() { return can_despawn; }
	b2Body* getBody() { return m_box_body; }
	void setBody(b2Body* b) { m_box_body = b; }

	void applySpeed();
	bool getBoolDirection();
	
};

class Bone : public Projectile {
private:
	string s_texture;
	sf::Vector2f m_size;
	bool m_direction;
public:
	Bone(b2Body*b, bool dir) {
		b->SetUserData(this);
		loadMedia();
		m_spawn_point = vHelper::toSF(b->GetPosition());
		if (dir)			b->ApplyForce(b2Vec2(30, -60), b->GetPosition(), true);
		else 				b->ApplyForce(b2Vec2(-30, -60), b->GetPosition(), true);
		setBody(b);
		m_direction = dir;
	}
	Bone(b2Body*b, b2Vec2 force) {
		b->SetUserData(this);
		loadMedia();
		m_spawn_point = vHelper::toSF(b->GetPosition());
		b->ApplyForce(b2Vec2(force.x, force.y), b->GetPosition(), true);
		setBody(b);
		m_direction = true;
	}
	void Die() override {
		setAlive(false);
		m_box_body->GetFixtureList()->SetSensor(true);
	}
	void update() override {
		alineSprite();
		if (vHelper::distance(getPosition(), m_spawn_point) > 1000) {
			Die();
		}
	}
	void alineSprite() override {
		setPosition(vHelper::toSF(m_box_body->GetPosition()));

		float r = getRotation();
		r += 1.5f;
		setRotation(r);
	}
	void loadMedia() {
		s_texture = "Assets/Game/bone.png";
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		m_size = sf::Vector2f(16, 16);
		setOrigin(m_size.x / 2, m_size.y / 2);
	}
};

#endif