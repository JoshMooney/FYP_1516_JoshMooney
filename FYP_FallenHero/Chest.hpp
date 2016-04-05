#ifndef _CHEST_HPP
#define _CHEST_HPP
#include "stdafx.h"
#include "Enemy.hpp"
#include "Thor\Animations.hpp"
#include "GemMine.hpp"
#include "Entity.hpp"
#include <memory>

class Lock : public Entity {
private:
	sf::IntRect lock_pos;
	sf::Vector2f spawn_pos;
public:
	Lock(b2Body *b, bool dir, string text);
	~Lock();
	void update(FTS fts);
	void render(sf::RenderWindow &w);
	void alineSprite();
};

class Chest : public Enemy {
private:
	bool m_lock_alive;
	string s_open, s_hit;
	sf::Sound m_open, m_hit;
	float m_value;
	GemMine *m_mine;
	sf::Vector2u m_size;
	thor::FrameAnimation frame_open;
	thor::FrameAnimation frame_close;
	shared_ptr<Lock> m_lock;
	vector<Gem::TYPE> m_loot;
	sf::Clock m_clock;
	bool spawn_loot;
	int loot_pos;
	bool create_lock;
	float gem_timing;
	int loot_num;
	vector<Gem::TYPE>::iterator m_loot_iter;
public:
	enum TYPE {
		BROWN, 		//!<
		GREEN,		//!<
		PURPLE,		//!<
	};
	TYPE m_type;
	enum STATE {
		OPEN, 	//!<
		CLOSE,  //!<
	};
	STATE m_current_state;
	thor::Animator<sf::Sprite, STATE> m_animator;		//!<This is the THOR::Animator for stepping through a sprite sheet

	Chest();
	Chest(b2Body* bod, bool dir, GemMine *g, Chest::TYPE type);
	~Chest();

	void update(FTS fts, Player *p);
	void render(sf::RenderWindow &w, sf::Time frames);
	void loadMedia();

	sf::FloatRect getBounds() override {
		sf::Vector2f position(getPosition().x - (m_size.x / 2), getPosition().y - (m_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
	}
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

	void alineSprite();
	void TakeDamage();
	void Die();
	void calculateDrop(int amount);

	sf::FloatRect geometry() {
		sf::Vector2f position(e_box_body->GetPosition().x - (m_size.x / 2), e_box_body->GetPosition().y - (m_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
	}
};

#endif