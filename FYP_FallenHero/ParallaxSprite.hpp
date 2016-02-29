#ifndef _PARALLAX_SPRITE_HPP
#define _PARALLAX_SPRITE_HPP
#include "stdafx.h"
#include "SFML\Graphics\View.hpp"
#include "SFML\System\Vector3.hpp"
#include "ResourceManager.hpp"

/**
*	@class ParallaxSprite
*	@brief This is a wrapped for the SFML Sprite class. This class inherits from sf::Sprite
*	and uses a Vector3f instead of the V2f with the z component being used as the scale of 
*	parallax on the surface.
*/
class ParallaxSprite : public sf::Sprite {
private:
	string s_texture;			
	sf::Vector3f position;      

public:
	/**
	*	@brief Is the default constructor for a parallax sprite.
	*/
	ParallaxSprite(){	}
	/**
	*	@brief Overloaded constructor for the parallax sprite. The resource manager
	*	will be responcible for loading the asset at the path passed in as a string.
	*	@param string The path to the texture to be loaded.
	*	@param sf::Vector3f The x&y position and z for the parallax scale.
	*/
	ParallaxSprite(string text, sf::Vector3f pos) : s_texture(text), position(pos){
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		setPosition(position.x, position.y);
	}

	sf::Vector3f getDefaultPosition()	{ return position; }		//!<Gets the position of the sprite
	void setDefaultPosition(sf::Vector3f p)	{ position = p; }       //!<Sets the default position of the sprite.
};

#endif