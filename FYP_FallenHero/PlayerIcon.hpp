#ifndef _PLAYER_ICON_HPP
#define _PLAYER_ICON_HPP
#include "stdafx.h"
#include "ResourceManager.hpp"
#include "SFML\Graphics.hpp"

class PlayerIcon : public sf::Sprite {
private:
	
public:
	string s_texture;
	bool is_moving;
	string m_lvl_tag;

	PlayerIcon(){
		is_moving = false;
		m_lvl_tag = "LVL_1";
		s_texture = "Assets/World/playericon.png";

		loadMedia();
	}
	void update() {

	}
	void bump(string direction){

	}
	void loadMedia(){
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	}
	void setCenter(sf::Vector2f v)	{
		sf::Vector2u size = ResourceManager<sf::Texture>::instance()->get(s_texture).getSize();
		sf::Vector2f pos = getPosition();
		setPosition(sf::Vector2f(v.x - size.x / 2, v.y - size.y / 2));
	}

	string& getTag()	{ return m_lvl_tag; }
	void setTag(string s)	{ m_lvl_tag = s; }
	bool moving()	{ return is_moving; }
};

#endif