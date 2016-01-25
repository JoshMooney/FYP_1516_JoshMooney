#ifndef _SCENERY_HPP
#define _SCENERY_HPP
#include "stdafx.h"
#include <algorithm>
#include "SFML\Graphics\RenderWindow.hpp"
#include "vCamera.hpp"
#include "ParallaxSprite.hpp"

/**
*	@struct BGSorter
*	@brief Is a short struct used as a sorting operator for the backgound images sorting 
*	the ParallaxSprite's passed in from back to front. 
*/

/**
*	@struct FGSorter
*	@brief Is a short struct used as a sorting operator for the backgound images sorting
*	the ParallaxSprite's passed in from front to back.
*/

/**
*	@class Scenery
*	@brief This class manages the paralax background for the game by storing two vectors of ParallaxSprite 
*	one for Background images and another for the Foreground
*/
class Scenery{
private:
	vector<ParallaxSprite> bg;
	vector<ParallaxSprite> fg;
public:
	/**
	*	@brief This is the default constructor for the scenery class
	*/
	Scenery();
	~Scenery();
	
	/**
	*	@brief This renders all the background textures in the order of the vector 
	*	and calculates the appropreate x and y axis offset to achieve the parallax effect. 
	*	@param sf::RenderWindow This is the SFML Render window being used by the game and which is to be rendered to.
	*	@param vCamera This is the game camera to set the ParallaxSprite offset to.
	*/
	void renderBG(sf::RenderWindow &w, vCamera *cam);
	/**
	*	@brief This renders all the foreground textures in the order of the vector 
	*	and calculates the appropreate x and y axis offset to achieve the parallax effect. 
	*	@param sf::RenderWindow This is the SFML Render window being used by the game and which is to be rendered to.
	*	@param vCamera This is the game camera to set the ParallaxSprite offset to.
	*/
	void renderFG(sf::RenderWindow &w, vCamera *cam);
	/**
	*	@brief This function uses std::sort and BGSorter to organise the bakcgrounds
	*	from back to front. This method should be called whenever all the backgrounds have been
	*	added to the Scenery class.
	*/
	void sortBG();
	/**
	*	@brief This function uses std::sort and FGSorter to organise the bakcgrounds
	*	from front to back. This method should be called whenever all the backgrounds have been
	*	added to the Scenery class.
	*/
	void sortFG();
	/**
	*	@brief Adds the passed in ParallaxSprite to the background queue for rendering.
	*	To keep the ParallaxSprite in correct order ensure to call sortBG after each addition 
	*	to the new queue or once the scenerys sprites had been added. 
	*	@param ParallaxSprite Is the Sprite to be added to the background queue
	*/
	void insertBG(ParallaxSprite &ps);
	/**
	*	@brief Adds the passed in ParallaxSprite to the foreground queue for rendering.
	*	To keep the ParallaxSprite in correct order ensure to call sortBG after each addition 
	*	to the new queue or once the scenerys sprites had been added. 
	*	@param ParallaxSprite Is the Sprite to be added to the foreground queue
	*/
	void insertFG(ParallaxSprite &ps);
	/**
	*	@brief This erases all the data held by the background and foreground queues and resets
	*	the class.
	*/
	void clear();
};

#endif