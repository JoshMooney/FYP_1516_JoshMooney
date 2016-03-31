#ifndef _VIEW_CAMERA_HPP
#define _VIEW_CAMERA_HPP
#include "stdafx.h"
#include "SFML\Main.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Shape.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\View.hpp"

/**
*	@class vCamera
*	@brief This class is the vector camera class responsible for adjusting the view and
*	keeping the player in the approprate position on screen.
*/
class vCamera : public sf::View {
private:
	bool lock_x, lock_y;
	bool prev_lock_x, prev_lock_y;
	float lock_x_value, lock_y_value;
	bool oob_x, oob_y;
	float pos_x, pos_y;
	float XAxisOffset, YAxisOffset;
	sf::FloatRect m_bounds;
	sf::Vector2f SCREEN_SIZE;
	float default_zoom;
public:
	/**
	*	@brief Default constructor which has been deprecated
	*/
	vCamera();
	/**
	*	@brief Overloaded constructor for the Camera which takes a sf::Vector2f for the screen_size.
	*	@param sf::Vector2f The width and height of the screen.
	*/
	vCamera(sf::Vector2f screen_size);
	/**
	*	@brief Overloaded constructor for the Camera which takes a sf::Vector2f for the screen_size 
	*	and a sf::FloatRect for the bounds of the camera.
	*	@param sf::Vector2f The width and height of the screen.
	*	@param sf::FloatRect The width and height of the camera bounds.
	*/
	vCamera(sf::Vector2f screen_size, sf::FloatRect bounds);
	/**
	*	@brief Overloaded constructor for the Camera which takes a sf::Vector2f for the screen_size 
	*	, a sf::FloatRect for the bounds of the camera and a pair of bools if the camera is ever needed
	*	to be constructed with specific locking.
	*	@param sf::Vector2f The width and height of the screen.
	*	@param sf::FloatRect The width and height of the camera bounds.
	*	@param pair<bool, bool> Whether the x and y axis are locked.
	*/
	vCamera(sf::Vector2f screen_size, sf::FloatRect bounds, pair<bool, bool> locked_axis);
	/**
	*	@brief Deconstructor of the camera
	*/
	~vCamera();

	/**
	*	@brief Resets all the variables of the camera and points it at the sf::Vector2f passed in.
	*	@param sf::Vector2f The center to fix the camera to.
	*/
	void refresh(sf::Vector2f player_center);

	/**
	*	@brief Finds the player offset taking an allowence and the paralax effect into account.
	*	@param sf::Vector2f The players Center point
	*	@return sf::Vector2f The new center of the player.
	*/
	sf::Vector2f getPlayerOffset(sf::Vector2f player_center);
	/**
	*	@brief Set the bounds of the camera after construction
	*	@param sf::FloatRect The new bounds of the camera
	*/
	void setBounds(sf::FloatRect bounds);
	/**
	*	@brief Checks if the camera view has stepped outside the bounds of the camera. 
	*	@param sf::Vector2f The center of the screen.
	*	@return The new viewport after the bounds have been taken into consideration.
	*/
	sf::FloatRect checkBounds(sf::Vector2f player_center);
	/**
	*	@brief Creates a sf::FloatRect of the current viewport of the camera.
	*	@return The viewport of the camera.
	*/
	sf::FloatRect getRectViewport();
	//!Adds a boundary to the camera
	void addBounds(sf::FloatRect bounds) { m_bounds = bounds; }
	
	/**
	*	@brief Setter for the locking the X axis
	*/
	void LockX(bool b);
	/**
	*	@brief Setter for the locking the Y axis
	*/
	void LockY(bool b);
	/**
	*	@brief Gets the X value of the camera
	*/
	float getX();
	/**
	*	@brief Gets the Y value of the camera
	*/
	float getY();
	/**
	*	@brief Checks if the rectangle passed in is continaed within the bounds of the camera.
	*	@param sf::FloatRect The Shape to check 
	*	@return bool for whether or not the shape is inside the bounds.
	*/
	bool outOfBounds(sf::FloatRect &rec);
};

#endif