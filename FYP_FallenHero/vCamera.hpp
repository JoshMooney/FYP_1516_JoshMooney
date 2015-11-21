#ifndef _VIEW_CAMERA_HPP
#define _VIEW_CAMERA_HPP
#include "stdafx.h"
#include "SFML\Main.hpp"
#include "SFML\Graphics\View.hpp"

class vCamera : public sf::View {
private:

public:
	vCamera();
	vCamera(sf::Vector2f screen_size);
	~vCamera();

	sf::Vector2f getPlayerOffset(sf::Vector2f player_center){
		player_center.y -= 150;
		return player_center;
	}
	
};

#endif