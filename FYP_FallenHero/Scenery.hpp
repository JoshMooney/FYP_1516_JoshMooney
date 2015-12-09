#ifndef _SCENERY_HPP
#define _SCENERY_HPP
#include "stdafx.h"
#include <algorithm>
#include "SFML\Graphics\RenderWindow.hpp"
#include "vCamera.hpp"
#include "ParallaxSprite.hpp"

class Scenery{
private:
	vector<ParallaxSprite> bg;
	vector<ParallaxSprite> fg;
public:
	Scenery();
	~Scenery();

	void renderBG(sf::RenderWindow *w, vCamera cam);
	void renderFG(sf::RenderWindow *w, vCamera cam);
	void sortBG();
	void sortFG();
	void insertBG(ParallaxSprite ps);
	void insertFG(ParallaxSprite ps);
	void clear();
};


#endif