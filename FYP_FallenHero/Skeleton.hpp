#ifndef _SKELETON_HPP
#define _SKELETON_HPP
#include "stdafx.h"

#include "Terrain.hpp"
#include "Enemy.hpp"
#include "Thor\Animations.hpp"
#include "ProjectileManager.hpp"

/**
*	@class Skeleton 
*	@brief This is the ground enemy for the gamme and will need to hold multiple animations,
*	AI's and information about the gameworld.
*/
class Skeleton : public Enemy {
private:
	sf::Vector2u m_text_size;
	float m_speed;
	Terrain* touching_terr;
	float speedFactor;
	thor::FrameAnimation frame_walk;
	thor::FrameAnimation frame_attack;
	thor::FrameAnimation frame_idle;
	thor::FrameAnimation frame_death;
	string s_death;
	sf::Sound m_death;
	ProjectileManager * projectile_mgr;

	b2Vec2 low_lob;
	b2Vec2 high_lob;

	bool back_and_forth;
	sf::Clock m_fire_clock;
	bool can_fire;
	float cooldown_time;
public:
	//!The three types of AI the Skeleton can use
	enum AI { 
	WHITE,		//!<White AI :
	GREY,       //!<Grey AI:
	BLACK       //!<Black AI:
	};
	AI m_ai;		//!<The current AI of the Skeleton
	//!The three types of Animations the Skeleton can use
	enum STATE {
		WALKING, 	//!<Walking animation for walking arounds
		ATTACKING,  //!<Attacking stop walking and attack 
		IDLE, 		//!<The Idle for when the unit is standing still.
		DEATH     	//!<The deayj animation
	};
	STATE m_current_state;		//!<The Current animation state of the unit
	STATE m_previous_state;		//!<The Current animation state of the unit
	thor::Animator<sf::Sprite, STATE> m_animator;		//!<This is the THOR::Animator for stepping through a sprite sheet

	/**
	*	@brief The default constructor for the skeleton enemy. This method is
	*	a old method of creating the skeleton use the overloadded construcror
	*	@see Skeleton::Skeleton(b2Body *b, sf::Vector2f pos, bool dir)
	*/
	Skeleton();
	/**
	*	@brief This is the overloaded method for the skeleton enemy class where
	*	the skeleton takes everything required for creation this method will be
	*	located inside of the SpawnSkeleton function inside the spawner
	*	@see Spawn::SpawnSkeleton
	*	@param b2Body This is the Box2D body assocated with the entity.
	*	@param bool This direction the Skeleton is facing and will begin the to walk in.
	*/
	Skeleton(b2Body *b, bool dir, AI ai);
	/**
	*	@brief This is the overloaded method for the skeleton enemy class where
	*	the skeleton takes everything required for creation this method will be
	*	located inside of the SpawnSkeleton function inside the spawner
	*	@see Spawn::SpawnSkeleton
	*	@param b2Body This is the Box2D body assocated with the entity.
	*	@param bool This direction the Skeleton is facing and will begin the to walk in.
	*/
	Skeleton(b2Body *b, bool dir, AI ai, ProjectileManager *pj);
	/**
	*	@brief This is and even older way of creating the Skeleton where the enemy
	*	creates its own body.
	*	@param b2World This is the Box2D world for the enemy to create its own boxbody.
	*/
	Skeleton(b2World *world);
	/**
	*	@brief Initalises the enemy class and all its variables
	*/
	void init();

	/**
	*	@brief This changes the animation state of the enemy to the passed in STATE
	*	@param STATE The state to change the animation to.
	*/
	void ChangeState(STATE s);
	/**
	*	@brief Load all the animations frames, images and audio for the enemy class
	*/
	void loadMedia();
	/**
	*	@brief This checks the current animation and changes the state of the animation 
	*	depending on the flags currently raised and the state of the unit.
	*/
	void checkAnimation();
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

	/**
	*	@brief This updates the unit in any way possible. The function calls the checkAnimation
	*	to keep the animation in step as well as alines the sprite.
	*	@param FTS The Fixed time step to update the entity with.
	*/
	void update(FTS fts, Player *p);
	/**
	*	@brief This renders the enemy to the SFML window.
	*	@param sf::RenderWindow This is the SFML window to render everything to.
	*	@param sf::Time The elapsed time used for progressing the Animator.
	*/
	void render(sf::RenderWindow &w, sf::Time frames);

	/**
	*	@brief This is the take damage funtion where the unit takes flat damage
	*/
	void TakeDamage() override;
	/**
	*	@brief This kills the unit and raises the flag to detroy body.
	*/
	void Die() override;
	/**
	*	@brief Attach the body to the unit
	*	@param b2Body The box2d body to attach.
	*/
	void assignBody(b2Body *b) { e_box_body = b; }
	/**
	*	@brief This advances the unit a step using there direction and speed.
	*/
	void move();
	/**
	*	@brief Attack and play the attack animaiton
	*/
	void attack();
	/**
	*	@brief Position the sprite with the boxbody.
	*/
	void alineSprite();
	/**
	*	@brief Change the direction of the enemy and flip the sprite so the
	*	texture is reversed.
	*/
	void ChangeDirection();
	/**
	*	@brief Set the direction of the unit which also calss the ChangeDirection
	*	function.
	*/
	void setDirection(bool b);
	/**
	*	@brief Fetches the center of the unit and returns it as a float vector
	*	@return sf::Vector2f The center of the unit.
	*/
	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }
	/**
	*	@brief Gets the width and height of the texture in a sf::Vector2u
	*	@return sf::Vector2u The Width and Height of the texture of the unit.
	*/
	sf::Vector2u getTextureSize() { return m_text_size; }
	/**
	*	@brief Sets the terrrain toucher to the terrain passed in.
	*	@param Terrain* The terrain the unit is touching.
	*/
	void isTouching(Terrain* t);
	/**
	*	@brief Tell the unit it has reached the edge.
	*/
	void ReachedEdge();
	/**
	*	@brief Tell the unit it has reached the player
	*/
	void ReachPlayer();
	/**
	*	@brief Tell the unit it has reached the player
	*/
	void ReachWall();
	/**
	*	@brief Create a rectangle
	*	@return sf::FloatRect The boundaries of the skeleton 
	*/
	sf::FloatRect getBounds() override {
		sf::Vector2f position(getPosition().x - (m_text_size.x / 2), getPosition().y - (m_text_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_text_size.x, (float)m_text_size.y };
	}

	void CheckFire();
};

#endif