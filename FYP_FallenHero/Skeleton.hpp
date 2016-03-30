#ifndef _SKELETON_HPP
#define _SKELETON_HPP
#include "stdafx.h"

#include "Terrain.hpp"
#include "Enemy.hpp"
#include "Thor\Animations.hpp"

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

public:
	enum AI { WHITE, GREY, BLACK };
	AI ai;
	enum STATE {WALKING, ATTACKING, IDLE, DEATH};
	STATE m_current_state, m_previous_state;
	thor::Animator<sf::Sprite, STATE> m_animator;

	Skeleton();
	Skeleton(b2Body *b, sf::Vector2f pos, bool dir);
	Skeleton(b2World *world);
	void init();

	void ChangeState(STATE s);
	void loadMedia();
	void checkAnimation();
	void addFrames(thor::FrameAnimation& animation, int x, int yFirst, int yLast, int xSep, int ySep, float duration);
	void update(FTS fts, Player *p);
	void render(sf::RenderWindow &w, sf::Time frames);

	void TakeDamage() override;
	void Die() override;
	void assignBody(b2Body *b) { e_box_body = b; }
	void move();
	void attack();
	void alineSprite();
	void ChangeDirection();
	void setDirection(bool b);
	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }
	sf::Vector2u getTextureSize() { return m_text_size; }
	void isTouching(Terrain* t);
	void ReachedEdge();
	void ReachPlayer();
	void ReachWall();
	sf::FloatRect getBounds() override {
		sf::Vector2f position(getPosition().x - (m_text_size.x / 2), getPosition().y - (m_text_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_text_size.x, (float)m_text_size.y };
	}
};

#endif