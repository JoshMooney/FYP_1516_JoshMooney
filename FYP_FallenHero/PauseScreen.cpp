#include "stdafx.h"
#include "PauseScreen.hpp"

PauseScreen::PauseScreen() {
	s_font = "Assets/Font/Golden Age Shad.ttf";
	m_begin_list_pos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 300);
	m_list_pos = m_begin_list_pos;
	m_y_spacing = 50;

	loadMedia();

	addItem("Resume");
	addItem("Options");
	addItem("Quit");

	m_result = NA;
	m_item_count = 0;
	m_current_item = m_items.begin();
	m_current_item->setColor(sf::Color::Yellow);
}
PauseScreen::~PauseScreen() {

}

void PauseScreen::loadMedia() {
	s_splash = "Assets/Game/fade.png";
	m_splash_sprt.setPosition(0, 0);
	m_splash_sprt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_splash));

	//Load and initalise the Audio for the scene
	s_move_down = "Assets/Audio/Menu/move_down.wav";
	m_move_down.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_move_down));
	s_move_up = "Assets/Audio/Menu/move_up.wav";
	m_move_up.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_move_up));
	s_select = "Assets/Audio/Menu/select.wav";
	m_select.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_select));
	s_bump = "Assets/Audio/Menu/bump.wav";
	m_bump.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_bump));

	m_title_pos = sf::Vector2f(m_begin_list_pos.x, m_begin_list_pos.y - 100);

	m_title.setFont(ResourceManager<sf::Font>::instance()->get(s_font));
	m_title.setString("Pause");
	m_title.setColor(sf::Color::Black);
	m_title.setCharacterSize(60);
	m_title.setPosition(m_title_pos);
	sf::FloatRect textRect = m_title.getLocalBounds();
	m_title.setOrigin(textRect.width / 2, textRect.height / 2);

	s_title = "Assets/Game/wings.png";
	m_title_sprt.setPosition(m_title_pos);
	m_title_sprt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_title));
	sf::FloatRect titleRect = m_title_sprt.getLocalBounds();
	m_title_sprt.setOrigin(titleRect.width / 2, titleRect.height / 2 + 60);

	s_banner = "Assets/Game/pause_banner.png";
	sf::Vector2f banner_pos = m_begin_list_pos + sf::Vector2f(0, 120);
	m_banner_sprt.setPosition(banner_pos);
	m_banner_sprt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_banner));
	sf::FloatRect bannerRect = m_banner_sprt.getLocalBounds();
	m_banner_sprt.setOrigin(bannerRect.width / 2, bannerRect.height / 2 + 60);
}

void PauseScreen::addItem(string name) {
	sf::Text text;
	text.setFont(ResourceManager<sf::Font>::instance()->get(s_font));
	text.setString(name);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(32);
	sf::Vector2f pos = sf::Vector2f(0, m_y_spacing * m_items.size());
	text.setPosition(m_list_pos + pos);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);

	m_items.push_back(text);
}
bool PauseScreen::isPaused() {
	return m_is_pause;
}
void PauseScreen::setPaused(bool b){
	m_is_pause = b;
	if (!m_is_pause) {
		m_result = NA;
		m_current_item->setColor(sf::Color::Black);
		m_current_item = m_items.begin();
		m_current_item->setColor(sf::Color::Yellow);
	}
}
void PauseScreen::select() {
	string selected = m_current_item->getString();
	m_select.play(); 

	if (selected == "Resume")
		m_result = RESUME;
	if (selected == "Quit")
		m_result = QUIT;
}
void PauseScreen::moveUp() {
	if (m_current_item != m_items.begin()){
		m_current_item->setColor(sf::Color::Black);
		m_current_item--;
		m_current_item->setColor(sf::Color::Yellow);
		m_move_up.play();
	}
	else
		m_bump.play();
}
void PauseScreen::moveDown() {
	if (m_current_item != --m_items.end()){
		m_current_item->setColor(sf::Color::Black);
		m_current_item++;
		m_current_item->setColor(sf::Color::Yellow);
		m_move_down.play();
	}
	else
		m_bump.play();
}
PauseScreen::RESULT& PauseScreen::getResult(){
	return m_result;
}

void PauseScreen::update() {
	 
}
void PauseScreen::render(sf::RenderWindow &w, sf::Time &framse) {
	w.draw(m_splash_sprt);

	w.draw(m_banner_sprt);
	w.draw(m_title_sprt);
	w.draw(m_title);


	for (sf::Text t : m_items) {
		w.draw(t);
	}
}