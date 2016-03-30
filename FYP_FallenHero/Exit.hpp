#ifndef _EXIT_HPP
#define _EXIT_HPP
#include "stdafx.h"
#include "ResourceManager.hpp"
#include "SFML\Graphics.hpp"

/**
*	@class Exit 
*	@brief The Exit trigger for a level when this has been tripped the level will end and the player
*	will be returned to the World map once the objecct has been tripped.
*/
class Exit : public sf::Sprite {
private:
	string s_texture;
	sf::FloatRect geometry;
public:
	/**	Is the Exit Default Constructor	*/
	Exit() {

	}
	/**	
	*	@brief This over loaded constructor is the correct function to class the default
	*	constructor is deprecated and nolonger has use for it.
	*	@param sf::Vector2f The position of the Exit trigger
	*/
	Exit(sf::Vector2f pos) {
		s_texture = "Assets/Game/exit.png";
		sf::Vector2u size = ResourceManager<sf::Texture>::instance()->get(s_texture).getSize();
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		setPosition(pos);
		geometry = { pos.x,pos.y,(float)size.x, (float)size.y };
	}
	/**	
	*	@brief Checks weather the float rectangle passed in collides with the exit.
	*	@param sf::FloatRect This is the player represented as a sf::FloatRect
	*/
	bool isCollided(sf::FloatRect player_geo) {
		if (geometry.top < player_geo.top + player_geo.width && geometry.top + geometry.width > player_geo.top &&
			geometry.left < player_geo.left + player_geo.height && geometry.height + geometry.left > player_geo.left)
			return true;
		return false;
	}
};

#endif
