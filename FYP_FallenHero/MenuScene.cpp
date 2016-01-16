#include "stdafx.h"
#include "MenuScene.hpp"
#include "ResourceManager.hpp"

MenuScene::MenuScene(){
	m_item_position = sf::Vector2f(SCREEN_WIDTH - ((SCREEN_WIDTH / 100) * 28), SCREEN_HEIGHT - ((SCREEN_HEIGHT / 100) * 36));
	m_item_spacing = sf::Vector2f(0, 50);
	m_key_pressed = false;

	loadMedia();
	loadText();

	m_current_state = SPLASH;
	m_current_menu_item = M_CONTINUE;
	menu_text[M_CONTINUE].setColor(sf::Color::Yellow);

	cLog::inst()->print("MenuScene Initalised");
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
			break;
		case M_NEW:
			menu_text[M_CONTINUE].setColor(sf::Color::Yellow);
			m_current_menu_item = M_CONTINUE;
			menu_text[M_NEW].setColor(sf::Color::Black);
			break;
		case M_OPTIONS:
			menu_text[M_NEW].setColor(sf::Color::Yellow);
			m_current_menu_item = M_NEW;
			menu_text[M_OPTIONS].setColor(sf::Color::Black);
			break;
		case M_EXIT:
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
			menu_text[M_NEW].setColor(sf::Color::Yellow);
			m_current_menu_item = M_NEW;
			menu_text[M_CONTINUE].setColor(sf::Color::Black);
			break;
		case M_NEW:
			menu_text[M_OPTIONS].setColor(sf::Color::Yellow);
			m_current_menu_item = M_OPTIONS;
			menu_text[M_NEW].setColor(sf::Color::Black);
			break;
		case M_OPTIONS:
			menu_text[M_EXIT].setColor(sf::Color::Yellow);
			m_current_menu_item = M_EXIT;
			menu_text[M_OPTIONS].setColor(sf::Color::Black);
			break;
		case M_EXIT:
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

	}
}
void MenuScene::moveLeft(){
	if (m_current_state == MAIN){

	}
	if (m_current_state == SAVE_SELECT){

	}
}
void MenuScene::select(){
	cLog::inst()->print("Select Pressed");
	if (m_current_state == MAIN)
		switch (m_current_menu_item)
		{
		case M_CONTINUE:
			m_current_state = SAVE_SELECT;
			break;
		case M_NEW:
			m_current_state = GAME;
			break;
		case M_OPTIONS:
			m_current_state = OPTIONS;
			break;
		case M_EXIT:
			m_current_state = CLOSE;
			break;
		}
	if (m_current_state == SPLASH)
		m_current_state = MAIN;
}
void MenuScene::back(){
	if (m_current_state == SAVE_SELECT){
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
	//s_logo.setScale(sf::Vector2f(2.0, 2.0));
	m_logo_sprt.setPosition(SCREEN_WIDTH / 2 - l_texture.getSize().x / 2, (SCREEN_HEIGHT / 100) * 10);

	s_save_gui = "Assets/Menu/saveSelectGUI.png";
	m_save_gui.setTexture(ResourceManager<sf::Texture>::instance()->get(s_save_gui));
	m_save_gui.setPosition(0, 0);
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
}
void MenuScene::setLoader(XMLLoader *l){
	loader = l;
}
void MenuScene::changeState(STATE s) {
	switch (m_current_slot){
	case SPLASH:
		break;
	case MAIN:
		m_current_menu_item = M_CONTINUE;
		break;
	case OPTIONS:
		break;
	case SAVE_SELECT:
		m_current_slot = SLOT_1;
		break;
	}
}