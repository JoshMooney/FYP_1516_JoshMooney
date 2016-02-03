#ifndef _CRUMBLE_BLOCK_HPP
#define _CRUMBLE_BLOCK_HPP
#include "stdafx.h"
#include "Enemy.hpp"
#include "Thor\Animations.hpp"

class CrumbleBlock : public Enemy {
private:
	string s_hit;
	string s_destroy;
	sf::Sound m_hit;
	sf::Sound m_destroy;
	thor::FrameAnimation frame_dead;
	thor::FrameAnimation frame_alive;
	thor::FrameAnimation frame_crumble;
	sf::Vector2u m_text_size;
public:
	enum STATE { ALIVE, CRUMBLE, DEAD };
	STATE m_current_state, m_previous_state;
	enum TYPE { SAND, DIRT, ROCK };
	TYPE m_type;
	enum SIZE { SMALL, LARGE };
	SIZE m_size;
	thor::Animator<sf::Sprite, STATE> m_animator;

	CrumbleBlock();
	CrumbleBlock(b2Body *b, sf::Vector2f pos, TYPE t, SIZE s);
	~CrumbleBlock();

	void loadMedia();

	void checkAnimation();
	void addFrames(thor::FrameAnimation& animation, STATE s, int xFirst, int xLast, int xSep, int ySep, float duration);
	
	void alineSprite() override;
	void TakeDamage() override;
	void Die() override;
	void init();

	void update(FTS fts);
	void render(sf::RenderWindow &w, sf::Time frames);

	sf::Vector2u getTextureSize() { return m_text_size; }
	sf::FloatRect getBounds() override  {
		sf::Vector2f position(getPosition().x - (m_text_size.x / 2), getPosition().y - (m_text_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_text_size.x, (float)m_text_size.y };
	}
};

#endif