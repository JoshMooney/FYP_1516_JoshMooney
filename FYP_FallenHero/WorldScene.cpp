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

	//m_gui = std::make_shared<SimpleGUI>(SimpleGUI("Gui.png", maporigin + sf::Vector2f(240, -100), "Golden Age Shad.ttf", "Test Test", sf::Vector2f(25, 12)));
	m_gui = std::make_shared<SimpleGUI>(SimpleGUI("Gui.png", maporigin + sf::Vector2f(220, -100), "Golden Age Shad.ttf", "Test Test", sf::Vector2f(25, 12), "GUI_title.png"));

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

void WorldScene::reset() {
	has_selected = false;
}

void WorldScene::checkUnlocks(string lvl_name) {
	WorldNode* node = m_world_map->getNode(lvl_name);
	if(node->m_next_lvl != nullptr)
		if (node->m_next_lvl->m_is_locked)
			node->m_next_lvl->unlock();
	generateMapData();
}

//Regenerates and copys map data to the current loaded save slot
void WorldScene::generateMapData() {
	//Generate Map data
	m_map_data["LVL1"] = m_world_map->getNode("LVL_1")->m_is_locked;
	m_map_data["LVL2"] = m_world_map->getNode("LVL_2")->m_is_locked;
	m_map_data["LVL3"] = m_world_map->getNode("LVL_3A")->m_is_locked;
	m_map_data["LVL4"] = m_world_map->getNode("LVL_3B")->m_is_locked;
	m_map_data["LVL5"] = m_world_map->getNode("LVL_4")->m_is_locked;
	m_map_data["LVL6"] = m_world_map->getNode("LVL_5")->m_is_locked;
	m_map_data["LVL7"] = m_world_map->getNode("LVL_6")->m_is_locked;
	//Copy Map data to saveslot
	m_current_slot->m_LVL_DATA = m_map_data;	
}

void WorldScene::loadSaveSlot(SaveSlot * ss) {
	m_current_slot = ss;
	m_world_map->createMap(ss->m_LVL_DATA);
}
