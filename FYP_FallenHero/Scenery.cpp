#include "stdafx.h"
#include "Scenery.hpp"

struct myclass {
	bool operator() (ParallaxSprite ps1, ParallaxSprite ps2) { return (ps1.getDefaultPosition().z < ps2.getDefaultPosition().z); }
} myobject;

Scenery::Scenery() {

}

Scenery::~Scenery()	{	}

void Scenery::renderBG(sf::RenderWindow * w, vCamera cam) {

}
void Scenery::renderFG(sf::RenderWindow * w, vCamera cam) {

}

void Scenery::sortBG() {
	std::sort(bg.begin(), bg.end(), myobject);
}
void Scenery::sortFG() {

}

void Scenery::insertBG(ParallaxSprite ps) {
	bg.push_back(ps);
}
void Scenery::insertFG(ParallaxSprite ps) {
	bg.push_back(ps);
	sortFG();
}

void Scenery::clear() {
	bg.clear();
	fg.clear();
}
