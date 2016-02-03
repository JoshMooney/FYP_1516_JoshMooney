#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "stdafx.h"
#include "Entity.hpp"

#include "Box2D\Box2D.h"
#include "Thor\Animations.hpp"
#include "SFML\Audio.hpp"
#include "vHelper.hpp"

/**
*	@class Player
*	@brief This is the player class that will represent the user while in game, and will be responsable for
*	constructing, rendering and updating the player. The responce to input is handled here also. 
*/
class Player : public Entity {
private:
	bool m_is_moving;		
	bool m_is_jumping;  
	bool m_is_attacking;
	float m_speed;             
	bool m_direction;          
	sf::Vector2u m_text_size;  
	float m_acceleration;      
	float m_deceleration;      
	float m_jump_force;        
	float speedFactor;   
	bool m_alive;
	//Sound Effects
	string s_jump;
	string s_death;
	string s_finish_level;
	string s_fall;
	string s_hit;
	string s_swing;

	sf::Sound m_jump;
	sf::Sound m_death;
	sf::Sound m_finish_level;
	sf::Sound m_fall;
	sf::Sound m_hit;
	sf::Sound m_swing;
	int m_gold;
	//Animation
	thor::FrameAnimation frame_attack;
	thor::FrameAnimation frame_run;
	thor::FrameAnimation frame_idle;
	thor::FrameAnimation frame_jump;
	thor::FrameAnimation frame_hit;

	enum STATE { ATTACK, RUN, JUMP, IDLE, HIT };
	STATE m_current_state, m_previous_state;
	thor::Animator<sf::Sprite, STATE> m_animator;
	sf::Vector2i attack_frame_size;
	sf::Vector2f const knock_back_factor = sf::Vector2f(0.5f, 0.8f);
public:
	float m_xp;
	float m_max_xp;
	/**
	*	@brief Default constructor for the player where all the member variables are set and the boxbody is
	*	is created and attached to the player object. The texture is loaded and set for the player here also
	*	@param B2World Is a reference to the current box2d world 
	*/
	Player(b2World &m_world);
	~Player();

	void checkAnimation();
	void addFrames(thor::FrameAnimation& animation, STATE s, int xFirst, int xLast, int xSep, int ySep, float duration);
	void render(sf::Time frames);

	void loadMedia();
	/**
	*	@brief Updates the player in any way nessasary eg alineSprite
	*	@param FTS frame time stamp
	*/
	void update(FTS fts);
	/**
	*	@brief Check if the player is standing idle
	*/
	void Idle();
	/**
	*	@brief Make the player move left and apply speed factor 
	*/
	void moveLeft();
	/**
	*	@brief Make the player move right and apply speed factor 
	*/
	void moveRight();
	/**
	*	@brief Make the player jump
	*/
	void jump();
	/**
	*	@brief Resets the player in the game setting its direction and speedfactor 
	*	@param sf::Vector2f Set b2body and sprite to this position
	*/
	void reset(sf::Vector2f pos);
	void FallOffMap(sf::Vector2f pos);

	void attack();
	
	int getGold() { return m_gold; }
	bool isAlive() { return m_alive; }
	b2Body* getBody()	{ return e_box_body; }                                                  //!<Returns a pointer to the b2body associated with the player
	bool isMoving()	{ return m_is_moving; }		//!<Bool whether the player is moving or not
	bool isAttacking() { return m_is_attacking; }
	float getSpeed()	{ return m_speed; }                                                     //!<Finds the speed of the player
	void ChangeDirection();
	void setDirection(bool b);                                           //!<Sets the players direction to the value passed in
	bool isJumping()	{ return m_is_jumping; }   
	void setJumping(bool b) { 
		m_is_jumping = b; 
		e_box_body->GetFixtureList()->SetFriction(1.5f);
	}												//!<Checks if the player is in the jumping animation
	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }                                   //!<Finds the center of the player in Global coordinates
	void moveTo(sf::Vector2f p) {	e_box_body->SetTransform(vHelper::toB2(p), 0.0f);	}		//!<Sets the Player to the position passed in
	void TakeDamage(bool knock_dir);
	sf::Vector2u getSize() { return m_text_size; }
	/**
	*	@brief Position the players b2Body to the position passed in
	*	@param p Position
	*/
	void Spawn(sf::Vector2f p);
	
	/**
	*	@brief Finds a value between the max and min passed in 
	*	@param
	*	@param min the minimum range of the clamp
	*	@param max the maximum range of the clamp
	*	@return clamps value
	*/
	inline float clamp(float x, float min, float max);
	/**
	*	@brief Calculates and sets the position of the sf::Sprite in relation to the b2Body
	*/
	void alineSprite();
	void setIfMoving(bool b) { m_is_moving = b; }		//!<Sets the Variable m_is_moving
	/**
	*	@brief Gets a sf::FloatRect representing the bounds of the Player
	*	@return Bounds of the player
	*/
	sf::FloatRect getBounds() { 
		sf::Vector2f center = getCenter();
		return sf::FloatRect{ center.x - (m_text_size.x /2), center.y - (m_text_size.y / 2), (float)m_text_size.x, (float)m_text_size.y};
	}
	sf::FloatRect getAttackBounds() {
		sf::Vector2f center = getCenter();
		if (m_direction) {
			sf::Vector2f bot_left = sf::Vector2f(center.x - (m_text_size.x / 2), center.y + (m_text_size.y / 2));
			sf::Vector2f position = sf::Vector2f(bot_left.x, bot_left.y - attack_frame_size.y);
			return sf::FloatRect{ position.x, position.y, (float)attack_frame_size.x, (float)attack_frame_size.y };
		}
		else {
			sf::Vector2f bot_right = sf::Vector2f(center.x + (m_text_size.x / 2), center.y + (m_text_size.y / 2));
			sf::Vector2f position = sf::Vector2f(bot_right.x - attack_frame_size.x, bot_right.y - attack_frame_size.y);
			return sf::FloatRect{ position.x, position.y, (float)attack_frame_size.x, (float)attack_frame_size.y };
		}
	}
	float healthRatio() {
		return e_hp / e_max_hp;
	}
	float experienceRatio() {
		return m_xp / m_max_xp;
	}
	
};

#endif