#include "stdafx.h"
#include "Game.hpp"

#include "Box2D\Common\b2Draw.h"

Game::Game() :
	m_window(new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Fallen Hero", sf::Style::Titlebar)),
	dd(*m_window)
{
	/*sf::Sprite title;
	title.setTexture(ResourceManager<sf::Texture>::instance()->get("Assets\title_screen.png"));
	title.setPosition(0, 0);
	m_window->draw(title);
	m_window->display();*/
	//m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Fallen Hero", sf::Style::Titlebar);
	//dd(*m_window);

	dd.PassWindow(m_window);
	isRunning = true;
	m_xbox_controller = make_shared<XBOXController>();
	m_xbox_controller->UpdateButtons();
	cLog::inst()->print("Game class initialised");

	m_menu_scene = new MenuScene();
	m_level_scene = new LevelScene();
	m_world_scene = new WorldScene();

	//Debugdraw
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	dd.SetFlags(flags);
	m_level_scene->m_world->SetDebugDraw(&dd);

	m_loader = new XMLLoader();
	m_menu_scene->setLoader(m_loader);
	/*
	debug_draw = SFMLDebugDraw(*m_window);
	m_level_scene->m_world->SetDebugDraw(&debug_draw);
	*/
	//Starting scene
	m_current_state = MENU;
	m_current_scene = m_menu_scene;

	//m_time_per_frame = sf::seconds(1.f / 30.f);
	//m_delta_time = sf::Time::Zero;
	//createPlayer();
}

Game::~Game(){

}

void Game::run(){
	while (isRunning) {
		sf::Event l_event;
		m_window->pollEvent(l_event);

		controller_connected = checkController();		//Checks controller connections and compaires to previous state.
		if (controller_connected)	
			m_xbox_controller->UpdateButtons();
		if (controller_connected)	
			m_current_scene->handleInput(*m_xbox_controller);
		else
			m_current_scene->handleEvent(l_event);
		m_current_scene->update();

		render();
		checkSceneChange();
	}
}

void Game::render(){
	m_window->clear();

	m_current_scene->render(*m_window);
	//m_level_scene->m_world->DrawDebugData();
	m_window->display();
}
void Game::createPlayer(){
	//m_player = new Player(*m_world);
	//m_level_scene->setPlayer(m_player);
}

bool Game::checkController() {
	bool is_connected = m_xbox_controller->isConnected();
	if (is_connected && !previous_connected) {
		previous_connected = is_connected;
	}
	if (!is_connected && previous_connected) {
		//Throw Controller Disconnect error.
		previous_connected = is_connected;
	}

	return is_connected;
}
void Game::goToNextScene() {
	switch (m_current_state) {
	case MENU:
		m_current_scene = m_world_scene;
		m_current_state = WORLD;
		//Pass the Selected slot to the world
		m_world_scene->loadSaveSlot(m_menu_scene->selected_slot);
		break;
	case WORLD:
		m_world_scene->reset();
		m_current_scene = m_level_scene;
		m_current_state = LEVEL;

		m_menu_scene->m_background_music.stop();
		m_level_scene->loadLevel(m_world_scene->getCurrentLevel());
		
		//m_level_scene->createPlatforms(m_world);
		break;
	case LEVEL:
		m_world_scene->checkUnlocks(m_level_scene->getLevelName());
		//Save Game here
		m_loader->save();

		m_level_scene->reset();
		m_current_scene = m_world_scene;
		m_current_state = WORLD;
		break;
	}
}

void Game::checkSceneChange() {
	if (m_current_state == MENU && m_menu_scene->getState() == MenuScene::GAME)
		goToNextScene();
	if (m_current_state == WORLD && m_world_scene->LevelSelected())
		goToNextScene();
	if (m_current_state == LEVEL && m_level_scene->isComplete())
		goToNextScene();
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