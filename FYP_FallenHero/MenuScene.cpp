#include "stdafx.h"
#include "MenuScene.hpp"
#include "ResourceManager.hpp"
#include <sstream> 

MenuScene::MenuScene(){
	m_item_position = sf::Vector2f(SCREEN_WIDTH - ((SCREEN_WIDTH / 100) * 28), SCREEN_HEIGHT - ((SCREEN_HEIGHT / 100) * 36));
	m_item_spacing = sf::Vector2f(0, 50);
	m_key_pressed = false;
	m_banner_pos = sf::Vector2f(52, 115);
	m_banner_sep = sf::Vector2f(304, 0);

	loadMedia();
	loadText();

	m_current_state = SPLASH;
	m_current_menu_item = M_CONTINUE;
	menu_text[M_CONTINUE].setColor(sf::Color::Yellow);

	cLog::inst()->print("MenuScene Initalised");
	m_background_music.play();
}
MenuScene::~MenuScene(){
	cLog::inst()->print("MenuScene Deconstructor Called");
}

void MenuScene::update(){

}
void MenuScene::render(sf::RenderWindow &w){
	switch (m_current_state){
	case SPLASH:
		w.draw(m_splash_sprt);
		break;
	case MAIN:
		w.draw(m_main_bg_sprt);
		w.draw(m_logo_sprt);

		for (int i = 0; i < menu_text.size(); i++){
			w.draw(menu_text[i]);
		}
		break;
	case SAVE_SELECT:
		w.draw(m_main_bg_sprt);
		w.draw(m_save_gui);
		w.draw(m_save_banner);
		for (int i = 0; i < m_save_text.size(); i++)
			for (int j = 0; j < m_save_text[i].size(); j++) {
				w.draw(m_save_text[i][j]);
			}
		w.draw(m_save_select_text);
		break;
	case NEW:
		w.draw(m_main_bg_sprt);
		w.draw(m_save_gui);
		w.draw(m_erase_banner);
		for (int i = 0; i < m_save_text.size(); i++)
			for (int j = 0; j < m_save_text[i].size(); j++) {
				w.draw(m_save_text[i][j]);
			}
		w.draw(m_erase_select_text);
		break;
	case OPTIONS:
		w.draw(m_main_bg_sprt);
		w.draw(m_options_gui);
		break;
	}
}
void MenuScene::handleEvent(sf::Event &e){
	if (e.type == sf::Event::KeyReleased){
		switch (e.key.code){
		case sf::Keyboard::Up:
			if (!m_key_pressed){
				m_key_pressed = true;
				moveUp();
			}
			break;
		case sf::Keyboard::Down:
			if (!m_key_pressed){
				m_key_pressed = true;
				moveDown();
			}
			break;
		case sf::Keyboard::Right:
			if (!m_key_pressed) {
				m_key_pressed = true;
				moveRight();
			}
			break;
		case sf::Keyboard::Left:
			if (!m_key_pressed) {
				m_key_pressed = true;
				moveLeft();
			}
			break;
		case sf::Keyboard::Return:
			if (!m_key_pressed){
				m_key_pressed = true;
				select();
			}
			break;
		case sf::Keyboard::Space:
			if (!m_key_pressed){
				m_key_pressed = true;
				select();
			}
			break;
		case sf::Keyboard::BackSpace:
			if (!m_key_pressed){
				m_key_pressed = true;
				back();
			}
			break;
		default:
			m_key_pressed = false;
			break;
		}
	}
	else
		m_key_pressed = false;
}
void MenuScene::handleInput(XBOXController &controller){
	if (controller.isPressed["D_UP"] || controller.isPressed["AL_UP"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			moveUp();
		}
	}
	if (controller.isPressed["D_DOWN"] || controller.isPressed["AL_DOWN"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			moveDown();
		}
	}
	if (controller.isPressed["D_RIGHT"] || controller.isPressed["AL_RIGHT"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			moveUp();
		}
	}
	if (controller.isPressed["D_LEFT"] || controller.isPressed["AL_LEFT"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			moveDown();
		}
	}
	if (controller.isPressed["A"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			select();
		}
	}
	if (controller.isPressed["B"]){
		if (!m_key_pressed){
			m_key_pressed = true;
			back();
		}
	}
	if (controller.isIdle())
		m_key_pressed = false;
}

void MenuScene::moveUp(){
	if (m_current_state == MAIN){
		switch (m_current_menu_item){
		case M_CONTINUE:
			m_bump.play();
			break;
		case M_NEW:
			m_move_up.play();

			menu_text[M_CONTINUE].setColor(sf::Color::Yellow);
			m_current_menu_item = M_CONTINUE;
			menu_text[M_NEW].setColor(sf::Color::Black);
			break;
		case M_OPTIONS:
			m_move_up.play();

			menu_text[M_NEW].setColor(sf::Color::Yellow);
			m_current_menu_item = M_NEW;
			menu_text[M_OPTIONS].setColor(sf::Color::Black);
			break;
		case M_EXIT:			
			m_move_up.play();

			menu_text[M_OPTIONS].setColor(sf::Color::Yellow);
			m_current_menu_item = M_OPTIONS;
			menu_text[M_EXIT].setColor(sf::Color::Black);
			break;
		}
	}
	if (m_current_state == SAVE_SELECT){

	}
}
void MenuScene::moveDown(){
	if (m_current_state == MAIN) {
		switch (m_current_menu_item) {
		case M_CONTINUE:
			m_move_down.play();

			menu_text[M_NEW].setColor(sf::Color::Yellow);
			m_current_menu_item = M_NEW;
			menu_text[M_CONTINUE].setColor(sf::Color::Black);
			break;
		case M_NEW:
			m_move_down.play();

			menu_text[M_OPTIONS].setColor(sf::Color::Yellow);
			m_current_menu_item = M_OPTIONS;
			menu_text[M_NEW].setColor(sf::Color::Black);
			break;
		case M_OPTIONS:
			m_move_down.play();

			menu_text[M_EXIT].setColor(sf::Color::Yellow);
			m_current_menu_item = M_EXIT;
			menu_text[M_OPTIONS].setColor(sf::Color::Black);
			break;
		case M_EXIT:
			m_bump.play();
			break;
		}
	}
	if (m_current_state == SAVE_SELECT){

	}
}
void MenuScene::moveRight(){
	if (m_current_state == MAIN){

	}
	if (m_current_state == SAVE_SELECT){
		switch (m_current_slot) {
		case SLOT_1:
			m_move_up.play();
			m_current_slot = SLOT_2;
			m_save_banner.setPosition(m_banner_pos + m_banner_sep);
			break;
		case SLOT_2:
			m_move_up.play();
			m_current_slot = SLOT_3;
			m_save_banner.setPosition(m_banner_pos + m_banner_sep + m_banner_sep);
			break;
		case SLOT_3:
			m_bump.play();
			break;
		}
	}
	if (m_current_state == NEW) {
		switch (m_current_slot) {
		case SLOT_1:
			m_move_up.play();
			m_current_slot = SLOT_2;
			m_erase_banner.setPosition(m_banner_pos + m_banner_sep);
			break;
		case SLOT_2:
			m_move_up.play();
			m_current_slot = SLOT_3;
			m_erase_banner.setPosition(m_banner_pos + m_banner_sep + m_banner_sep);
			break;
		case SLOT_3:
			m_bump.play();
			break;
		}
	}
}
void MenuScene::moveLeft(){
	if (m_current_state == MAIN){

	}
	if (m_current_state == SAVE_SELECT){
		switch (m_current_slot) {
		case SLOT_1:
			m_bump.play();
			break;
		case SLOT_2:
			m_move_down.play();
			m_current_slot = SLOT_1;
			m_save_banner.setPosition(m_banner_pos);
			break;
		case SLOT_3:
			m_move_down.play();
			m_current_slot = SLOT_2;
			m_save_banner.setPosition(m_banner_pos + m_banner_sep);
			break;
		}
	}
	if (m_current_state == NEW) {
		switch (m_current_slot) {
		case SLOT_1:
			m_bump.play();
			break;
		case SLOT_2:
			m_move_down.play();
			m_current_slot = SLOT_1;
			m_erase_banner.setPosition(m_banner_pos);
			break;
		case SLOT_3:
			m_move_down.play();
			m_current_slot = SLOT_2;
			m_erase_banner.setPosition(m_banner_pos + m_banner_sep);
			break;
		}
	}
}
void MenuScene::select() {
	cLog::inst()->print("Select Pressed");
	if (m_current_state == MAIN)
		switch (m_current_menu_item)
		{
		case M_CONTINUE:
			changeState(SAVE_SELECT);
			break;
		case M_NEW:
			changeState(NEW);
			break;
		case M_OPTIONS:
			changeState(OPTIONS);
			break;
		case M_EXIT:
			m_current_state = CLOSE;
			break;
		}
	else if (m_current_state == SAVE_SELECT) {
		selected_slot = loader->saved_data[m_current_slot];
		changeState(GAME);
	}
	else if (m_current_state == NEW) {
		delete loader->saved_data[m_current_slot];
		loader->saved_data[m_current_slot] = new SaveSlot(m_current_slot + 1);
		selected_slot = loader->saved_data[m_current_slot];
		changeState(GAME);
	}
	else if (m_current_state == SPLASH)
		changeState(MAIN);
}
void MenuScene::back(){
	if (m_current_state == SAVE_SELECT){
		changeState(STATE::MAIN);
	}
	else if (m_current_state == OPTIONS) {
		changeState(STATE::MAIN);
	}
	else if (m_current_state == NEW) {
		changeState(STATE::MAIN);
	}
}

void MenuScene::loadMedia(){
	if (!m_font.loadFromFile("Assets/Font/Golden Age Shad.ttf"))
		cLog::inst()->print(1, "MenuScene", "Golden Age Shad font failed to load");

	s_splash = "Assets/Splash/Background.png";
	m_splash_sprt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_splash));
	m_splash_sprt.setPosition(0, 0);

	s_main_bg = "Assets/Menu/Background.png";
	m_main_bg_sprt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_main_bg));
	m_main_bg_sprt.setPosition(0, 0);

	s_logo = "Assets/Menu/Logo.png";
	m_logo_sprt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_logo));
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(s_logo);
	m_logo_sprt.setPosition(SCREEN_WIDTH / 2 - l_texture.getSize().x / 2, (SCREEN_HEIGHT / 100) * 10);

	s_save_gui = "Assets/Menu/saveSelectGUI.png";
	m_save_gui.setTexture(ResourceManager<sf::Texture>::instance()->get(s_save_gui));
	m_save_gui.setPosition(0, 0);

	s_options_gui = "Assets/Menu/options_menu.png";
	m_options_gui.setTexture(ResourceManager<sf::Texture>::instance()->get(s_options_gui));
	m_options_gui.setPosition(0, 0);

	s_save_banner = "Assets/Menu/select_gui_banner.png";
	m_save_banner.setTexture(ResourceManager<sf::Texture>::instance()->get(s_save_banner));
	m_save_banner.setPosition(m_banner_pos);

	s_erase_banner = "Assets/Menu/erase_gui_banner.png";
	m_erase_banner.setTexture(ResourceManager<sf::Texture>::instance()->get(s_erase_banner));
	m_erase_banner.setPosition(m_banner_pos);

	//Load and initalise the Audio for the scene
	s_move_down = "Assets/Audio/Menu/move_down.wav";
	m_move_down.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_move_down));
	s_move_up = "Assets/Audio/Menu/move_up.wav";
	m_move_up.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_move_up));
	s_select = "Assets/Audio/Menu/select.wav";
	m_select.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_select));
	s_bump = "Assets/Audio/Menu/bump.wav";
	m_bump.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_bump));

	s_background_music = "Assets/Audio/Menu/Champion_of_Light.ogg";
	if (!m_background_music.openFromFile(s_background_music))
		cLog::inst()->print(3, "MenuScene", "Background music failed to load");
	m_background_music.setLoop(true);
	m_background_music.setVolume(65.0f);
}
void MenuScene::loadText(){
	sf::Vector2f spacing = m_item_spacing;

	sf::Text text;
	buttons.push_back("Continue");
	buttons.push_back("New Game");
	buttons.push_back("Options");
	buttons.push_back("Exit");
	for (int i = 0; i < buttons.size(); i++){
		text.setFont(m_font);
		text.setString(buttons[i]);
		text.setColor(sf::Color::Black);
		text.setCharacterSize(32);
		spacing = sf::Vector2f(m_item_spacing.x * i, m_item_spacing.y * i);
		text.setPosition(m_item_position + spacing);

		menu_text.push_back(text);
	}
	m_item_spacing = sf::Vector2f(0, 50);

	m_save_select_text.setFont(m_font);
	m_save_select_text.setString("Please select your save slot to load.");
	m_save_select_text.setColor(sf::Color::Black);
	m_save_select_text.setCharacterSize(22);
	m_save_select_text.setPosition(195, 500);

	m_erase_select_text.setFont(m_font);
	m_erase_select_text.setString("Please select a save slot to overwrite.");
	m_erase_select_text.setColor(sf::Color::Black);
	m_erase_select_text.setCharacterSize(22);
	m_erase_select_text.setPosition(195, 500);
}
void MenuScene::setLoader(XMLLoader *l){
	loader = l;
	selected_slot = loader->saved_data[0];
}
void MenuScene::changeState(STATE s) {
	m_select.play();
	switch (s){
	case SPLASH:
		break;
	case MAIN:
		m_current_state = MAIN;
		break;
	case OPTIONS:
		m_current_state = OPTIONS;
		break;
	case GAME:
		m_current_state = GAME;
		break;
	case SAVE_SELECT:
		m_current_state = SAVE_SELECT;
		m_current_slot = SLOT_1;
		generateSaveText();
		break;
	case NEW:
		m_current_state = NEW;
		m_current_slot = SLOT_1;
		generateSaveText();
		break;
	}
}

void MenuScene::generateSaveText() {
	sf::Vector2f text_sep(0, 20);
	sf::Vector2f text_pos;
	sf::Vector2f origin;
	std::stringstream data;
	sf::Text text;

	text.setFont(m_font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(22);
	for (int i = 0; i < 3; i++) {
		SaveText save_text;		//Local save_text to be pushed back to the main
		origin = m_banner_pos + sf::Vector2f(m_banner_sep.x * i, m_banner_sep.y) + sf::Vector2f(25, 50);		//Banner pos + banner sep + aesthetics
		text_pos = sf::Vector2f(0,0);
		
		data.str(std::string());
		data.clear();
		text.setPosition(origin + text_pos + sf::Vector2f(24,-20));
		text.setCharacterSize(26);
		text_pos = text_pos + text_sep;
		data << "Save Slot " << i;
		text.setString(data.str());
		save_text.push_back(text);

		data.str(std::string());
		data.clear();
		text.setPosition(origin + text_pos);
		text.setCharacterSize(22);
		text_pos = text_pos + text_sep;
		data << "Time " << loader->saved_data[i]->m_timePlayed;
		text.setString(data.str());
		save_text.push_back(text);
		
		data.str(std::string());
		data.clear();
		text.setPosition(origin + text_pos);
		text_pos = text_pos + text_sep;
		data << "Gold " << loader->saved_data[i]->m_currentGold;
		text.setString(data.str());
		save_text.push_back(text);

		data.str(std::string());
		data.clear();
		text.setPosition(origin + text_pos);
		text.setCharacterSize(22);
		data << "Lvls " << loader->saved_data[i]->m_levels_unlocked << "/7";
		text.setString(data.str());
		save_text.push_back(text);

		//Push back each SaveText which is just trnslated XML to sf::Text and positioned within my GUI
		m_save_text.push_back(save_text);
	}
}
