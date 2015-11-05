#include "stdafx.h"
#include "LevelScene.hpp"

LevelScene::LevelScene()	{
	m_level_active = true;
}
LevelScene::LevelScene(string lvl_name, Player *p){
	loadLevel(lvl_name);
	m_player = p;
	m_level_active = true;
}
LevelScene::~LevelScene(){

}

void LevelScene::update(){
	cLog::inst()->print(1, "LevelScene", "Deprecated update called");
}
void LevelScene::update(sf::Time dt){
	m_player->update(dt);

}
void LevelScene::render(sf::RenderWindow &w){
	w.draw(*m_player);
	//for (int i = 0; i < m_platform.size(); i++){
	//	m_platform[i].render(w);
	//}
	m_plat1.render(w);
	m_plat2.render(w);
}
void LevelScene::handleEvent(sf::Event &e){
	cLog::inst()->print(1, "LevelScene", "Deprecated handleEvent called");
}
void LevelScene::handleEvent(sf::Event &e, sf::Time dt){
	if (e.type == sf::Event::KeyPressed){
		switch (e.key.code){
		#pragma region Movement Keys
		case sf::Keyboard::Up:
			m_player->jump();
			break;
		case sf::Keyboard::Down:
			break;
		case sf::Keyboard::Right:
			m_player->moveRight();
			break;
		case sf::Keyboard::Left:
			m_player->moveLeft();
			break;
#pragma endregion
		case sf::Keyboard::Return:
			break;
		case sf::Keyboard::Space:
			break;
		}
	}
}

void LevelScene::loadLevel(string s){

}

void LevelScene::createPlatforms(b2World *l_world){
	//m_platform.push_back(Platform(sf::Vector2f(150, 500), sf::Vector2f(200, 50), *l_world));
	//m_platform.push_back(Platform(sf::Vector2f(500, 450), sf::Vector2f(200, 50), *l_world));
	m_plat1 = Platform(sf::Vector2f(150, 500), sf::Vector2f(200, 50), *l_world);
	m_plat2 = Platform(sf::Vector2f(500, 450), sf::Vector2f(200, 50), *l_world);
}
