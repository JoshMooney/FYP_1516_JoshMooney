#include "stdafx.h"
#include "MenuScene.hpp"
#include "ResourceManager.hpp"

MenuScene::MenuScene(){
	m_item_position = sf::Vector2f(SCREEN_WIDTH - ((SCREEN_WIDTH / 100) * 25), SCREEN_HEIGHT - ((SCREEN_HEIGHT / 100) * 30));
	m_item_spacing = sf::Vector2f(0, 50);
	m_key_pressed = false;

	loadMedia();
	loadText();

	m_current_state = SPLASH;
	m_current_menu_item = M_PLAY;
	m_play_text.setColor(sf::Color::Yellow);

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

		w.draw(m_play_text);
		w.draw(m_options_text);
		w.draw(m_exit_text);
	}
}
void MenuScene::handleEvent(sf::Event &e){
	if (e.type == sf::Event::KeyPressed){
		switch (e.key.code){
		case sf::Keyboard::Up:
			if ((m_current_state == MAIN || m_current_state == OPTIONS) && !m_key_pressed){
				m_key_pressed = true;
				moveUp();
			}
			break;
		case sf::Keyboard::Down:
			if ((m_current_state == MAIN || m_current_state == OPTIONS) && !m_key_pressed){
				m_key_pressed = true;
				moveDown();
			}
			break;
		case sf::Keyboard::Return:
			if ((m_current_state == MAIN || m_current_state == OPTIONS) && !m_key_pressed){
				m_key_pressed = true;
				select();
			}
			else
				m_current_state = MAIN;
			break;
		case sf::Keyboard::Space:
			if ((m_current_state == MAIN || m_current_state == OPTIONS) && !m_key_pressed){
				m_key_pressed = true;
				select();
			}
			else
				m_current_state = MAIN;
			break;
		default:
			m_key_pressed = false;
			break;
		}
	}
	else
		m_key_pressed = false;
}
void MenuScene::handleInput(){

}

void MenuScene::moveUp(){
	switch (m_current_menu_item){
	case M_PLAY:
		break;
	case M_OPTIONS:
		m_play_text.setColor(sf::Color::Yellow);
		m_current_menu_item = M_PLAY;

		m_options_text.setColor(sf::Color::Black);
		break;
	case M_EXIT:
		m_options_text.setColor(sf::Color::Yellow);
		m_current_menu_item = M_OPTIONS;

		m_exit_text.setColor(sf::Color::Black);
		break;
	}
}
void MenuScene::moveDown(){
	switch (m_current_menu_item){
	case M_PLAY:
		m_options_text.setColor(sf::Color::Yellow);
		m_current_menu_item = M_OPTIONS;

		m_play_text.setColor(sf::Color::Black);
		break;
	case M_OPTIONS:
		m_exit_text.setColor(sf::Color::Yellow);
		m_current_menu_item = M_EXIT;

		m_options_text.setColor(sf::Color::Black);
		break;
	case M_EXIT:
		break;
	}
}
void MenuScene::select(){
	switch (m_current_menu_item)
	{
	case M_PLAY:
		m_current_state = GAME;
		break;
	case M_OPTIONS:
		m_current_state = OPTIONS;
		break;
	case M_EXIT:
		m_current_state = CLOSE;
		break;
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
}
void MenuScene::loadText(){
	m_play_text.setFont(m_font);
	m_play_text.setString("Play");
	m_play_text.setColor(sf::Color::Black);
	m_play_text.setCharacterSize(32);
	m_play_text.setPosition(m_item_position);

	m_options_text.setFont(m_font);
	m_options_text.setString("Options");
	m_options_text.setColor(sf::Color::Black);
	m_options_text.setCharacterSize(32);
	m_options_text.setPosition(m_item_position + m_item_spacing);

	m_exit_text.setFont(m_font);
	m_exit_text.setString("Exit");
	m_exit_text.setColor(sf::Color::Black);
	m_exit_text.setCharacterSize(32);
	m_item_spacing = sf::Vector2f(0, 50 * 2);
	m_exit_text.setPosition(m_item_position + m_item_spacing);

	m_item_spacing = sf::Vector2f(0, 50);
}