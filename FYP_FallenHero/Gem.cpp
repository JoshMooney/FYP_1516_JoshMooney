#include "stdafx.h"
#include "Gem.hpp"
#include "vHelper.hpp"

Gem::Gem() {		}
Gem::Gem(b2Body *b, sf::Vector2f pos, TYPE t){
	b->SetUserData(this);
	b->SetTransform(vHelper::toB2(pos), 0.0f);
	e_box_body = b;
	type_ = t;

	init();
	
	alineSprite();
}
Gem::~Gem()	{	}

void Gem::init(){
	e_body_active = true;
	e_hp = 1;
	e_max_hp = 1;

	loadMedia();
}

void Gem::loadMedia(){
	e_texture = "Assets/Game/gem.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));

	switch (type_){
	case B_10:
		m_texture_rect = sf::IntRect{ 7, 10, 6, 6 };
		break;
	case P_20:
		m_texture_rect = sf::IntRect{ 27, 8, 8, 8 };
		break;
	case O_50:
		m_texture_rect = sf::IntRect{ 48, 4, 9, 12 };
		break;
	case R_100:
		m_texture_rect = sf::IntRect{ 67, 7, 13, 3 };
		break;
	case B_150:
		m_texture_rect = sf::IntRect{ 86, 3, 17, 13 };
		break;
	case W_250:
		m_texture_rect = sf::IntRect{ 105, 0, 21, 16 };
		break;
	}
	setTextureRect(m_texture_rect);
	setOrigin(m_texture_rect.width / 2, m_texture_rect.height / 2);

	s_pickup = "Assets/Audio/Game/gem_pickup.wav";
	m_pickup.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_pickup));
}

void Gem::update(FTS fts) {

}

void Gem::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}

int Gem::pickup(){
	float value = 0;
	m_pickup.play();
	e_body_active = false;

	switch (type_){
	case B_10:
		value = 10;
		break;
	case P_20:
		value = 20;
		break;
	case O_50:
		value = 50;
		break;
	case R_100:
		value = 100;
		break;
	case B_150:
		value = 150;
		break;
	case W_250:
		value = 250;
		break;
	}

	return value;
}


/* Notes - 
switch (type_){
case B_10:
	break;
case P_20:
	break;
case O_50:
	break;
case R_100:
	break;
case B_150:
	break;
case W_250:
	break;
}

*/