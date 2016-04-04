#include "stdafx.h"
#include "Chest.hpp"

Lock::Lock(b2Body *b, bool dir, string text) {
	float m_speed = 185;
	e_texture = text;
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	lock_pos = sf::IntRect{ 0, 38, 10, 11 };
	setOrigin(sf::Vector2f((float)lock_pos.width / 2, (float)lock_pos.height / 2));
	setTextureRect(lock_pos);

	e_body_active = true;
	e_box_body = b;
	e_box_body->SetUserData(this);

	spawn_pos = vHelper::toSF(e_box_body->GetPosition());

	//e_box_body->ApplyForce(vHelper::toB2(sf::Vector2f(dir * )))

	if (dir) {
		setScale(-1, 1);
		e_box_body->ApplyForce(vHelper::toB2(sf::Vector2f(0.75f * m_speed, -1 * m_speed)), e_box_body->GetPosition(), true);
	}
	else
	{	
		setScale(1, 1);
		e_box_body->ApplyForce(vHelper::toB2(sf::Vector2f(-0.75f * m_speed, -1 * m_speed)), e_box_body->GetPosition(), true);
	}
}
Lock::~Lock() {
	e_box_body->GetWorld()->DestroyBody(e_box_body);
	cLog::inst()->print(0, "Chest/Lock", "Lock Destructed.");
}
void Lock::update(FTS fts) {
	alineSprite();

	if (vHelper::distance(spawn_pos, vHelper::toSF(e_box_body->GetPosition())) > 350)
		e_body_active = false;
}
void Lock::render(sf::RenderWindow & w) {	}
void Lock::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}

Chest::Chest() {	}
Chest::Chest(b2Body * bod, bool dir, GemMine * g, Chest::TYPE type) {
	m_type = type;
	bod->SetUserData(this);
	e_box_body = bod;
	e_body_active = true;

	spawn_loot = false;
	e_sword_col = false;
	e_can_despawn = false;
	
	loadMedia();
	alineSprite();

 	m_current_state = CLOSE;
	m_animator.playAnimation(m_current_state, true);
	create_lock = false;
	
	e_direction = dir;
	if (e_direction)	setScale(-1, 1);
	else setScale(1, 1);
	m_mine = g;

	switch (m_type) {
	case BROWN:
		e_hp = 10;
		loot_num = 190;
		break;
	case GREEN:
		e_hp = 20;
		loot_num = 260;
		break;
	case PURPLE:
		e_hp = 30;
		loot_num = 370;
		break;
	}

}
Chest::~Chest()	{	
	cLog::inst()->print(0, "Chest", "Chest Despawned.");
}

void Chest::update(FTS fts, Player * p) {
	alineSprite();
	if (m_current_state == OPEN && m_lock_alive) {
		if (m_lock->e_body_active == false) {
			m_lock->~Lock();
			m_lock_alive = false;
		}
		else
			m_lock->update(fts);
	}

	if (spawn_loot) {
		if (loot_pos == m_loot.size())
			spawn_loot = false;
		if (m_clock.getElapsedTime().asSeconds() > 0.25) {
			m_mine->SpawnGem(m_loot[loot_pos], getPosition(), true, e_direction);
			loot_pos++;
			m_clock.restart();
		}
	}
}
void Chest::addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));
}
void Chest::render(sf::RenderWindow & w, sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);

	if (m_current_state == OPEN && m_lock_alive)
		w.draw(*m_lock);
}

void Chest::loadMedia() {
	switch (m_type) {
	case BROWN:
		m_size = sf::Vector2u(27, 15);
		addFrames(frame_close, 0, 0, 1, 27, 15, 1.0f);
		addFrames(frame_open, 15, 0, 1, 33, 23, 1.0f);
		e_texture = "Assets/Game/brown_chest.png";
		break;
	case GREEN:
		m_size = sf::Vector2u(37, 18);
		addFrames(frame_close, 0, 0, 1, 37, 18, 1.0f);
		addFrames(frame_open, 18, 0, 1, 42, 23, 1.0f);
		e_texture = "Assets/Game/green_chest.png";
		break;
	case PURPLE:
		m_size = sf::Vector2u(37, 18);
		addFrames(frame_close, 0, 0, 1, 37, 18, 1.0f);
		addFrames(frame_open, 18, 0, 1, 42, 23, 1.0f);
		e_texture = "Assets/Game/purple_chest.png";
		break;
	}
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	setOrigin(m_size.x / 2, m_size.y / 2);
	m_animator.addAnimation(OPEN, frame_open, sf::seconds(1.0f));
	m_animator.addAnimation(CLOSE, frame_close, sf::seconds(1.0f));

	s_open = "Assets/Audio/Game/chest_gems.wav";
	m_open.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_open));
	s_hit = "Assets/Audio/Game/chest_hit.wav";
	m_hit.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_hit));
}

void Chest::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}

void Chest::TakeDamage() {
	if (!is_hit && e_hp > 0) {
		e_hp -= 10;
		is_hit = true;
		m_hit.play();
	}
	if (e_hp <= 0 && !create_lock) {
		b2BodyDef myBodyDef;
		b2PolygonShape shape;
		b2FixtureDef myFixtureDef;
		sf::Vector2f size;
		sf::Vector2f pos_off;

		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		size = sf::Vector2f(10, 11);
		pos_off = sf::Vector2f(getPosition().x + size.x / 2, getPosition().y + size.y / 2);
		myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		b2Body* body;
		body = e_box_body->GetWorld()->CreateBody(&myBodyDef);
		shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.5f;
		myFixtureDef.shape = &shape;
		//Left on purpose so all the collision detection is the same. For now...
		myFixtureDef.userData = "Lock";
		myFixtureDef.isSensor = true;

		myFixtureDef.filter.categoryBits = _filterCategory::ENEMY;
		myFixtureDef.filter.maskBits = ENEMY | TERRAIN | PLATFORM;

		body->CreateFixture(&myFixtureDef);

		bool direction = true;

		m_lock = make_shared<Lock>(body, direction, e_texture);
		create_lock = true;
		m_lock_alive = true;
		m_open.play();
		Die();
	}
}

void Chest::Die() {
	int loot_value = rand() % 500;
	loot_value += 190;

	loot_pos = 0;
	spawn_loot = true;
	calculateDrop(loot_value);

	e_body_active = false;
	e_box_body->GetFixtureList()->SetSensor(true);
	if(m_type == BROWN)
		m_size = sf::Vector2u(33, 23 + 8);
	if (!m_type == BROWN)
		m_size = sf::Vector2u(42, 23 + 6);
	setOrigin(m_size.x / 2, m_size.y / 2);

	m_current_state = OPEN;
	m_animator.playAnimation(m_current_state, true);

	is_hit = true;
	m_clock.restart();
}

void Chest::calculateDrop(int amount) {
	int needs_spawn = amount;
	int num_spawn = 0;

	num_spawn = needs_spawn / Gem::TYPE::W_250;
	for (int i = 0; i < num_spawn; i++)
		m_loot.push_back(Gem::TYPE::W_250);
	needs_spawn = needs_spawn % Gem::TYPE::W_250;

	num_spawn = needs_spawn / Gem::TYPE::B_150;
	for (int i = 0; i < num_spawn; i++)
		m_loot.push_back(Gem::TYPE::B_150);
	needs_spawn = needs_spawn % Gem::TYPE::B_150;

	num_spawn = needs_spawn / Gem::TYPE::R_100;
	for (int i = 0; i < num_spawn; i++)
		m_loot.push_back(Gem::TYPE::R_100);
	needs_spawn = needs_spawn % Gem::TYPE::R_100;

	num_spawn = needs_spawn / Gem::TYPE::O_50;
	for (int i = 0; i < num_spawn; i++)
		m_loot.push_back(Gem::TYPE::O_50);
	needs_spawn = needs_spawn % Gem::TYPE::O_50;

	num_spawn = needs_spawn / Gem::TYPE::P_20;
	for (int i = 0; i < num_spawn; i++)
		m_loot.push_back(Gem::TYPE::P_20);
	needs_spawn = needs_spawn % Gem::TYPE::P_20;

	num_spawn = needs_spawn / Gem::TYPE::B_10;
	for (int i = 0; i < num_spawn; i++)
		m_loot.push_back(Gem::TYPE::B_10);
	needs_spawn = needs_spawn % Gem::TYPE::B_10;
}
