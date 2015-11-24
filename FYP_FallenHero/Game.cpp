#include "stdafx.h"
#include "Game.hpp"

Game::Game() {
	m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Fallen Hero", sf::Style::Titlebar);
	m_world = new b2World(GRAVITY);
	isRunning = true;
	m_xbox_controller = XBOXController();
	m_xbox_controller.UpdateButtons();
	cLog::inst()->print("Game class initialised");

	m_menu_scene = new MenuScene();
	m_level_scene = new LevelScene();
	m_world_scene = new WorldScene();

	//Starting scene
	m_current_state = MENU;
	m_current_scene = m_menu_scene;

	m_time_per_frame = sf::seconds(1.f / 60.f);
	m_delta_time = sf::Time::Zero;
	createPlayer();
}

Game::~Game(){

}

void Game::run(){
	while (isRunning) {
		sf::Event l_event;
		m_window->pollEvent(l_event);
		controller_connected = checkController();		//Checks controller connections and compaires to previous state.
		if (controller_connected)	m_xbox_controller.UpdateButtons();
		if (m_current_state == LEVEL){	m_world->Step(B2_TIMESTEP, VEL_ITER, POS_ITER);	}
		
		if (controller_connected)	
			m_current_scene->handleInput(m_xbox_controller);
		else
			m_current_scene->handleEvent(l_event);
		m_current_scene->update();

		render();

		if (m_current_state == MENU)
			if (m_menu_scene->getState() == MenuScene::GAME){
				m_current_scene = m_level_scene;
				m_current_state = LEVEL;
				m_level_scene->createPlatforms(m_world);
		}
	}
}

void Game::render(){
	m_window->clear();

	m_current_scene->render(*m_window);
	m_window->display();
}
void Game::createPlayer(){
	m_player = new Player(*m_world);
	m_level_scene->setPlayer(m_player);
}

bool Game::checkController() {
	bool is_connected = m_xbox_controller.isConnected();
	if (is_connected && !previous_connected) {
		previous_connected = is_connected;
	}
	if (!is_connected && previous_connected) {
		//Throw Controller Disconnect error.
		previous_connected = is_connected;
	}

	return is_connected;
}

#pragma region Notes:
//Scene Casting
/*MenuScene* scene = dynamic_cast<MenuScene*>(m_current_scene);
if (scene == nullptr)
cLog::inst()->print("Menu Cast Failed");
LevelScene* scene_1 = dynamic_cast<LevelScene*>(m_current_scene);
if (scene == nullptr)
cLog::inst()->print("Level Cast Failed");
WorldScene* scene_2 = dynamic_cast<WorldScene*>(m_current_scene);
if (scene == nullptr)
cLog::inst()->print("World Cast Failed");
*/


#pragma endregion