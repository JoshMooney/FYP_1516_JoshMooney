#include <stdafx.h>
#include "Subject.hpp"

Subject* Subject::mInstance = nullptr;

Subject::Subject() {

}

void Subject::notify(EVENT e, Entity *entity_) {
	for (int i = 0; i < observers_.size(); i++){
		observers_[i]->onNotify(e, entity_);
	}
}

void Subject::addObserver(Observer* o) {
	observers_.push_back(o);
}

void Subject::removeObserver(Observer *o) {
	std::vector<Observer*>::iterator begin = observers_.begin();
	std::vector<Observer*>::iterator end = observers_.end();

	auto iter = std::remove(begin, end, o);
	if (iter != end)
		observers_.erase(iter);
}

void Subject::update() {
	for (int i = 0; i < observers_.size(); i++) {
		observers_[i]->update();
	}
}

void Subject::render(sf::RenderWindow * w) {
	for (int i = 0; i < observers_.size(); i++) {
		observers_[i]->render(w);
	}
}

Subject::~Subject() {		}

Subject* Subject::instance() {
	if (!mInstance) {
		mInstance = new Subject();
	}
	return mInstance;
}