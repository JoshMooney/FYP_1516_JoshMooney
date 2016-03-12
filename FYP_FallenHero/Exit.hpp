#ifndef _EXIT_HPP
#define _EXIT_HPP
#include "stdafx.h"
#include "ResourceManager.hpp"
#include "SFML\Graphics.hpp"
#include "vHelper.hpp"
#include "Sensor.hpp"
#include "Thor\Animations.hpp"

/**
*	@class Exit
*	@brief
*/
class Checkpoint : public Sensor {
private:
	string s_texture;
	sf::Sprite m_sprite;
	sf::Vector2u m_text_size;
	string s_noise;
	sf::Sound m_noise;

	thor::FrameAnimation frame_walk;
	thor::FrameAnimation frame_attack;
	thor::FrameAnimation frame_idle;
	thor::FrameAnimation frame_death;
	thor::Animator<sf::Sprite, STATE> m_animator;

	void init() {
		getBody()->SetUserData("Checkpoint");

		m_sprite.setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		m_sprite.setOrigin(m_text_size.x / 2, m_text_size.y / 2);
		m_sprite.setPosition(vHelper::toSF(getBody()->GetPosition()));


	}
public:
	enum STATE { ON, OFF };
	STATE m_current_state;
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*	@param
	*/
	Checkpoint(b2World *w, sf::Vector2f pos, sf::Vector2u size, string text) : Sensor(w, pos, size), s_texture(text), m_text_size(size) {
		init();
		
	}
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*	@param
	*	@param
	*/
	Checkpoint(b2World *w, sf::Vector2f pos, sf::Vector2u size, string text, string id) : Sensor(w, pos, size, id), s_texture(text), m_text_size(size) {
		init();

	}

	/**
	*	@brief 
	*/
	void trip() override {
		setTrip(true);
	}

	void addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
		/*if (y == 0)
			y = 0;
		else if (y == 1)
			y = 47;
		else if (y == 2)
			y = 91;
		else if (y == 3)
			y = 135;

		for (int x = xFirst; x != xLast; x += 1)
			animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));*/
	}

	void render(sf::RenderWindow &w, sf::Time frames) {
		//m_animator.update(frames);
		//m_animator.animate(*m_sprite);
		w.draw(m_sprite);
	}
};

#endif
