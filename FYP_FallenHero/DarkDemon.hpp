#ifndef _DARK_DEMON_HPP
#define _DARK_DEMON_HPP
#include "stdafx.h"
#include "Enemy.hpp"

#include "ProjectileManager.hpp"
#include "Terrain.hpp"

#include "Thor\Animations.hpp"
#include "Form.hpp"

#include <memory>

class DemonAI;

namespace Prob {
	enum B_TYPE {
		AT_PLAYER,
		UP,
		DIRECT,
		DIRECT_MORE,
	};

	enum A_TYPE {
		DASH,

	};
}

/**
*	@class DarkDemon
*	@brief 
*/
class DarkDemon : public Enemy {
private:
	sf::Vector2u m_text_size;
	float m_speed;
	Terrain* touching_terr;
	float speedFactor;

	thor::FrameAnimation frame_idle;
	thor::FrameAnimation frame_dash;
	thor::FrameAnimation frame_hurt;
	thor::FrameAnimation frame_recover;
	thor::FrameAnimation frame_ready;
	thor::FrameAnimation frame_attack;
	thor::FrameAnimation frame_transform;
	thor::FrameAnimation frame_rev_transform;
	thor::FrameAnimation frame_attack_trans;
	thor::FrameAnimation frame_transform_dash;
	thor::FrameAnimation frame_rev_transform_dash;
	thor::FrameAnimation frame_attack_dash;
	thor::FrameAnimation frame_die;
	
	string s_death;
	sf::Sound m_death;

	//AI variables
	shared_ptr<DemonAI> m_ai;
	Form::ACTIONS m_action, m_prev_action;
	Form::TYPE m_type;
	bool ai_think;

	sf::Clock m_clock;
	sf::Clock m_shoot_clock;
	float shoot_cooldown;
	bool m_has_taken_action;
	bool m_has_finished_action;
	bool m_has_attacked;
	bool m_can_take_damage;
	float m_cooldown;
	sf::Vector2i attack_frame_size;
	vector<float> m_shoot_prop;
	vector<float> m_attack_prop;

	int off_wall, max_off_wall;
	ProjectileManager* m_projectile_mgr;
public:
	/**
	*	@brief
	*/
	enum STATE {
		IDLE,			//!<
		DASH,			//!<
		HURT,			//!<
		RECOVER,		//!<
		READY,			//!<
		ATTACK,			//!<
		TRANS,			//!<
		REV_TRANS,		//!<
		ATTACK_TRANS,	//!<
		TRANS_DASH,		//!<
		REV_TRANS_DASH,	//!<
		ATTACK_DASH,	//!<
		DIE,			//!<
	};
	STATE m_current_state;		//!<The Current animation state of the unit
	STATE m_previous_state;		//!<The Current animation state of the unit

	//! This is the THOR::Animator for stepping through a sprite sheet
	thor::Animator<sf::Sprite, STATE> m_animator;		

	/**
	*	@brief
	*/
	DarkDemon();
	/**
	*	@brief
	*/
	DarkDemon(b2Body* b, ProjectileManager* pm, bool dir);
	/**
	*	@brief
	*/
	~DarkDemon();

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
	void addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration);

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
	*	@brief This advances the unit a step using there direction and speed.
	*/
	void move();
	/**
	*	@brief Attack and play the attack animaiton
	*/
	void attack();
	/**
	*	@brief Attack and play the attack animaiton
	*/
	void shoot(Player* p);

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
	*	@brief 
	*/
	void setDirection(bool dir);
	/**
	*	@brief Fetches the center of the unit and returns it as a float vector
	*	@return sf::Vector2f The center of the unit.
	*/
	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }

	/**
	*	@brief Tell the unit it has reached the edge.
	*/
	void ReachedWall();
	/**
	*	@brief Tell the unit it has reached the player
	*/
	void ReachPlayer();
	/**
	*	@brief Create a rectangle
	*	@return sf::FloatRect The boundaries of the skeleton
	*/
	sf::FloatRect getBounds() override {
		sf::Vector2f position(getPosition().x - (40 / 2), getPosition().y - (44 / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_text_size.x, (float)m_text_size.y };
	}
	/**
	*	@brief
	*/
	void retract() {
		off_wall++;
		if (off_wall > max_off_wall) {
			off_wall = 0;
			finishCurrentAciton();
		}
	}
	/**
	*	@brief
	*/
	bool canThink();
	/**
	*	@brief
	*/
	bool canTakeAction();
	/**
	*	@brief 
	*/
	void takeAction();
	/**
	*	@brief Sets the terrrain toucher to the terrain passed in.
	*	@param Terrain* The terrain the unit is touching.
	*/
	void isTouching(Terrain* t);
	/**
	*	@brief
	*/
	Prob::B_TYPE chooseShoot();
	/**
	*	@brief
	*/
	Prob::A_TYPE chooseAttack();

	/**
	*	@brief 
	*/
	void finishCurrentAciton();
	/**
	*	@brief
	*/
	bool isAttacking() {
		return (m_current_state == ATTACK);
	}

	/**
	*	@brief
	*/
	sf::FloatRect getAttackBounds() {
		sf::Vector2f center = getCenter();
		if (e_direction) {
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
};

#include "AI.hpp"

#endif