#ifndef _CRUMBLE_BLOCK_HPP
#define _CRUMBLE_BLOCK_HPP
#include "stdafx.h"
#include "Enemy.hpp"
#include "Thor\Animations.hpp"

/**
*	@class CrumbleBlock
*	@brief This is the single class that is responable for generating a CrumbleBlock depending on the 
*	passed in SIZE and TYPE enums. This blocks must have health and be animated for when they are 
*	damaged and crumble and fall apart. This is why the class inherits from Enemy
*/
class CrumbleBlock : public Enemy {
private:
	string s_hit;
	string s_destroy;
	sf::Sound m_hit;
	sf::Sound m_destroy;
	thor::FrameAnimation frame_dead;
	thor::FrameAnimation frame_alive;
	thor::FrameAnimation frame_crumble;
	sf::Vector2u m_text_size;
	int gemCount;
public:
	//!	Enum for representing the current state of the Block
	enum STATE { 
	ALIVE, 		//!<The Block is Fully alive and well 
	CRUMBLE, 	//!<If the type of brick can be crumbled this will be the next state after ALIVE
	DEAD		//!<This is the death state when here the boxbody will be destroyed and animated 
	};		
	STATE m_current_state;			//!<The current state of the block
	STATE m_previous_state;			//!<The previous state of the block
	
	//!	Enum for representing the current type of the Block
	enum TYPE { 
	SAND, 		//!<Sand Texture this type of block is weak and can only take one hit
	DIRT,       //!<Dirt Texture this type of block is weak and can only take one hit
	ROCK 		//!<Rock Texture this type of block is strong and can take multiple hits
	};     
	TYPE m_type;					//!<The current type of the Block
	
	//!	Enum for representing the current size of the Block
	enum SIZE { 
	SMALL, 		//!<The Block is small the size in SFML dimentions its :(32*32)
	LARGE 		//!<The Block is large the size in SFML dimentions its :(64*64)
	};	
	SIZE m_size;					//!<The current size of the Block
	
	thor::Animator<sf::Sprite, STATE> m_animator;		//!<The Thor animator for stepping through the sprite sheet.

	/**
	*	@brief This is the default constructor for the CrumbleBlock. This function has been 
	*	deprecated and is un used the overloaded Constructor is the main use.
	*/
	CrumbleBlock();
	/**
	*	@brief This is the main constructor for the crumble block and is responcable for calling 
	*	load media and must also add all the frames as part of the animation.
	*	@param b2body This is the box2d body for handling physics
	*	@param sf::Vector2f This is the position to spawn the block at
	*	@param TYPE The type of block to spawn (e.g. Sand, Rock, Dirt)
	*	@param SIZE The size of the block either (32x32) || (64x64)
	*/
	CrumbleBlock(b2Body *b, sf::Vector2f pos, TYPE t, SIZE s);
	/**
	*	@brief This is the Deconstructor for the CrumbleBlock
	*/
	~CrumbleBlock();

	/**
	*	@brief This loads the approprate assets for the CrumbleBlock
	*/
	void loadMedia();

	/**
	*	@brief Keeps the Animation in step. Checks for the the flags in the approprate order
	*	to keep the animation running smoothy. If an animation needs to be looped or replayed 
	*	this will be handled here.
	*/
	void checkAnimation();
	/**
	*	@brief Creates and adds a frame to a thor::FrameAnimation
	*	@param thor::FrameAnimation The FrameAnimation to add the custom frame too.
	*	@param STATE The state of the block to find the y offset of the image.
	*	@param xFirst The X of the first frame.
	*	@param xLast The X of the last frame.
	*	@param xSep The X seperation of frames.
	*	@param ySep The Y seperation of frames.
	*	@param duration The duration of the frames.
	*/
	void addFrames(thor::FrameAnimation& animation, STATE s, int xFirst, int xLast, int xSep, int ySep, float duration);
	
	/**
	*	@brief Alines the sprite with the Box2D body
	*/
	void alineSprite() override;
	/**
	*	@brief Default TakeDamage method to lose 10 hp
	*/
	void TakeDamage() override;
	/**
	*	@brief Raise the Death flag for the brick that gets picked up from the checkAnimation
	*	function and changes the animation.
	*/
	void Die() override;
	/**
	*	@brief Initalises the approprate variables for the Block class
	*/
	void init();

	/**
	*	@brief Updates any requirements for the Block currently its empty
	*	@param FTS This is the Fixed Time Step the game is running.
	*/
	void update(FTS fts, Player *p);
	/**
	*	@brief This renders the Block and its approprate animation
	*	@param sf::RenderWindow The Window to render things to.
	*	@param sf::Time The Number of frames that have passed for updating the animation
	*/
	void render(sf::RenderWindow &w, sf::Time frames);

	sf::Vector2u getTextureSize() { return m_text_size; }			//!<Returns the Width and Height of the texture as a sf::Vector2u. 
	/**
	*	@brief Returns the bounds of the block as a sf::FloatRect
	*	@return FloatRect of the bounds of the brick.
	*/
	sf::FloatRect getBounds() override  {
		sf::Vector2f position(getPosition().x - (m_text_size.x / 2), getPosition().y - (m_text_size.y / 2));
		return sf::FloatRect{ position.x, position.y, (float)m_text_size.x, (float)m_text_size.y };
	}
	/**
	*	@brief
	*/
	bool canGemSpawn() {
		if (gemCount > 0) {
			gemCount--;
			return true;
		}
		return false;
	}
};

#endif