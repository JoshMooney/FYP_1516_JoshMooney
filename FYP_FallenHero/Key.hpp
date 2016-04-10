#ifndef _KEY_HPP
#define _KEY_HPP
#include "stdafx.h"
#include "Entity.hpp"

class Key : public Entity {
private:
	string s_pickup;
	sf::Sound m_pickup;
	sf::IntRect m_texture_rect;
	string m_id;
	sf::Vector2u m_size;
	string m_door;
public:
	//!The Type and value of the gem when it is created.
	enum TYPE {
		GOLD,		//!<
		BLU,		//!<
		GRN,		//!<
		SIL,		//!<
	};
	TYPE m_type;		//!<The current type of the gem

	Key();
	Key(b2Body *b, Key::TYPE t, string door, string id);
	~Key();

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
	*	@brief 
	*	@param 
	*	@param
	*/
	void render(sf::RenderWindow *w, sf::Time frames);
	/**
	*	@breif This gets the value of the gem, raises the required flags for despawning the object
	*	and sets the body to be a sensor.
	*	@return The value of the Gem to be added to the players gold.
	*/
	std::pair<string, string> pickup();
	/**
	*	@brief Position the sprite with the boxbody.
	*/
	void alineSprite();
	/**
	*	@brief
	*	@return 
	*/
	string getID()	{ return m_id; }
	/**
	*	@brief
	*	@return
	*/
	string getDoor() { return m_door; }
	/**
	*	@brief Whether or not the Gem can be despawned.
	*	@return bool if it can be despawned.
	*/
	bool canDespawn();
};

#endif