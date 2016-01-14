#ifndef _PARALLAX_SPRITE_HPP
#define _PARALLAX_SPRITE_HPP
#include "stdafx.h"
#include "SFML\Graphics\View.hpp"
#include "SFML\System\Vector3.hpp"
#include "ResourceManager.hpp"

class ParallaxSprite : public sf::Sprite {
private:
	string s_texture;
	sf::Vector3f position;

public:
	ParallaxSprite(){	}
	ParallaxSprite(string text, sf::Vector3f pos) : s_texture(text), position(pos){
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		setPosition(position.x, position.y);
	}

	sf::Vector3f getDefaultPosition()	{ return position; }
	void setDefaultPosition(sf::Vector3f p)	{ position = p; }
};

#endif