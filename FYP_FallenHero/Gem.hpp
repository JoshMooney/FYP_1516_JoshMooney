#ifndef _GEM_HPP
#define _GEM_HPP
#include "stdafx.h"
#include "Entity.hpp"
#include "Box2D\Box2D.h"

/**
*	@class Gem
*	@brief This is the coin in the game the collectible the player wants to
*	collect, which can be used to buy new weapons and armor.
*/
class Gem : public Entity {
private:
	string s_pickup;
	sf::Sound m_pickup;
	sf::IntRect m_texture_rect;
public:
	//!The Type and value of the gem when it is created.
	enum TYPE {
		B_10,		//!<Brown Gem value: 10
		P_20, 		//!<Purple Gem value: 20
		O_50,		//!<Orange Gem value: 50
		R_100, 		//!<Red Gem value: 100
		B_150, 		//!<Blue Gem value: 150
		W_250		//!<White Gem value: 250
	};
	TYPE type_;		//!<The current type of the gem
	/**
	*	@brief The unused default constructor of the Gem
	*/
	Gem();
	/**
	*	@brief Overloaded constructor taking the required components to make up a gem
	*	object.
	*	@param b2Body The box2d body associated with the object
	*	@param The position to be at.
	*	@param The type the gem is.
	*/
	Gem(b2Body *b, sf::Vector2f pos, TYPE t);
	/**
	*	@brief The deconstructor for the gem
	*/
	~Gem();

	/**
	*	@brief The initaliser for the object. Creates the nessary variables required for
	*	the class to function.
	*/
	void init();
	/**
	*	@brief Loads all the assets for the Gem object
	*/
	void loadMedia();
	/**
	*	@brief Updates the gem whatever that is for even i dont know.
	*	@param FTS The Fixed Time Step
	*/
	void update(FTS fts);
	/**
	*	@breif This gets the value of the gem, raises the required flags for despawning the object
	*	and sets the body to be a sensor.
	*	@return The value of the Gem to be added to the players gold.
	*/
	int pickup();

	/**
	*	@brief Position the sprite with the boxbody.
	*/
	void alineSprite();
	/**
	*	@brief Fetches the center of the unit and returns it as a float vector
	*	@return sf::Vector2f The center of the unit.
	*/
	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }

	/**
	*	@brief Whether or not the Gem can be despawned.
	*@return bool if it can be despawned.
	*/
	bool canDespawn()	{ return !(m_pickup.getStatus() == sf::Sound::Playing); }
};

#endif