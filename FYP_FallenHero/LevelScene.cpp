#include "stdafx.h"
#include "LevelScene.hpp"
#include "vHelper.hpp"

LevelScene::LevelScene() :
	contact_listener(ContactListener())
{
	m_world = new b2World(b2Vec2(0, 2));
	m_world->SetContactListener(&contact_listener);

	m_gem_mine = make_shared<GemMine>(m_world);

	m_spawner = make_shared<Spawner>(m_world);
	m_sensor_pool = make_shared<SensorPool>(m_world);
	m_projectiles = make_shared<ProjectileManager>(m_world);
	m_platform_creator = make_shared<PlatformCreator>(m_world);
	m_entity_creator = make_shared<EntityCreator>(m_world);

	m_spawner->AttachGemMine(m_gem_mine.get());
	m_spawner->AttachProjectileMgr(m_projectiles.get());
	m_spawner->AttachEntityCreator(m_entity_creator.get());
	
	loadMedia();
	buttonX_ = new AttackCommand();
	buttonY_ = new NULLCommand();
	buttonB_ = new InteractCommand();
	buttonA_ = new JumpCommand();

	m_level_complete = false;
	m_level_quit = false;
	m_camera = vCamera(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), sf::FloatRect{0.0f, 0.0f, 960.0f, 640.0f});
	m_camera.LockX(false);
	m_camera.LockY(false);
	m_camera.zoom(0.5f);

	//tiled_map = new tmx::TileMap("test.tmx");
	//m_time_per_frame = sf::seconds(1.f / 30.0f);
	m_key_pressed = false;
	isPaused = false;
	m_b2_dd = false;

	m_player = new Player(*m_world);
	m_player_HUD = HUD(m_player);
	player_size = m_player->getSize();
	m_animation_clock.restart();

	m_pause_menu = new PauseScreen();
}
LevelScene::LevelScene(string lvl_name, Player *p){
	m_player = p;
	m_level_complete = false;

	//Dont use !
}
LevelScene::~LevelScene(){
	delete m_pause_menu;
}

void LevelScene::loadMedia() {
	s_background_music = "Assets/Audio/Game/TheLoomingBattle.OGG";
	m_background_music.openFromFile(s_background_music);
	m_background_music.setLoop(true);
	m_background_music.setVolume(45.0f);
}
void LevelScene::update(){
	//cLog::inst()->print(1, "LevelScene", "Deprecated update called");
	timeOfLastTick = game_clock.now();
	if (!m_pause_menu->isPaused()) {
		m_world->Step(B2_TIMESTEP, VEL_ITER, POS_ITER);
		frame_elapse = m_animation_clock.restart();

		m_gem_mine->update(timeOfLastTick, m_player);

		m_spawner->update(timeOfLastTick, m_player);
		m_spawner->CullInActiveEnemies();

		m_platform_creator->update(timeOfLastTick);

		m_entity_creator->update(timeOfLastTick, m_player);

		m_projectiles->update(timeOfLastTick);
		m_projectiles->cull();
		//m_sensor_pool->cull();

		if (m_player->isAlive())
			m_player->update(timeOfLastTick);
		else
			respawnPlayer();
		m_player_HUD.update();

		if (m_camera.outOfBounds(m_player->getBounds())) {
			m_camera.refresh(m_player->getCenter());
			m_player->FallOffMap(m_level->getSpawn());
		}
		m_camera.setCenter(m_camera.getPlayerOffset(m_player->getCenter()));

		if (m_sensor_pool->hasEnded())	{
			m_player->clearKeys();
			m_level_complete = true;
		}
	}

	if (m_pause_menu->isPaused()) {
		PauseScreen::RESULT result = m_pause_menu->getResult();
		if (result != PauseScreen::NA) {
			if (result == PauseScreen::RESUME)
				m_pause_menu->setPaused(false);
			else if (result == PauseScreen::QUIT) {
				m_pause_menu->setPaused(false);
				m_player->clearKeys();
				m_level_quit = true;
			}
		}
		//m_camera.checkBounds();
	}
}
void LevelScene::render(sf::RenderWindow &w){
	if (m_pause_menu->isPaused())
		frame_elapse = sf::seconds(0.0f);

	w.setView(m_camera);		//Set the Camera
	m_level->scenery.renderBG(w, &m_camera);	//Render Background	

	m_level->render(w, &m_camera, frame_elapse);		//render the level

	m_entity_creator->render(&w, frame_elapse);

	m_player->render(&w, frame_elapse);
	w.draw(*m_player);					//render Player

	m_projectiles->render(w, frame_elapse);
	m_spawner->render(w, frame_elapse);
	m_gem_mine->render(w, frame_elapse);
	m_platform_creator->render(w, frame_elapse);
	
	if(m_b2_dd)
		m_world->DrawDebugData();
	m_level->scenery.renderFG(w, &m_camera);	//Render Foreground	

	w.setView(w.getDefaultView());		//Reset the windows view before exiting renderer
	m_player_HUD.render(&w);

	if (m_pause_menu->isPaused())
		m_pause_menu->render(w, frame_elapse);
}

void LevelScene::handleEvent(sf::Event &e){
	if (!m_pause_menu->isPaused()) {
		if (e.type == sf::Event::KeyPressed) {
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
				m_spawner->CheckLockDoor(m_player->getKeys());
				break;
			case sf::Keyboard::Z:
				m_camera.LockY(false);
				break;
			case sf::Keyboard::C:
				m_camera.LockY(true);
				break;
			//Execute command pattern commands here
			case sf::Keyboard::P:
				
				break;
			case sf::Keyboard::L:
				
				break;
			case sf::Keyboard::W:
				buttonY_->execute(m_player);
				break;
			case sf::Keyboard::A:
				buttonX_->execute(m_player);
				break;
			case sf::Keyboard::D:
				buttonB_->execute(m_player);
				break;
			case sf::Keyboard::S:
				buttonA_->execute(m_player);
				break;

			case sf::Keyboard::Return:
				break;
			case sf::Keyboard::Space:
				m_player->attack();
				break;

			case sf::Keyboard::B:
				if (!m_key_pressed){
					m_b2_dd = !m_b2_dd;
					m_key_pressed = true;
				}
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
			case sf::Keyboard::P:
				m_pause_menu->setPaused(true);
				break;
			case sf::Keyboard::Return:
				break;
			case sf::Keyboard::Space:
				break;
			default:
				m_key_pressed = false;
				break;
			}
		}
	}
	else {
		if (e.type == sf::Event::KeyReleased) {
			switch (e.key.code){
			#pragma region Movement Keys
			case sf::Keyboard::Up:
				if (!m_key_pressed) {
					m_key_pressed = true;
					m_pause_menu->moveUp();
				}
				break;
			case sf::Keyboard::Down:
				if (!m_key_pressed) {
					m_key_pressed = true;
					m_pause_menu->moveDown();
				}
				break;
			case sf::Keyboard::Space:
				if (!m_key_pressed) {
					m_key_pressed = true;
					m_pause_menu->select();
				}
				break;
			#pragma endregion
			}
		}
		else
			m_key_pressed = false;
	}

}
void LevelScene::handleInput(XBOXController &controller) {
	if(!m_pause_menu->isPaused()) {
		if (controller.isPressed["START"] && !controller.wasPressed["START"]) {
			isPaused = !isPaused;	//This Flips the pause of the game on and off.
		}
		if (controller.isPressed["D_RIGHT"] || controller.isPressed["AL_RIGHT"]) {
			m_player->moveRight();
		}
		if (controller.isPressed["D_LEFT"] || controller.isPressed["AL_LEFT"]) {
			m_player->moveLeft();
		}
		if (controller.isPressed["A"] && !m_key_pressed) {
			buttonA_->execute(m_player);
			m_key_pressed = true;
		}
		if (controller.isPressed["B"] && !m_key_pressed) {
			buttonB_->execute(m_player);
			m_spawner->CheckLockDoor(m_player->getKeys());
			m_key_pressed = true;
		}
		if (controller.isPressed["X"] && !m_key_pressed) {
			buttonX_->execute(m_player);
			m_key_pressed = true;
		}
		if (controller.isPressed["Y"]) {
			buttonY_->execute(m_player);
		}
		if (controller.isPressed["START"]) {
			m_pause_menu->setPaused(true);
		}
		if (controller.isPressed["SELECT"]) {
			if (!m_key_pressed) {
				m_b2_dd = !m_b2_dd;
				m_key_pressed = true;
			}
		}
		if (controller.isIdle())
			m_key_pressed = false;
	}
	else {
		//if (controller.isPressed["START"] || controller.isPressed["START"]){
			//m_pause_menu->setPaused(false);
		//}
		if (controller.isPressed["D_UP"] || controller.isPressed["AL_UP"] && !m_key_pressed){
			m_pause_menu->moveUp();
			m_key_pressed = true;
		}
		if (controller.isPressed["D_DOWN"] || controller.isPressed["AL_DOWN"] && !m_key_pressed){
			m_pause_menu->moveDown();
			m_key_pressed = true;
		}
		if (!controller.isPressed["A"] && controller.wasPressed["A"]){
			m_pause_menu->select();
			m_key_pressed = true;
		}
		if (controller.isIdle())
			m_key_pressed = false;
	}

	//If there is input being recieved or not
	if (!controller.isPressed["D_LEFT"] && !controller.isPressed["D_RIGHT"] &&
		!controller.isPressed["AL_LEFT"] && !controller.isPressed["AL_RIGHT"])
		m_player->setIfMoving(false);

	/*if (controller.isIdle())
	m_key_pressed = false;*/
}

void LevelScene::loadLevel(string lvl_name){
	m_background_music.play();
	m_level_complete = false;
	level_id = lvl_name;		//Store the currently loaded levels ID
	if (m_level != nullptr)		m_level->Destroy(m_world);			//If there was a previous level destroy all the b2Bodies in that level 
	
	m_spawner->clear();
	m_gem_mine->clear();
	m_projectiles->clear();
	m_platform_creator->clear();
	m_entity_creator->clear();
	m_sensor_pool->clear();

	m_level = make_shared<Level>(lvl_name, m_world, m_spawner.get(), m_gem_mine.get(), m_platform_creator.get(), m_entity_creator.get(), m_sensor_pool.get());				//Create a new level
	m_spawn_pos = m_level->getSpawn();

	m_camera.setBounds(m_level->Bounds());
	
	m_player->reset(m_level->getSpawn());
	m_camera.refresh(m_player->getCenter());

	m_camera.refresh(m_player->getCenter());
	m_level_clock.restart();

	//Set the Cameras bounds here once loaded from the .tmx
}

void LevelScene::respawnPlayer() {
	Subject::instance()->notify(Subject::OUT_OF_CATS_LIVES, m_player);
	m_player->clearKeys();
	m_player->reset(m_level->getSpawn());
	m_camera.refresh(m_player->getCenter());
}

void LevelScene::reset() {
	m_background_music.stop();
	m_level_complete = false;
	m_level_quit = false;
	m_player->reset(sf::Vector2f(0,0));
	m_camera.refresh(m_player->getCenter());
}
