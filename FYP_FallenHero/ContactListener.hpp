#ifndef _CONTACTLISTENER_HPP
#define _CONTACTLISTENER_HPP

#include "Box2D\Box2D.h"

#include "Player.hpp"
#include "Terrain.hpp"
#include "Enemy.hpp"
#include "Skeleton.hpp"

class ContactListener : public b2ContactListener {
private:
	const float player_jump_y_offset = 10;
public:
	ContactListener() : b2ContactListener() {	}

	/*void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
	void* fixAType = contact->GetFixtureA()->GetBody()->GetUserData();
	void* fixBType = contact->GetFixtureB()->GetBody()->GetUserData();
	if (fixAType == "Player" && fixBType == "Bullet"
	|| fixAType == "Bullet" && fixBType == "Player")
	{
	if (fixAType == "Player")
	{
	void* bodyUserData1 = contact->GetFixtureA()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetUserData();
	if (static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1()
	|| static_cast<Player*>(bodyUserData1)->isPlayer1() == false && static_cast<Bullet*>(bodyUserData2)->isBullet1() == false)
	{
	contact->SetEnabled(false);
	}
	else
	{
	AudioManager::GetInstance()->PlaySoundEffect(3);
	}
	}
	if (fixAType == "Bullet")
	{
	void* bodyUserData1 = contact->GetFixtureB()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureA()->GetUserData();
	if (static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1()
	|| static_cast<Player*>(bodyUserData1)->isPlayer1() == false && static_cast<Bullet*>(bodyUserData2)->isBullet1() == false)
	{
	contact->SetEnabled(false);
	}
	else
	{
	AudioManager::GetInstance()->PlaySoundEffect(3);
	}
	}
	}
	}*/

	void BeginContact(b2Contact* contact) {
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		//Player and Terrain
		if (fixAType == "Terrain" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Terrain") {

			Terrain* t;
			Player* p;
			if (fixAType == "Player") {
				//If Botton of Enemy touches top of Terrain
				//Get pointers to the objects
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				p = static_cast<Player*>(bodyUserData1);
				if (p->isJumping()) {
					b2Vec2 p_pos = contact->GetFixtureA()->GetBody()->GetPosition();
					b2Vec2 t_pos = contact->GetFixtureB()->GetBody()->GetPosition();
					sf::FloatRect player_geo = p->getBounds();
					sf::FloatRect terrain_geo = static_cast<Terrain*>(bodyUserData2)->geometry;

					if (player_geo.top + player_geo.height >= terrain_geo.top - player_jump_y_offset &&
						player_geo.top + player_geo.height <= terrain_geo.top)
						p->setJumping(false);
				}
			}
			else if (fixBType == "Player") {
				//If Botton of Enemy touches top of Terrain
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				p = static_cast<Player*>(bodyUserData1);
				if (p->isJumping()) {
					b2Vec2 p_pos = contact->GetFixtureB()->GetBody()->GetPosition();
					b2Vec2 t_pos = contact->GetFixtureA()->GetBody()->GetPosition();
					sf::FloatRect player_geo = p->getBounds();
					sf::FloatRect terrain_geo = static_cast<Terrain*>(bodyUserData2)->geometry;

					if (player_geo.top + player_geo.height >= terrain_geo.top - player_jump_y_offset &&
						player_geo.top + player_geo.height <= terrain_geo.top)
						p->setJumping(false);
				}
			}
		}

		//Ground and Skeleton
		else if (fixAType == "Skeleton" && fixBType == "Terrain"
			|| fixAType == "Terrain" && fixBType == "Skeleton") {
			
			if (fixAType == "Skeleton") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				Terrain* t = static_cast<Terrain*>(bodyUserData2);
				static_cast<Skeleton*>(bodyUserData1)->isTouching(t);
			}
			else if (fixBType == "Skeleton") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				Terrain* t = static_cast<Terrain*>(bodyUserData2);
				static_cast<Skeleton*>(bodyUserData1)->isTouching(t);
			}
		}

		//Player and Skeleton
		else if (fixAType == "Skeleton" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Skeleton") {

			if (fixAType == "Skeleton") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
		
				Skeleton* s = static_cast<Skeleton*>(bodyUserData1); //->ReachPlayer();
				Player* p = static_cast<Player*>(bodyUserData2); //->TakeDamage();

				if (p->getBounds().top + p->getBounds().height < s->getBounds().top)	{
					//Kill enemy
					s->TakeDamage();
				}
				else {
					static_cast<Skeleton*>(bodyUserData1)->ReachPlayer();
					static_cast<Player*>(bodyUserData2)->TakeDamage();
				}
			}
			else if (fixBType == "Skeleton") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				
				static_cast<Skeleton*>(bodyUserData1)->ReachPlayer();
				static_cast<Player*>(bodyUserData2)->TakeDamage();
			}
		}
		/*
		if (fixAType == "Player" && fixBType == "Platform"
		|| fixAType == "Platform" && fixBType == "Player") {
		if (fixAType == "Player") {
		void* bodyUserData1 = contact->GetFixtureA()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureB()->GetUserData();
		b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

		b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

		if (posPlat.y - (20 / 60.0f) > posPlayer.y + 16 / 30.0f)
		static_cast<Player*>(bodyUserData1)->Ground();
		static_cast<Platform*>(bodyUserData2)->ToggleMove();
		}
		else if (fixBType == "Player") {
		void* bodyUserData1 = contact->GetFixtureB()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureA()->GetUserData();
		b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

		b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

		if (posPlat.y - (20 / 60.0f) > posPlayer.y + 16 / 30.0f)
		static_cast<Player*>(bodyUserData1)->Ground();

		static_cast<Platform*>(bodyUserData2)->ToggleMove();
		}
		}

		if (fixAType == "Bullet" && fixBType == "Boundary"
		|| fixAType == "Boundary" && fixBType == "Bullet") {
		if (fixAType == "Bullet") {
		void* bodyUserData1 = contact->GetFixtureA()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureB()->GetUserData();
		static_cast<Bullet*>(bodyUserData1)->HitWall();
		}
		else if (fixBType == "Bullet") {
		void* bodyUserData1 = contact->GetFixtureB()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureA()->GetUserData();
		static_cast<Bullet*>(bodyUserData1)->HitWall();

		}
		}

		if (fixAType == "Player" && fixBType == "Bullet"
		|| fixAType == "Bullet" && fixBType == "Player") {
		if (fixAType == "Player") {
		void* bodyUserData1 = contact->GetFixtureA()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureB()->GetUserData();
		if (static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1())
		{
		static_cast<Player*>(bodyUserData1)->PickupBullet();
		static_cast<Bullet*>(bodyUserData2)->Reset();
		}
		else if (!static_cast<Player*>(bodyUserData1)->isPlayer1() && !static_cast<Bullet*>(bodyUserData2)->isBullet1()) {
		static_cast<Player*>(bodyUserData1)->PickupBullet();
		static_cast<Bullet*>(bodyUserData2)->Reset();
		}
		else if (!static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1())
		{
		if (static_cast<Bullet*>(bodyUserData2)->getAlive()) {
		level->ChangeLevel();
		static_cast<Bullet*>(bodyUserData2)->Reset();
		}
		}
		else if (static_cast<Player*>(bodyUserData1)->isPlayer1() && !static_cast<Bullet*>(bodyUserData2)->isBullet1()) {
		if (static_cast<Bullet*>(bodyUserData2)->getAlive()) {
		level->ChangeLevel();
		static_cast<Bullet*>(bodyUserData2)->Reset();

		}
		}
		}
		else if (fixBType == "Player") {
		void* bodyUserData1 = contact->GetFixtureB()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureA()->GetUserData();
		if (static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1())
		{
		static_cast<Player*>(bodyUserData1)->PickupBullet();
		static_cast<Bullet*>(bodyUserData2)->Reset();
		}
		else if (!static_cast<Player*>(bodyUserData1)->isPlayer1() && !static_cast<Bullet*>(bodyUserData2)->isBullet1()) {
		static_cast<Player*>(bodyUserData1)->PickupBullet();
		static_cast<Bullet*>(bodyUserData2)->Reset();
		}
		else if (!static_cast<Player*>(bodyUserData1)->isPlayer1() && static_cast<Bullet*>(bodyUserData2)->isBullet1())
		{
		if (static_cast<Bullet*>(bodyUserData2)->getAlive()) {

		level->ChangeLevel();
		static_cast<Bullet*>(bodyUserData2)->Reset();
		}
		}
		else if (static_cast<Player*>(bodyUserData1)->isPlayer1() && !static_cast<Bullet*>(bodyUserData2)->isBullet1()) {
		if (static_cast<Bullet*>(bodyUserData2)->getAlive()) {

		level->ChangeLevel();
		static_cast<Bullet*>(bodyUserData2)->Reset();
		}
		}
		}
		}*/
	}

	void EndContact(b2Contact* contact) {
		void* fixAType = contact->GetFixtureA()->GetBody()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetBody()->GetUserData();
		/*
		if (fixAType == "Player" && fixBType == "Platform"
		|| fixAType == "Platform" && fixBType == "Player")
		{
		if (fixAType == "Player") {
		void* bodyUserData1 = contact->GetFixtureA()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureB()->GetUserData();
		b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

		b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

		if (posPlat.y - (20 / 60.0f) > posPlayer.y + 16 / 30.0f)
		static_cast<Player*>(bodyUserData1)->SetGrounded(false);
		static_cast<Platform*>(bodyUserData2)->ToggleMove();
		}
		else if (fixBType == "Player") {
		void* bodyUserData1 = contact->GetFixtureB()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureA()->GetUserData();
		b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

		b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

		if (posPlat.y - (20 / 60.0f) > posPlayer.y + 16 / 30.0f)
		static_cast<Player*>(bodyUserData1)->SetGrounded(false);

		static_cast<Platform*>(bodyUserData2)->ToggleMove();
		}
		}*/
	}
};
#endif