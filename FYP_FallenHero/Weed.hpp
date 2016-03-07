#ifndef _WEED_HPP
#define _WEED_HPP
#include "stdafx.h"
#include "Enemy.hpp"

class Weed : public Enemy {
private:
	sf::Vector2u m_text_size;
	float speedFactor;
	float m_jump;
	string s_death;
	sf::Sound m_death;

	thor::FrameAnimation frame_excited;
	thor::FrameAnimation frame_attack;
	thor::FrameAnimation frame_idle;
	thor::FrameAnimation frame_death;

	
public:
	enum AI { GREEN, BLUE, RED };
	AI ai;
	enum STATE { ATTACKING, IDLE, DEATH, EXCITED };
	STATE m_current_state, m_previous_state;
	thor::Animator<sf::Sprite, STATE> m_animator;

	Weed();
	Weed(b2Body *b, sf::Vector2f pos, bool dir);
	~Weed();

	void TakeDamage() override;
	void Die() override;

	void checkAnimation();
	void addFrames(thor::FrameAnimation& animation, int x, int yFirst, int yLast, int xSep, int ySep, float duration);
	void loadMedia();
	void init();

	void update(FTS fts);
	void render(sf::RenderWindow &w, sf::Time frames);
	void assignBody(b2Body *b) { e_box_body = b; }
	void attack();
	void alineSprite();

	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }
	sf::Vector2u getTextureSize() { return m_text_size; }
	sf::FloatRect getBounds() override {
		sf::Vector2f position(getPosition().x - (m_text_size.x / 2), getPosition().y - (m_text_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_text_size.x, (float)m_text_size.y };
	}
};

#endif