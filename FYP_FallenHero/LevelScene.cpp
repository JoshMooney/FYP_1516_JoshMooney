#include "stdafx.h"
#include "LevelScene.hpp"
#include "vHelper.hpp"

LevelScene::LevelScene() :
	contact_listener(ContactListener())
{
	m_world = new b2World(vHelper::toB2(GRAVITY));
	m_world->SetContactListener(&contact_listener);

	m_spawner = Spawner(m_world);

	buttonX_ = new JumpCommand();
	buttonY_ = new FireCommand();
	buttonB_ = new LurchCommand();
	buttonA_ = new SwapCommand();

	m_level_complete = false;
	m_camera = vCamera(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), sf::FloatRect{0.0f, 0.0f, 960.0f, 640.0f});
	m_camera.LockX(false);
	m_camera.LockY(false);
	//tiled_map = new tmx::TileMap("test.tmx");
	//m_time_per_frame = sf::seconds(1.f / 30.0f);
	isPaused = false;
	m_player = new Player(*m_world);
	player_size = ResourceManager<sf::Texture>::instance()->get(m_player->e_texture).getSize();
}
LevelScene::LevelScene(string lvl_name, Player *p){
	m_player = p;
	m_level_complete = false;

	//Dont use !
}
LevelScene::~LevelScene(){
	
}

void LevelScene::update(){
	//cLog::inst()->print(1, "LevelScene", "Deprecated update called");
	while (game_clock.now() - timeOfLastTick >= timePerTick && !isPaused){
		timeOfLastTick = game_clock.now();

		m_spawner.update(timeOfLastTick, m_player);
		m_spawner.CullInActiveEnemies();
		m_world->Step(B2_TIMESTEP, VEL_ITER, POS_ITER);

		
		
		m_player->update(timeOfLastTick);
		if (m_camera.outOfBounds(m_player->getBounds())) {
			respawnPlayer();
			m_camera.refresh(m_player->getCenter());
		}
		m_camera.setCenter(m_camera.getPlayerOffset(m_player->getCenter()));

		if (m_level->hasEnded(sf::FloatRect{ m_player->getPosition().x, m_player->getPosition().y, (float)player_size.x, (float)player_size.y }))
		{
			m_level_complete = true;
		}
	}

	//m_camera.checkBounds();
}
void LevelScene::render(sf::RenderWindow &w){
	w.setView(m_camera);		//Set the Camera
	m_level->scenery.renderBG(w, &m_camera);	//Render Background	

	m_level->render(w, &m_camera);		//render the level
	
	m_spawner.render(w);
	w.draw(*m_player);					//render Player

	m_world->DrawDebugData();
	m_level->scenery.renderFG(w, &m_camera);	//Render Foreground	
	w.setView(w.getDefaultView());		//Reset the windows view before exiting renderer
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
			//Execute command pattern commands here
			case sf::Keyboard::P:
				m_player->setJumping(false);
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
	level_id = lvl_name;		//Store the currently loaded levels ID
	if (m_level != nullptr)		m_level->Destroy(m_world);			//If there was a previous level destroy all the b2Bodies in that level 
	m_level = make_shared<Level>(lvl_name, m_world, &m_spawner);				//Create a new level
	m_camera.setBounds(m_level->Bounds());
	m_player->reset(m_level->getSpawn());			//Reset the player for the new level
	//Set the Cameras bounds here once loaded from the .tmx
}

void LevelScene::respawnPlayer() {
	m_player->reset(m_level->getSpawn());
}

void LevelScene::reset() {
	m_level_complete = false;
	m_player->reset(sf::Vector2f(0,0));
	m_camera.refresh(m_player->getCenter());

}
