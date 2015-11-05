#include "stdafx.h"
#include "WorldScene.hpp"


WorldScene::WorldScene(){
	m_key_pressed = false;
	
	if (!t_main_bg.loadFromFile("Assets/World/map.png"))
		cLog::inst()->print(1, "World", "Map texture failed to load");
	s_main_bg.setPosition(0, 0);
	s_main_bg.setTexture(t_main_bg);

	if (!t_player_icon.loadFromFile("Assets/World/player_icon.png"))
		cLog::inst()->print(1, "WorldMap", "Player Icon texture could not be loaded");
	s_player_icon.setScale(.25f, .25f);
	s_player_icon.setTexture(t_player_icon);
	s_player_icon.setPosition(200, 200);

	m_world_map = WorldMap(sf::Vector2f(0, 0), t_player_icon);
}
WorldScene::~WorldScene(){

}

void WorldScene::update(){

}
void WorldScene::render(sf::RenderWindow &w){
	w.draw(s_main_bg);		//Renders the background
	//w.draw(s_player_icon);
	m_world_map.render(w);		//Renders the entire World Map

}
void WorldScene::handleEvent(sf::Event &e){
	if (e.type == sf::Event::KeyPressed){
		switch (e.key.code){
		#pragma region Movement Controls
		case sf::Keyboard::Left:
			s_key_map["LEFT"] = true;
			m_key_pressed = true;
			break;
		case sf::Keyboard::Right:
			s_key_map["RIGHT"] = true;
			m_key_pressed = true;
			break;
		case sf::Keyboard::Up:
			s_key_map["UP"] = true;
			m_key_pressed = true;
			break;
		case sf::Keyboard::Down:
			s_key_map["DOWN"] = true;
			m_key_pressed = true;
			break;
		#pragma endregion
		#pragma region Interaction Controls
		case sf::Keyboard::Return:
			s_key_map["RETURN"] = true;
			m_key_pressed = true;
			break;
		case sf::Keyboard::Space:
			s_key_map["SPACE"] = true;
			m_key_pressed = true;
			break;
		#pragma endregion
		default:
			m_key_pressed = false;
			break;
		}
	}
}

void WorldScene::handleInput(){
	if (s_key_map["UP"] && !s_prev_key_map["UP"]){

	}
	else if (s_key_map["DOWN"] && !s_prev_key_map["DOWN"]) {

	}
	else if (s_key_map["LEFT"] && !s_prev_key_map["LEFT"]) {

	}
	else if (s_key_map["RIGHT"] && !s_prev_key_map["RIGHT"]) {

	}
	else if (s_key_map["RETURN"] && !s_prev_key_map["RETURN"]) {

	}
	else if (s_key_map["SPACE"] && !s_prev_key_map["SPACE"]) {

	}

	s_prev_key_map = s_key_map;
	s_key_map.clear();
}