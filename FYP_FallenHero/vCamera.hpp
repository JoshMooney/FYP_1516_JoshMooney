#ifndef _VIEW_CAMERA_HPP
#define _VIEW_CAMERA_HPP
#include "stdafx.h"
#include "SFML\Main.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Shape.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\View.hpp"

class vCamera : public sf::View {
private:
	bool lock_x, lock_y;
	bool prev_lock_x, prev_lock_y;
	float lock_x_value, lock_y_value;
	bool out_of_bounds = false;
	float pos_x, pos_y;
	float XAxisOffset;
	sf::FloatRect m_bounds;
	sf::Vector2f SCREEN_SIZE;
public:
	vCamera();
	vCamera(sf::Vector2f screen_size);
	vCamera(sf::Vector2f screen_size, sf::FloatRect bounds);
	vCamera(sf::Vector2f screen_size, sf::FloatRect bounds, pair<bool, bool> locked_axis);
	~vCamera();

	void refresh(sf::Vector2f player_center);

	sf::Vector2f getPlayerOffset(sf::Vector2f player_center);

	sf::FloatRect checkBounds(sf::Vector2f player_center);
	sf::FloatRect getRectViewport();
	void addBounds(sf::FloatRect bounds) { m_bounds = bounds; }
	void LockX(bool b);
	void LockY(bool b);
	float getX();
	float getY();
	bool outOfBounds(sf::FloatRect &rec);
};

#endif