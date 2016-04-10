#ifndef _LOCKED_DOOR_HPP
#define _LOCKED_DOOR_HPP
#include "stdafx.h"
#include "Enemy.hpp"
#include "Key.hpp"

#include "xboxConnector.hpp"
#include "SFML\Audio.hpp"
#include "Thor\Animations.hpp"
#include <map>

class Door : public Enemy {
private:
	sf::Vector2u m_size;
	float m_dis_to_player;

	bool m_controller_input, m_prev_ci;
	bool m_can_prompt;
	bool m_prompt_active;
	string s_prompt_spt;
	sf::Sprite m_prompt_spt;
	sf::Vector2f m_prompt_pos;
	string m_id;
	map<string, bool> m_req_keys;
	bool m_lock;

	//Animations
	thor::FrameAnimation frame_locked;
	thor::FrameAnimation frame_unlock;
	thor::FrameAnimation frame_fade_out;
	thor::FrameAnimation frame_fade_in;
	thor::FrameAnimation frame_hidden;

	//Audio
	string s_unlock, s_locked, s_cant_open, s_hit;
	sf::Sound m_unlock, m_locked, m_cant_open, m_hit;
public:
	enum TYPE {
		GOLD,		//!<
		SIL,		//!<
		BLU,		//!<
		GRN,		//!<
	};
	TYPE m_type;
	enum STATE {
		OPEN, 		//!<
		LOCKED,		//!<
		UNLOCK, 	//!<
		FADE_OUT,	//!<
		FADE_IN,	//!<
		HIDDEN,		//!<
	};
	STATE m_current_state, m_previous_state;
	thor::Animator<sf::Sprite, STATE> m_animator;

	Door();
	Door(b2Body *b, string id, vector<string> *keys);
	~Door();

	void update(FTS fts, Player *p);
	void render(sf::RenderWindow &w, sf::Time frames);
	void loadMedia();

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
	*	@brief This checks the current animation and changes the state of the animation
	*	depending on the flags currently raised and the state of the unit.
	*/
	void checkAnimation();

	sf::FloatRect getBounds() override {
		sf::Vector2f position(getPosition().x - (m_size.x / 2), getPosition().y - (m_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
	}
	void alineSprite();
	void TakeDamage();
	void Die();

	void attack();
	bool checkKeys(vector<string> *collected);
	bool isPrompted() { return m_prompt_active; }
	void changePrompt();
	string getID() { return m_id; }
	bool canUnlock();

	void unlock();
	void lock();
	bool isLocked() { return m_lock; }
	void setLock(bool b) { m_lock = b; }
};

#endif