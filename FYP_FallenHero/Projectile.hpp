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
	b2Body *m_box_body;     
	sf::Vector2f m_direction;
	bool can_despawn;
	thor::FrameAnimation frame_fire;
	thor::FrameAnimation frame_fire_bu;
	thor::FrameAnimation frame_fire_rd;
	thor::FrameAnimation frame_explode;
public:
	enum STATE {
		FIRE,
		BLUE,
		RED,
		EXPLODE
	};

	STATE m_current_state, m_previous_state;

	sf::Vector2f m_spawn_point;
	thor::Animator<sf::Sprite, STATE> m_animator;		//!<This is the THOR::Animator for stepping through a sprite sheet

	Projectile();
	Projectile(b2Body* b, sf::Vector2f dir);
	Projectile(b2Body* b, sf::Vector2f dir, STATE type);
	~Projectile();

	void init();

	void update();
	void render(sf::RenderWindow &w, sf::Time frames);
	void loadMedia();

	void Die();
	void alineSprite();
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

	bool isAlive() { return m_body_active; }
	bool canDespawn() { return can_despawn; }
	b2Body* getBody() { return m_box_body; }

	void applySpeed();
	bool getBoolDirection();
	
};

#endif