#ifndef _LOCKED_DOOR_HPP
#define _LOCKED_DOOR_HPP
#include "stdafx.h"
#include "Enemy.hpp"

#include "SFML\Audio.hpp"
#include "Thor\Animations.hpp"

class Door : public Enemy {
private:
	sf::Vector2u m_size;
	float m_dis_to_player;
	string s_locked, s_unlock, s_hit;
	sf::Sound m_locked, m_unlock, m_hit;

	bool m_prompt_active;
	string s_prompt_spt;
	sf::Sprite m_prompt_spt;
	sf::Vector2f m_prompt_pos;
	string m_id;
public:
	enum TYPE {
		BROWN, 		//!<
	};
	TYPE m_type;
	enum STATE {
		OPEN, 	//!<
		CLOSE,  //!<
	};
	STATE m_current_state;
	thor::Animator<sf::Sprite, STATE> m_animator;

	Door();
	Door(b2Body *b, string id);
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

	sf::FloatRect getBounds() override {
		sf::Vector2f position(getPosition().x - (m_size.x / 2), getPosition().y - (m_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
	}
	void alineSprite();
	void TakeDamage();
	void Die();

	void attack();
};

#endif