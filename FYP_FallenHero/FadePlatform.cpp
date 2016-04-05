#include "stdafx.h"
#include "FadePlatform.hpp"

FadePlatform::FadePlatform() {	}

FadePlatform::FadePlatform(b2Body * b) {
	m_box_body = b;
	m_box_body->SetUserData(this);
	m_body_active = true;

	fade_in = 3;
	fade_out = 3;

	loadMedia();

	alineSprite();
}

FadePlatform::FadePlatform(b2Body * b, float f_in, float f_out) {
	m_box_body = b;
	m_box_body->SetUserData(this);
	m_body_active = true;

	fade_in = f_in;
	fade_out = f_out;

	loadMedia();

	alineSprite();
	m_timer.restart();
}

FadePlatform::FadePlatform(b2Body * b, float f_in, float f_out, float a_sec, float d_sec) {
	m_box_body = b;
	m_box_body->SetUserData(this);
	m_body_active = true;

	fade_in = f_in;
	fade_out = f_out;
	alive_sec = a_sec;
	dead_sec = d_sec;

	loadMedia();

	alineSprite();
	m_timer.restart();
}

FadePlatform::~FadePlatform() {		}

void FadePlatform::update(FTS fts) {
	sf::Color colour = getColor();
	elapsed_time = m_timer.getElapsedTime();
	float perframe;
	float alpha;
	if (fading) {
		if (fade_step) {
			perframe = 255.0 / fade_in;
			alpha = elapsed_time.asSeconds() * perframe;
			alpha = 255.0 - alpha;

			if (elapsed_time.asSeconds() > fade_in) {
				fade_step = !fade_step;
				fading = false;
				m_timer.restart();
				elapsed_time = sf::Time::Zero;
			}
			if (elapsed_time.asSeconds() > (fade_in / 4.0) *3) {
				m_box_body->GetFixtureList()->SetSensor(true);
			}
		}
		else if (!fade_step) {
			perframe = 255.0 / fade_out;
			alpha = elapsed_time.asSeconds() * perframe;

			if (elapsed_time.asSeconds() > fade_out) {
				fade_step = !fade_step;
				fading = false;
				m_timer.restart();
				elapsed_time = sf::Time::Zero;
			}
			if (elapsed_time.asSeconds() > (fade_out / 4.0)) {
				m_box_body->GetFixtureList()->SetSensor(false);
			}
		}
	}
	else {
		alpha = colour.a;
		if (fade_step)
			if (elapsed_time.asSeconds() > alive_sec) {
				fading = true;
				m_timer.restart();
				elapsed_time = sf::Time::Zero;
			}
		if (!fade_step)
			if (elapsed_time.asSeconds() > dead_sec) {
				fading = true;
				m_timer.restart();
				elapsed_time = sf::Time::Zero;
			}
	}

	
	colour.a = alpha;
	
	setColor(colour);
}

void FadePlatform::render(sf::RenderWindow & w, sf::Time frames) {
	w.draw(*this);
}

void FadePlatform::loadMedia() {
	s_texture = "Assets/Game/fade_platform.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(s_texture);
	m_size = sf::Vector2u(160, 16);
	setOrigin(m_size.x / 2, m_size.y / 2);
}
