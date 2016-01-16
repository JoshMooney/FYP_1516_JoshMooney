#include "stdafx.h"
#include "SimpleGUI.hpp"
#include "cLog.hpp"
#include "ResourceManager.hpp"

//SimpleGUI::SimpleGUI() {
//	cLog::inst()->print(3, "Simple GUI", "Default Constructor was called, where no constructor exists");
//}
SimpleGUI::SimpleGUI(string texture, string font, string text) {
	title_texture = "";
	loadMedia(texture, font);

	m_background.setPosition(0, 0);

	m_text = sf::Text("Hello world", m_font);
	m_text.setCharacterSize(24);
	m_text.setStyle(sf::Text::Bold);
	m_text.setColor(sf::Color::Black);
	m_text.setPosition(10, 10);
}
SimpleGUI::SimpleGUI(string texture, sf::Vector2f bg_pos, string font, string text, sf::Vector2f t_offset) {
	title_texture = "";
	loadMedia(texture, font);

	m_background.setPosition(bg_pos);
	m_background.setScale(0.85f, 0.85f);

	text_offset = t_offset;
	m_text_for_gui = text;
	setText("hi");
}
SimpleGUI::SimpleGUI(string texture, sf::Vector2f bg_pos, string font, string text, sf::Vector2f t_offset, string tit_text) {
	title_texture = tit_text;
	loadMedia(texture, font);
	if (title_texture != "") {
		title_bar.setPosition(bg_pos - sf::Vector2f(16, 56));
	}

	m_background.setPosition(bg_pos);
	m_background.setScale(0.85f, 0.85f);

	text_offset = t_offset;
	m_text_for_gui = text;
	setText("hi");
}
SimpleGUI::~SimpleGUI() {

}

void SimpleGUI::loadMedia(string texture, string font) {
	m_font.loadFromFile("Assets/Font/" + font);
	m_background.setTexture(ResourceManager<sf::Texture>::instance()->get("Assets/" + texture));
	if (title_texture != "") {
		title_bar.setTexture(ResourceManager<sf::Texture>::instance()->get("Assets/" + title_texture));
	}
}

void SimpleGUI::setText(string s) {
	m_text.setString(s);
	m_text = sf::Text(s, m_font, 32);
	m_text.setCharacterSize(32);
	m_text.setStyle(sf::Text::Regular);
	m_text.setColor(sf::Color::White);
	m_text.setPosition(m_background.getPosition() + text_offset);
}

void SimpleGUI::setBackgroundPosition(sf::Vector2f p) {
	m_background.setPosition(p);
	m_text.setPosition(p + text_offset);
}

void SimpleGUI::setTextOffet(sf::Vector2f p) {
	text_offset = p;
}

void SimpleGUI::render(sf::RenderWindow &w, string lvl) {
	if(title_texture != "")
		w.draw(title_bar);
	w.draw(m_background);
	/*
	m_text = sf::Text("Hello world", m_font);
	m_text->setCharacterSize(50);
	m_text->setStyle(sf::Text::Regular);
	m_text->setColor(sf::Color::White);
	m_text->setPosition(100,100);
	*/
	/*m_text = new sf::Text("Hello world", m_font);
	m_text->setPosition(200, 200);
	m_text->setCharacterSize(15);
	m_text->setColor(sf::Color::Black);*/
	setText(lvl);

	w.draw(m_text);
}
