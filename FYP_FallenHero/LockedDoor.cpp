#include "stdafx.h"
#include "LockedDoor.hpp"

Door::Door() {		}
Door::Door(b2Body * b, string id, bool dir, bool locked) {
	m_id = id;
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	m_dis_to_player = 250;
	
	if (locked)
		m_can_prompt = true;
	else
		m_can_prompt = false;

	m_controller_input = xboxConnector::inst()->isConnected();
	m_prev_ci = false;
	m_lock = true;
	e_sword_col = false;
	e_can_despawn = false;

	m_prompt_active = false;
	loadMedia();
	alineSprite();
	m_prompt_pos = sf::Vector2f(0, -50);

	if (locked)
		m_current_state = LOCKED;
	else {
		m_current_state = HIDDEN;
		e_box_body->GetFixtureList()->SetSensor(true);
	}

	//Flip sprite if direction needs to be changed
	if (dir)
		setScale(-1, 1);
	else
		setScale(1, 1);

	m_previous_state = m_current_state;
	m_animator.playAnimation(m_current_state, true);
}
Door::Door(b2Body * b, string id, vector<string> *keys) {
	m_id = id;
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	m_dis_to_player = 250;

	for (int i = 0; i < keys->size(); i++)
		m_req_keys[keys->at(i)] = false;
	if (keys->size() > 0)
		m_can_prompt = true;
	else
		m_can_prompt = false;

	m_controller_input = xboxConnector::inst()->isConnected();
	m_prev_ci = false;
	m_lock = true;
	e_sword_col = false;
	e_can_despawn = false;

	m_prompt_active = false;
	loadMedia();
	alineSprite();
	m_prompt_pos = sf::Vector2f(0, -50);

	m_current_state = LOCKED;
	m_previous_state = m_current_state;
	m_animator.playAnimation(m_current_state, true);
}
Door::Door(b2Body * b, string id, vector<string>* keys, bool dir) {
	m_id = id;
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	m_dis_to_player = 250;

	for (int i = 0; i < keys->size(); i++)
		m_req_keys[keys->at(i)] = false;
	if (keys->size() > 0)
		m_can_prompt = true;
	else
		m_can_prompt = false;

	m_controller_input = xboxConnector::inst()->isConnected();
	m_prev_ci = false;
	m_lock = true;
	e_sword_col = false;
	e_can_despawn = false;

	m_prompt_active = false;
	loadMedia();
	alineSprite();
	m_prompt_pos = sf::Vector2f(0, -50);

	m_current_state = LOCKED;
	m_previous_state = m_current_state;
	m_animator.playAnimation(m_current_state, true);

	//Flip sprite if direction needs to be changed
	if (dir) 
		setScale(-1, 1);
	else
		setScale(1, 1);
}
Door::Door(b2Body * b, string id, vector<string>* keys, bool dir, bool locked) {
	m_id = id;
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	m_dis_to_player = 250;

	for (int i = 0; i < keys->size(); i++)
		m_req_keys[keys->at(i)] = false;
	if (locked)
		m_can_prompt = true;
	else
		m_can_prompt = false;

	m_controller_input = xboxConnector::inst()->isConnected();
	m_prev_ci = false;
	m_lock = locked;
	e_sword_col = false;
	e_can_despawn = false;

	m_prompt_active = false;
	loadMedia();
	alineSprite();
	m_prompt_pos = sf::Vector2f(0, -50);

	if (m_lock) {
		m_current_state = LOCKED;
	}
	if (!m_lock) {
		m_current_state = HIDDEN;
		e_box_body->GetFixtureList()->SetSensor(true);
	}
	m_previous_state = m_current_state;
	m_animator.playAnimation(m_current_state, true);

	//Flip sprite if direction needs to be changed
	if (dir)
		setScale(-1, 1);
	else
		setScale(1, 1);
}
Door::~Door() {		
	cLog::inst()->print("Door destroyed.");
}

void Door::update(FTS fts, Player * p) {
	//If the Door can prompt the player or not
	if (vHelper::distance(p->getPosition(), getPosition()) < m_dis_to_player && m_can_prompt)
		m_prompt_active = true;
	else
		m_prompt_active = false;

	//Change the prompt if required for when a controller is connected or disconnected mid play and the prompts need to be swapped
	if (xboxConnector::inst()->isConnected() != m_controller_input) {
		m_controller_input = xboxConnector::inst()->isConnected();
		changePrompt();
	}
	
	//If prompt active posiiton it above the player
	if (m_prompt_active) {
		sf::Vector2f p_pos = p->getPosition();
		m_prompt_spt.setPosition(p_pos + m_prompt_pos);
	}

	checkAnimation();
}

void Door::render(sf::RenderWindow & w, sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);

	if (m_prompt_active)
		w.draw(m_prompt_spt);
}

void Door::loadMedia() {
	s_prompt_spt = "Assets/Game/door_prompt.png";
	m_prompt_spt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_prompt_spt));
	m_prompt_spt.setOrigin(32 / 2, 32 / 2);

	m_prompt_spt.setTextureRect(sf::IntRect{ 32 * m_controller_input, 0, 32, 32 });

	e_texture = "Assets/Game/locked_door.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_size = sf::Vector2u(64, 160);
	setOrigin(m_size.x / 2, m_size.y / 2);
	if (m_req_keys.size() == 0) {
		addFrames(frame_locked, 2, 0, 1, m_size.x, m_size.y, 1.0f);
		addFrames(frame_unlock, 2, 0, 3, m_size.x, m_size.y, 1.0f);
	}
	if (m_req_keys.size() == 1) {
		addFrames(frame_locked, 0, 0, 1, m_size.x, m_size.y, 1.0f);
		addFrames(frame_unlock, 0, 0, 3, m_size.x, m_size.y, 1.0f);
	}
	if (m_req_keys.size() == 2) {
		addFrames(frame_locked, 3, 0, 1, m_size.x, m_size.y, 1.0f);
		addFrames(frame_unlock, 3, 0, 3, m_size.x, m_size.y, 1.0f);
	}
	addFrames(frame_fade_out,	1, 0, 7, m_size.x, m_size.y, 1.0f);
	addFrames(frame_hidden,		0, 3, 4, m_size.x, m_size.y, 1.0f);
	for (int x = 7; x != 0; x -= 1)
		frame_fade_in.addFrame(1.0f, sf::IntRect(m_size.x * x, m_size.y, m_size.x, m_size.y));

	m_animator.addAnimation(LOCKED,		frame_locked,	sf::seconds(1.0f));
	m_animator.addAnimation(UNLOCK,		frame_unlock,	sf::seconds(0.15f));
	m_animator.addAnimation(FADE_OUT,	frame_fade_out, sf::seconds(0.35f));
	m_animator.addAnimation(FADE_IN,	frame_fade_in,	sf::seconds(1.0f));
	m_animator.addAnimation(HIDDEN,		frame_hidden,	sf::seconds(1.0f));

	s_unlock = "Assets/Audio/Game/Door/unlock.wav";
	m_unlock.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_unlock));
	s_locked = "Assets/Audio/Game/Door/lock.wav";
	m_locked.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_locked));
	s_cant_open = "Assets/Audio/Game/Door/cannot_open.wav";
	m_cant_open.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_cant_open));
	s_hit = "Assets/Audio/Game/Door/hit.wav";
	m_hit.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_hit));
}

void Door::addFrames(thor::FrameAnimation & animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
	if (y == 0)
		y = 0;
	else if (y == 1)
		y = 160;
	else if (y == 2)
		y = 320;
	else if (y == 3)
		y = 480;

	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));
}

void Door::checkAnimation() {
	if (m_previous_state != m_current_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}
	if (m_current_state == UNLOCK && !m_animator.isPlayingAnimation())
		m_current_state = FADE_OUT;
	else if (m_current_state == FADE_OUT && !m_animator.isPlayingAnimation()) {
		m_current_state = HIDDEN;
	}
	else if (m_current_state == FADE_IN && !m_animator.isPlayingAnimation()) {
		m_current_state = LOCKED;
	}

}

void Door::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}
void Door::TakeDamage() {
	if (!is_hit) {
		m_hit.play();
		is_hit = true;
	}
}
void Door::Die() {		}
void Door::attack() {		}

bool Door::checkKeys(vector<string>* collected) {
	//Compair the Key lists
	for (int i = 0; i < collected->size(); i++) {
		auto it = m_req_keys.find(collected->at(i));
		if (it != m_req_keys.end())
			(*it).second = true;
	}

	//Check if all keys have been gotten
	auto first = m_req_keys.begin();
	auto last = m_req_keys.end();
	while (first != last) {
		if (!(*first).second) {
			m_cant_open.play();
			return false;
		}
		++first;
	}
	return true;
}

void Door::changePrompt() {
	m_prompt_spt.setTextureRect(sf::IntRect{ 32 * m_controller_input, 0, 32, 32 });
	//m_prompt_spt.setTexture(ResourceManager<sf::Texture>::instance()->get(s_prompt_spt));
}

bool Door::canUnlock() {
	//Check if all keys have been gotten
	auto first = m_req_keys.begin();
	auto last = m_req_keys.end();
	while (first != last) {
		if (!(*first).second) return false;
		++first;
	}
	return true;
}

void Door::unlock() {
	m_current_state = UNLOCK;
	m_unlock.play();
	m_can_prompt = false;
	m_lock = false;
	e_box_body->GetFixtureList()->SetSensor(true);
}

void Door::lock() {
	m_locked.play();
	m_lock = true;
	m_current_state = FADE_IN;
	m_can_prompt = false;
	e_box_body->GetFixtureList()->SetSensor(false);
}
