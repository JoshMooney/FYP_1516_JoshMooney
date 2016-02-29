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
	enum TYPE {B_10, P_20, O_50,R_100, B_150, W_250};
	TYPE type_;
	/**
	*	@brief 
	*/
	Gem();
	/**
	*	@brief
	*/
	Gem(b2Body *b, sf::Vector2f pos, TYPE t);
	/**
	*	@brief
	*/
	~Gem();

	/**
	*	@brief
	*/
	void init();
	/**
	*	@brief
	*/
	void loadMedia();
	/**
	*	@brief
	*/
	void update(FTS fts);

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

	bool canDespawn()	{ return !(m_pickup.getStatus() == sf::Sound::Playing); }
};

#endif