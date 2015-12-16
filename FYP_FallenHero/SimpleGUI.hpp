#ifndef _SIMPLE_GUI_HPP
#define _SIMPLE_GUI_HPP
#include "stdafx.h"

#include <string>
#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Text.hpp"
#include <memory>

class SimpleGUI {
private:
	sf::Text m_text;
	sf::Font m_font;
	sf::Sprite m_background;
	string m_texture;
	string m_text_for_gui;

	sf::Vector2f text_offset;

	SimpleGUI();
public:
	SimpleGUI(string texture, string font, string text);
	SimpleGUI(string texture, sf::Vector2f bg_pos, string font, string text, sf::Vector2f t_offset);
	~SimpleGUI();

	void loadMedia(string texture, string font);
	void setText(string s);
	void setBackgroundPosition(sf::Vector2f p);
	void setTextOffet(sf::Vector2f p);

	void render(sf::RenderWindow &w, string lvl);
};

#endif