#ifndef _EXIT_HPP
#define _EXIT_HPP
#include "stdafx.h"
#include "ResourceManager.hpp"
#include "SFML\Graphics.hpp"

class Exit : public sf::Sprite {
private:
	string s_texture;
	sf::FloatRect geometry;
public:
	Exit() {

	}
	Exit(sf::Vector2f pos) {
		s_texture = "Assets/Game/exit.png";
		sf::Vector2u size = ResourceManager<sf::Texture>::instance()->get(s_texture).getSize();
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		setPosition(pos);
		geometry = { pos.x,pos.y,(float)size.x, (float)size.y };
	}
	bool isCollided(sf::FloatRect player_geo) {
		if (geometry.top < player_geo.top + player_geo.width && geometry.top + geometry.width > player_geo.top &&
			geometry.left < player_geo.left + player_geo.height && geometry.height + geometry.left > player_geo.left)
			return true;
		return false;
	}
};

#endif
