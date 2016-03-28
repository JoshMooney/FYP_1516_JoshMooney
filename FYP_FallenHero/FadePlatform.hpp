#ifndef _FADE_PLATFORM_HPP
#define _FADE_PLATFORM_HPP
#include "stdafx.h"
#include "Platform.hpp"

class FadePlatform : public Platform {
private:
	float fade_in;
	float fade_out;
	float alive_sec;
	float dead_sec;

	bool fade_step;
	bool fading;
	//float alpha;
	sf::Clock m_timer;
	sf::Time elapsed_time;
public:
	FadePlatform();
	FadePlatform(b2Body* b);
	FadePlatform(b2Body* b, float f_in, float f_out);
	FadePlatform(b2Body* b, float f_in, float f_out, float a_sec, float d_sec);
	~FadePlatform();

	void update(FTS fts);
	void render(sf::RenderWindow &w, sf::Time frames);
	void loadMedia();
};

#endif