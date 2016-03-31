#ifndef _PLAYER_ICON_HPP
#define _PLAYER_ICON_HPP
#include "stdafx.h"
#include "ResourceManager.hpp"
#include "SFML\Graphics.hpp"

/**
*	@class PlayerIcon
*	@brief This is the players icon that can be seen on the WorldMap scene. It represents the players character 
*	as they move across the game world and progress onto new levels.
*
*/
class PlayerIcon : public sf::Sprite {
private:
	
public:
	string s_texture;		//!<A string to the path of the texture. Which will then be used by the ResourceManager to either load in or fetch the asset for use.
	bool is_moving;         //!<Whether or not the indicator is moving 
	string m_lvl_tag;       //!<The ID tag assoicated with the level the icon is currently on.

	/**
	*	@brief The default constructor for the PlayerIcon, this initalises all the variables approprately
	*/
	PlayerIcon(){
		is_moving = false;
		m_lvl_tag = "LVL_1";
		s_texture = "Assets/World/player_icon.png";

		loadMedia();
	}
	void update() {

	}
	/**
	*	@brief To play a sound and animation when the player attempts to move in a direction that is blocked or locked off to the player
	*/
	void bump(string direction){

	}
	/**
	*	@brief Calls load on the ResourceManager using s_texture
	*/
	void loadMedia(){
		setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
		sf::Vector2u size = ResourceManager<sf::Texture>::instance()->get(s_texture).getSize();
		setOrigin(size.x / 2, size.y / 2);
	}
	/**
	*	@brief Sets the center of the sf::Sprite instead of the top left corner as is standerd. I find it easier when working with small classes like this
	*/
	void setCenter(sf::Vector2f v)	{
		setPosition(v);
	}
	//!Fetchs the m_lvl_tag
	string& getTag()	{ return m_lvl_tag; }
	//!Sets the m_lvl_tag to a new passed in string s
	void setTag(string s)	{ m_lvl_tag = s; }
	//!A call to check is_moving
	bool moving()	{ return is_moving; }
};

#endif