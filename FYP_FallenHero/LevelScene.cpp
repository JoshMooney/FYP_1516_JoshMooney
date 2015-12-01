#include "stdafx.h"
#include "LevelScene.hpp"

LevelScene::LevelScene(){
	m_level_complete = false;
	m_camera = vCamera(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), sf::FloatRect{0.0f, 0.0f, 2880.0f, 640.0f});
	//tiled_map = new tmx::TileMap("test.tmx");
	m_time_per_frame = sf::seconds(1.f / 30.0f);
}
LevelScene::LevelScene(string lvl_name, Player *p){
	m_player = p;
	m_level_complete = false;
}
LevelScene::~LevelScene(){
	
}

void LevelScene::update(){
	//cLog::inst()->print(1, "LevelScene", "Deprecated update called");
	m_player->update(m_time_per_frame);
	m_camera.setCenter(m_camera.getPlayerOffset(vHelper::toSF(m_player->getCenter())));
	
	sf::Vector2u size = ResourceManager<sf::Texture>::instance()->get(m_player->e_texture).getSize();
	if (m_level->hasEnded(sf::FloatRect{ m_player->getPosition().x, m_player->getPosition().y, (float)size.x, (float)size.y }))
		m_level_complete = true;

	//m_camera.checkBounds();
}
void LevelScene::update(sf::Time dt){
	m_player->update(m_time_per_frame);
	m_camera.setCenter(m_camera.getPlayerOffset(vHelper::toSF(m_player->getCenter())));

}
void LevelScene::render(sf::RenderWindow &w){
	//Render Background

	w.setView(m_camera);
	m_level->render(w);
	w.draw(*m_player);
	//for (int i = 0; i < m_platform.size(); i++){
	//	m_platform[i].render(w);
	//}
	//m_plat1.render(w);
	//m_plat2.render(w);
	

	w.setView(w.getDefaultView());	//Reset the windows view before exiting renderer
}

void LevelScene::handleEvent(sf::Event &e){
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
		case sf::Keyboard::Q:
			m_camera.LockX(false);
			break;
		case sf::Keyboard::E:
			m_camera.LockX(true);
			break;
		case sf::Keyboard::Z:
			m_camera.LockY(false);
			break;
		case sf::Keyboard::C:
			m_camera.LockY(true);
			break;

		case sf::Keyboard::Return:
			break;
		case sf::Keyboard::Space:
			break;
		}
	}

	if (e.type == sf::Event::KeyReleased) {
		switch (e.key.code) {
		#pragma region Movement Keys
		case sf::Keyboard::Up:
			
			break;
		case sf::Keyboard::Down: 

			break;
		case sf::Keyboard::Right:
			m_player->setIfMoving(false);
			break;
		case sf::Keyboard::Left:
			m_player->setIfMoving(false);
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

void LevelScene::loadLevel(string lvl_name, b2World *world){
	m_level = make_shared<Level>(lvl_name, world);
	m_player->reset(m_level->getSpawn());
}

void LevelScene::createPlatforms(b2World *l_world){
	//m_platform.push_back(Platform(sf::Vector2f(150, 500), sf::Vector2f(200, 50), *l_world));
	//m_platform.push_back(Platform(sf::Vector2f(500, 450), sf::Vector2f(200, 50), *l_world));
	//m_plat1 = Platform(sf::Vector2f(150, 500), sf::Vector2f(200, 50), *l_world);
	//m_plat2 = Platform(sf::Vector2f(500, 450), sf::Vector2f(800, 50), *l_world);
}
void LevelScene::reset() {
	m_level_complete = false;
	m_player->reset(sf::Vector2f(0,0));
	m_camera.refresh(vHelper::toSF(m_player->getCenter()));

}
