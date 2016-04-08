#ifndef _ACHIEVEMENTS_HPP
#define _ACHIEVEMENTS_HPP
#include "Observer.hpp"

#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "SaveSlot.hpp"
#include <memory>
#include <iostream>
#include <queue>

/**
*	@class Achievements
*	@brief
*/
class Achievements : public Observer {
public:
	/**
	*	@brief
	*/
	Achievements();
	/**
	*	@brief
	*/
	Achievements(SaveSlot *cur);

	/**
	*	@brief
	*/
	~Achievements();
	/**
	*	@brief
	*/
	void onNotify(Subject::EVENT evnt, Entity *entity) override;
	/**
	*	@brief
	*/
	void update() override;
	/**
	*	@brief
	*/
	void render(sf::RenderWindow *w) override;
private:
	void unlock(Subject::EVENT e);

	SaveSlot *m_current_slot;
	sf::Sprite m_cheevo;
	sf::Vector2f m_cheevo_size;
	sf::Clock m_cheevo_clock;
	sf::Vector3f m_cheevo_colour;
	sf::Vector2f m_border_sep;
	queue<sf::Sprite> m_queue;
	float m_cheevo_fade;

	bool first_jump;
};

#endif