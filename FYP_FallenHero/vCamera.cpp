#include "stdafx.h"
#include "vCamera.hpp"

vCamera::vCamera(){

}
vCamera::vCamera(sf::Vector2f screen_size){
	reset(sf::FloatRect{ 0, 0, screen_size.x, screen_size.y });
	setViewport(sf::FloatRect{ 0, 0, 1.0f, 1.0f });
	
}
vCamera::~vCamera(){

}
