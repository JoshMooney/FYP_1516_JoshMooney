#include "stdafx.h"
#include "vCamera.hpp"

vCamera::vCamera(){

}
vCamera::vCamera(sf::Vector2f screen_size){
	reset(sf::FloatRect{ 0, 0, screen_size.x, screen_size.y });
	setViewport(sf::FloatRect{ 0, 0, 1.0f, 1.0f });
	
}
vCamera::vCamera(sf::Vector2f screen_size, sf::FloatRect bounds) {
	reset(sf::FloatRect{ 0, 0, screen_size.x, screen_size.y });
	setViewport(sf::FloatRect{ 0, 0, 1.0f, 1.0f });
	m_bounds = bounds;
}
vCamera::~vCamera(){

}

sf::Vector2f vCamera::getPlayerOffset(sf::Vector2f player_center) {
	player_center.y -= 150;
	checkBounds(player_center);
	if (out_of_bounds) {
		//Calculate new player position minus the distance to the edge of the screen 
		player_center.x = XAxisOffset;
		//out_of_bounds = false;
	}

	return player_center;
}
sf::FloatRect vCamera::checkBounds(sf::Vector2f player_center) {
	sf::FloatRect viewport = getRectViewport();

	if (viewport.left < m_bounds.left) {
		out_of_bounds = true;
		viewport.left = m_bounds.left;

		XAxisOffset = viewport.left;
		XAxisOffset += viewport.width / 2;
	}
	if (viewport.left > m_bounds.width - viewport.width) {
		out_of_bounds = true;
		viewport.left = m_bounds.width - viewport.width;

		XAxisOffset = m_bounds.width;
		XAxisOffset -= viewport.width / 2;
	}
	if(player_center.x > viewport.width / 2 && player_center.x < m_bounds.width - (viewport.width / 2))
		out_of_bounds = false;
		
	/*
	if (viewport.top < m_bounds.top)
	viewport.top = m_bounds.top;
	if (viewport.top > m_bounds.height - viewport.height)
	viewport.top = m_bounds.height - viewport.height;
	*/
	return viewport;
}
sf::FloatRect vCamera::getRectViewport() {
	sf::Vector2f l_size, l_center;
	l_size = getSize();
	l_center = getCenter();
	sf::FloatRect temp = sf::FloatRect((float)(l_center.x - l_size.x / 2),
		(float)(l_center.y - l_size.y / 2),
		(float)(l_size.x),
		(float)(l_size.y));
	return temp;
}


