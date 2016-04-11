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

	thor::FrameAnimation frame_idle;
	thor::FrameAnimation frame_trip;
	thor::FrameAnimation frame_active;

	bool m_first_trip;

	void init() {
		m_first_trip = false;
		m_current_state = IDLE;

		getBody()->GetFixtureList()->SetUserData("Checkpoint");
		getBody()->SetUserData(this);

		//Load Texture
		s_texture = "Assets/Game/cp_ps.png";
		m_text_size = sf::Vector2u(42, 94);
		m_sprite.setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		m_sprite.setOrigin(m_text_size.x / 2, m_text_size.y / 2);
		m_sprite.setPosition(vHelper::toSF(getBody()->GetPosition()));

		addFrames(frame_idle,	0, 0, 1, 42, 94, 1.0f);
		addFrames(frame_trip,	1, 0, 5, 42, 94, 1.0f);
		addFrames(frame_active, 2, 0, 3, 42, 94, 1.0f);

		m_animator.addAnimation(IDLE,	frame_idle,		sf::seconds(1.0f));
		m_animator.addAnimation(TRIP,	frame_trip,		sf::seconds(0.4f));
		m_animator.addAnimation(ACTIVE, frame_active,	sf::seconds(0.3f));

		//Load Audio
		s_noise = "Assets/Audio/Game/cp.wav";
		m_noise.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_noise));
	}
public:
	enum STATE { IDLE, TRIP, ACTIVE };
	STATE m_current_state;
	thor::Animator<sf::Sprite, STATE> m_animator;
	Checkpoint()	{	}
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*	@param
	*/
	Checkpoint(b2World *w, sf::Vector2f pos, sf::Vector2u size) : Sensor(w, pos, size), m_text_size(size) {
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
	Checkpoint(b2World *w, sf::Vector2f pos, sf::Vector2u size, string id) : Sensor(w, pos, size, id), m_text_size(size) {
		init();

	}

	/**
	*	@brief 
	*/
	void trip() override {
		setTrip(true);

		m_first_trip = true;
		m_noise.play();
		m_current_state = TRIP;
		m_animator.playAnimation(TRIP);
	}

	void update() {
		if (hasTripped() && body_active) {
			getBody()->GetWorld()->DestroyBody(getBody());
			body_active = false;
		}
	}

	bool firstTrip() {
		if (m_first_trip && hasTripped()) {
			return hasTripped();
			m_first_trip = false;
		}
		return false;
	}

	void addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
		if (y == 0)
			y = 0;
		else if (y == 1)
			y = 94;
		else if (y == 2)
			y = 188;

		for (int x = xFirst; x != xLast; x += 1)
			animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));
	}

	void checkAnimation() {
		if (m_current_state == IDLE)
			m_animator.playAnimation(IDLE);
		else if (m_current_state == TRIP && !m_animator.isPlayingAnimation())
			m_current_state = ACTIVE;
		else if (m_current_state == ACTIVE && !m_animator.isPlayingAnimation())
			m_animator.playAnimation(ACTIVE);
	}

	void render(sf::RenderWindow &w, sf::Time frames) {
		checkAnimation();

		m_animator.update(frames);
		m_animator.animate(m_sprite);
		w.draw(m_sprite);
	}
};

#endif
