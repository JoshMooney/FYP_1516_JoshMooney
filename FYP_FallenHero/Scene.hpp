#ifndef SCENE_HPP
#define SCENE_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <vector>
#include <string>
#include <map>
#include "XBOXController.hpp"

struct Scene{
	map<string, bool> s_key_map, s_prev_key_map;

	virtual void update() = 0;
	virtual void render(sf::RenderWindow &w) = 0;
	virtual void handleEvent(sf::Event &e) = 0;
	virtual void handleInput(XBOXController &controller) = 0;
};

#endif