#include "stdafx.h"
#include "Scenery.hpp"

struct BGSorter {
	bool operator() (ParallaxSprite ps1, ParallaxSprite ps2) { return (ps1.getDefaultPosition().z > ps2.getDefaultPosition().z); }
} BG_sort;
struct FGSorter {
	bool operator() (ParallaxSprite ps1, ParallaxSprite ps2) { return (ps1.getDefaultPosition().z < ps2.getDefaultPosition().z); }
} FG_sort;

Scenery::Scenery() {

}

Scenery::~Scenery()	{	}

void Scenery::renderBG(sf::RenderWindow &w, vCamera *cam) {
	for (int i = 0; i < bg.size(); i++) {
		float x = cam->getX() * bg[i].getDefaultPosition().z;//Find Parallax Offset
		//x = bg[i].getDefaultPosition().z;
		bg[i].setPosition(sf::Vector2f(x, bg[i].getDefaultPosition().y));		//Set Sprite to the Parallax Offset position

		w.draw(bg[i]);															//Render the ParallaxSprite
	}
}
void Scenery::renderFG(sf::RenderWindow &w, vCamera *cam) {
	for (int i = 0; i < fg.size(); i++) {
		float x = cam->getX() * fg[i].getDefaultPosition().z;					//Find Parallax Offset
		//Broken Needs to be changed !!!
		if (x == 0)	x = fg[i].getDefaultPosition().z;
		fg[i].setPosition(sf::Vector2f(x, fg[i].getDefaultPosition().y));		//Set Sprite to the Parallax Offset position

		w.draw(fg[i]);															//Render the ParallaxSprite
	}
}

void Scenery::sortBG() {
	std::sort(bg.begin(), bg.end(), BG_sort);
}
void Scenery::sortFG() {
	std::sort(fg.begin(), fg.end(), FG_sort);
}

void Scenery::insertBG(ParallaxSprite &ps) {
	bg.push_back(ps);
}
void Scenery::insertFG(ParallaxSprite &ps) {
	fg.push_back(ps);
}

void Scenery::clear() {
	bg.clear();
	fg.clear();
}
