#include "stdafx.h"
#include "LevelScene.hpp"
#include "vHelper.hpp"

LevelScene::LevelScene(){
	m_level_active = true;
	m_camera = vCamera(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

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
	m_camera.setCenter(m_camera.getPlayerOffset(vHelper::toSF(m_player->getCenter())));

}
void LevelScene::render(sf::RenderWindow &w){
	//Render Background

	w.setView(m_camera);
	w.draw(*m_player);
	//for (int i = 0; i < m_platform.size(); i++){
	//	m_platform[i].render(w);
	//}
	m_plat1.render(w);
	m_plat2.render(w);


	w.setView(w.getDefaultView());	//Reset the windows view before exiting renderer
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
void LevelScene::handleInput(XBOXController &controller){
	if (controller.isPressed["D_UP"] || controller.isPressed["A"]){
		m_player->jump();
	}
	if (controller.isPressed["D_RIGHT"]){
		m_player->moveRight();
	}
	if (controller.isPressed["D_LEFT"]){
		m_player->moveLeft();
	}
	if (controller.isPressed["SELECT"]){
		
	}

	/*if (controller.isIdle())
		m_key_pressed = false;*/
}

void LevelScene::loadLevel(string s){

}

void LevelScene::createPlatforms(b2World *l_world){
	//m_platform.push_back(Platform(sf::Vector2f(150, 500), sf::Vector2f(200, 50), *l_world));
	//m_platform.push_back(Platform(sf::Vector2f(500, 450), sf::Vector2f(200, 50), *l_world));
	m_plat1 = Platform(sf::Vector2f(150, 500), sf::Vector2f(200, 50), *l_world);
	m_plat2 = Platform(sf::Vector2f(500, 450), sf::Vector2f(200, 50), *l_world);
}
