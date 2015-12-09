#include "stdafx.h"
#include "LevelScene.hpp"

LevelScene::LevelScene(){
	m_world = new b2World(GRAVITY);

	m_level_complete = false;
	m_camera = vCamera(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), sf::FloatRect{0.0f, 0.0f, 2880.0f, 640.0f});
	//tiled_map = new tmx::TileMap("test.tmx");
	//m_time_per_frame = sf::seconds(1.f / 30.0f);
	isPaused = false;
	m_player = new Player(*m_world);
	player_size = ResourceManager<sf::Texture>::instance()->get(m_player->e_texture).getSize();
}
LevelScene::LevelScene(string lvl_name, Player *p){
	m_player = p;
	m_level_complete = false;
}
LevelScene::~LevelScene(){
	
}

void LevelScene::update(){
	//cLog::inst()->print(1, "LevelScene", "Deprecated update called");
	while (game_clock.now() - timeOfLastTick >= timePerTick && !isPaused){
		timeOfLastTick = game_clock.now();

		m_world->Step(B2_TIMESTEP, VEL_ITER, POS_ITER);

		m_player->update(timeOfLastTick);
		m_camera.setCenter(m_camera.getPlayerOffset(vHelper::toSF(m_player->getCenter())));
		
		if (m_level->hasEnded(sf::FloatRect{ m_player->getPosition().x, m_player->getPosition().y, (float)player_size.x, (float)player_size.y }))
			m_level_complete = true;
	}

	//m_camera.checkBounds();
}
void LevelScene::render(sf::RenderWindow &w){
	//Render Background
	w.setView(m_camera);

	m_level->render(w, &m_camera);
	w.draw(*m_player);
	

	w.setView(w.getDefaultView());	//Reset the windows view before exiting renderer
}

void LevelScene::handleEvent(sf::Event &e){
	if (!isPaused){
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
	else{

	}
}
void LevelScene::handleInput(XBOXController &controller){
	if (controller.isPressed["START"] && !controller.wasPressed["START"]){
		isPaused = !isPaused;	//This Flips the pause of the game on and off.
	}
	if (!isPaused){
		if (controller.isPressed["D_UP"] || controller.isPressed["A"]){
			m_player->jump();
		}
		//if (!controller.isPressed["A"] && controller.wasPressed["A"]){
		//	m_player->jump();
		//}
		if (controller.isPressed["D_RIGHT"] || controller.isPressed["AL_RIGHT"]){
			m_player->moveRight();
		}
		if (controller.isPressed["D_LEFT"] || controller.isPressed["AL_LEFT"]){
			m_player->moveLeft();
		}

		//If there is input being recieved or not
		if (!controller.isPressed["D_LEFT"] && !controller.isPressed["D_RIGHT"] &&
			!controller.isPressed["AL_LEFT"] && !controller.isPressed["AL_RIGHT"])
			m_player->setIfMoving(false);

		/*if (controller.isIdle())
			m_key_pressed = false;*/
	}
	else{

	}
}

void LevelScene::loadLevel(string lvl_name){
	m_level = make_shared<Level>(lvl_name, m_world);
	m_player->reset(m_level->getSpawn());
}

void LevelScene::reset() {
	m_level_complete = false;
	m_player->reset(sf::Vector2f(0,0));
	m_camera.refresh(vHelper::toSF(m_player->getCenter()));

}
