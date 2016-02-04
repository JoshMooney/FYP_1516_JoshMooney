#ifndef SCENE_HPP
#define SCENE_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include <vector>
#include <string>
#include <map>
#include "XBOXController.hpp"

/** \struct Scene
  * \brief This is a C++ abstract class, where one or more of its methods are pure virtual and such must
  * be overloaded in any inheriting classes i.e. MenuScene must have a menuScene.update()
  */
struct Scene{
	//Key Maps
	map<string, bool> s_key_map;			//!<This is used for storing any pressed keys this scene and holding them for use later in any of the inheriting scenes
	map<string, bool> s_prev_key_map;		//!<This is used for storing any previously pressed keys this scene and holding them for use later in any of the inheriting scenes. You can compair this variable to s_key_map to find held keys if required.

	//Pure virtual Funcitons
	virtual void update() = 0;									//!<This is a pure virtual funciton for update, which must be overloaded in any inheriting classes
	virtual void render(sf::RenderWindow &w) = 0;				//!<This is a pure virtual funciton for render, which must be overloaded in any inheriting classes
	virtual void handleEvent(sf::Event &e) = 0;					//!<This is a pure virtual funciton for handleEvent, which must be overloaded in any inheriting classes
	virtual void handleInput(XBOXController &controller) = 0;	//!<This is a pure virtual funciton for handleInput, which must be overloaded in any inheriting classes
};

#endif