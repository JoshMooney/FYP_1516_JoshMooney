#include "stdafx.h"
#include "WorldScene.hpp"

WorldScene::WorldScene(){
	m_key_pressed = true;
	has_selected = false;
	
	s_main_bg_text = "Assets/World/background.png";
	m_main_bg_sprt.setPosition(0, 0);
	m_main_bg_sprt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_main_bg_text));

	sf::Vector2f maporigin(100, 200);
	m_world_map = new WorldMap(maporigin);

	m_gui = std::make_shared<SimpleGUI>(SimpleGUI("Gui.png", maporigin + sf::Vector2f(250, -150), "Golden Age Shad.ttf", "Test Test", sf::Vector2f(25, 12)));

	m_player_icon = PlayerIcon();
	m_player_icon.setCenter(m_world_map->getNode(m_player_icon.getTag())->getCenter());

	m_camera = vCamera(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), sf::FloatRect{ 0.0f, 0.0f, 2880.0f, 640.0f });
	m_camera.setCenter(m_world_map->getCenter());
}
WorldScene::~WorldScene(){
	//delete m_world_map;
}

void WorldScene::update(){

}
void WorldScene::render(sf::RenderWindow &w){
	w.draw(m_main_bg_sprt);
	w.setView(m_camera);
	
	m_world_map->render(w);		//Renders the entire World Map
	w.draw(m_player_icon);
	m_gui->render(w, m_player_icon.m_lvl_tag);

	w.setView(w.getDefaultView());
}

void WorldScene::handleEvent(sf::Event &e){
	if (e.type == sf::Event::KeyReleased){
		switch (e.key.code){
		#pragma region Movement Controls
		case sf::Keyboard::Left:
			if (!m_key_pressed){
				m_key_pressed = true;
				movePlayer("LEFT");
			}
			break;
		case sf::Keyboard::Right:
			if (!m_key_pressed){
				m_key_pressed = true;
				movePlayer("RIGHT");
			}
			break;
		case sf::Keyboard::Up:
			if (!m_key_pressed){
				m_key_pressed = true;
				movePlayer("UP");
			}
			break;
		case sf::Keyboard::Down:
			if (!m_key_pressed){
				m_key_pressed = true;
				movePlayer("DOWN");
			}
			break;
		#pragma endregion
		#pragma region Interaction Controls
		case sf::Keyboard::Return:
			m_key_pressed = true;
			break;
		case sf::Keyboard::Space:
			if (!m_key_pressed) {
				m_key_pressed = true;
				select();
			}
			break;
		#pragma endregion
		}
	}
	else
		m_key_pressed = false;
}
void WorldScene::handleInput(XBOXController &controller){
	if (controller.isPressed["D_UP"] || controller.isPressed["AL_UP"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			movePlayer("UP");
		}
	}
	if (controller.isPressed["D_DOWN"] || controller.isPressed["AL_DOWN"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			movePlayer("DOWN");
		}
	}
	if (controller.isPressed["D_LEFT"] || controller.isPressed["AL_LEFT"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			movePlayer("LEFT");
		}
	}
	if (controller.isPressed["D_RIGHT"] || controller.isPressed["AL_RIGHT"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			movePlayer("RIGHT");
		}
	}
	if (controller.isPressed["A"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			select();
		}
	}
	if (controller.isIdle())
		m_key_pressed = false;
}

void WorldScene::movePlayer(string direction){
	WorldNode* node = m_world_map->getNode(m_player_icon.getTag());
	if (node->checkNeighbout(direction)){
		node = node->getNeightbourNode(direction);
		if (!node->m_is_locked) {
			m_player_icon.setTag(node->m_lvl_id);
			m_player_icon.setCenter(node->getCenter());
		}
	}
	else
		m_player_icon.bump(direction);
}
void WorldScene::select() {
	has_selected = true;
}

void WorldScene::reset(string s) {
	has_selected = false;
}