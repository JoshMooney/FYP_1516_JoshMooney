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
	sf::Sprite m_background, title_bar;
	string m_texture, title_texture;
	string m_text_for_gui;

	sf::Vector2f text_offset;

	SimpleGUI();
public:
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*/
	SimpleGUI(string texture, string font, string text);
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*	@param
	*	@param
	*/
	SimpleGUI(string texture, sf::Vector2f bg_pos, string font, string text, sf::Vector2f t_offset);
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*	@param
	*	@param
	*	@param
	*/
	SimpleGUI(string texture, sf::Vector2f bg_pos, string font, string text, sf::Vector2f t_offset, string title_texture);
	~SimpleGUI();

	/**
	*	@brief
	*	@param
	*	@param
	*/
	void loadMedia(string texture, string font);
	/**
	*	@brief
	*	@param
	*/
	void setText(string s);
	/**
	*	@brief
	*	@param
	*/
	void setBackgroundPosition(sf::Vector2f p);
	/**
	*	@brief
	*	@param
	*/
	void setTextOffet(sf::Vector2f p);

	/**
	*	@brief
	*	@param
	*	@param
	*/
	void render(sf::RenderWindow &w, string lvl);
};

#endif