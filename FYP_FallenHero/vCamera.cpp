#include "stdafx.h"
#include "vCamera.hpp"

vCamera::vCamera(){

}
vCamera::vCamera(sf::Vector2f screen_size){
	SCREEN_SIZE = screen_size;

	reset(sf::FloatRect{ 0, 0, screen_size.x, screen_size.y });
	setViewport(sf::FloatRect{ 0, 0, 1.0f, 1.0f });
	lock_x = false;
	lock_y = false;
	prev_lock_x = lock_x;
	prev_lock_y = lock_y;
}
vCamera::vCamera(sf::Vector2f screen_size, sf::FloatRect bounds) {
	SCREEN_SIZE = screen_size;

	reset(sf::FloatRect{ 0, 0, screen_size.x, screen_size.y });
	setViewport(sf::FloatRect{ 0, 0, 1.0f, 1.0f });
	m_bounds = bounds;
	lock_x = false;
	lock_y = false;
	prev_lock_x = lock_x;
	prev_lock_y = lock_y;
}
vCamera::vCamera(sf::Vector2f screen_size, sf::FloatRect bounds, pair<bool, bool> locked_axis) {
	SCREEN_SIZE = screen_size;

	reset(sf::FloatRect{ 0, 0, screen_size.x, screen_size.y });
	setViewport(sf::FloatRect{ 0, 0, 1.0f, 1.0f });
	m_bounds = bounds;
	lock_x = locked_axis.first;
	lock_y = locked_axis.second;
	prev_lock_x = false;
	prev_lock_y = false;
}
vCamera::~vCamera(){

}

void vCamera::refresh(sf::Vector2f player_center){
	reset(sf::FloatRect{ 0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y });
	setViewport(sf::FloatRect{ 0, 0, 1.0f, 1.0f });

	XAxisOffset = 0;
	YAxisOffset = 0;
	lock_x = false;
	lock_y = false;
	prev_lock_x = false;
	prev_lock_y = false;

	setCenter(getPlayerOffset(player_center));
}

sf::Vector2f vCamera::getPlayerOffset(sf::Vector2f player_center) {
	player_center.y -= 150;
	if (lock_x && !prev_lock_x){
		prev_lock_x = lock_x;
		lock_x_value = player_center.x;
	}
	if (lock_y && !prev_lock_y){
		prev_lock_y = lock_y;
		lock_y_value = player_center.y;
	}

	if (lock_y)
		player_center.y = lock_y_value;
	if (lock_x)
		player_center.x = lock_x_value;
	checkBounds(player_center);
	if (out_of_bounds) {
		//Calculate new player position minus the distance to the edge of the screen 
		player_center.x = XAxisOffset;
		//player_center.y = YAxisOffset;
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
	/*
	if (viewport.top < m_bounds.top) {
		out_of_bounds = true;
		viewport.top = m_bounds.top;

		YAxisOffset = viewport.top;
		YAxisOffset += viewport.height / 2;
	}
	if (viewport.top > m_bounds.height - viewport.height) {
		out_of_bounds = true;
		viewport.top = m_bounds.height - viewport.height;

		YAxisOffset = m_bounds.height;
		YAxisOffset -= viewport.height / 2;
	}
	*/
	if(player_center.x > viewport.width / 2 && player_center.x < m_bounds.width - (viewport.width / 2)) /*||player_center.y > viewport.height / 2 && player_center.y < m_bounds.height - (viewport.height / 2))*/
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
	pos_x = l_center.x - l_size.x / 2;
	pos_y = l_center.y - l_size.y / 2;
	sf::FloatRect temp = sf::FloatRect((float)(pos_x),
		(float)(pos_y),
		(float)(l_size.x),
		(float)(l_size.y));
	return temp;
}
void vCamera::LockX(bool b){
	if (!b){
		lock_x = b;
		prev_lock_x = lock_x;
		lock_x_value = -1;
	}
	else	lock_x = b;
}
void vCamera::LockY(bool b){
	if (!b){
		lock_y = b;
		prev_lock_y = lock_y;
		lock_y_value = -1;
	}
	else	lock_y = b;
}
float vCamera::getX(){
	return pos_x;
}
float vCamera::getY(){
	return pos_y;
}

bool vCamera::outOfBounds(sf::FloatRect & rec) {
	if (m_bounds.intersects(rec))
		return false;
	return true;
}

