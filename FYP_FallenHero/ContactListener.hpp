#ifndef _CONTACTLISTENER_HPP
#define _CONTACTLISTENER_HPP

#include "Box2D\Box2D.h"

#include "Player.hpp"
#include "CrumbleBlock.hpp"
#include "Checkpoint.hpp"
#include "Sensor.hpp"
#include "Terrain.hpp"
#include "Enemy.hpp"
#include "Skeleton.hpp"
#include "Platform.hpp"
#include "OneWayPlatform.hpp"
#include "FadePlatform.hpp"
#include "XYPlatform.hpp"

#include "Cannon.hpp"
#include "Gem.hpp"
#include "Projectile.hpp"

#include "Subject.hpp"

/**
*	@class ContactListener
*	@brief This is the box2D contactlistener that detects and responds to collision 	
*	as it happens using callbacks.
*/
class ContactListener : public b2ContactListener {
private:
	const float player_jump_y_offset = 15;
	const float entity_wall_offset = 10;
public:
	/**
	*	@brief
	*/
	ContactListener() : b2ContactListener() {	}
	/*void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
	
	}*/
	
	/**
	*	@brief This is the Box2d callback called when two box bodies begin colliding 
	*	@param b2Contact This is the colliding point of two boxbodies
	*/
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
					sf::Vector2f t_pos = vHelper::toSF(contact->GetFixtureB()->GetBody()->GetPosition());
					sf::FloatRect player_geo = p->getBounds();

					Terrain* terrain = reinterpret_cast<Terrain*>(bodyUserData2);
					terrain = static_cast<Terrain*>(bodyUserData2);
					//terrain = dynamic_cast<Terrain*>(bodyUserData2);

					sf::FloatRect terrain_geo = terrain->geometry;
					
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

		//Projectile and Player
		if (fixAType == "Projectile" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Projectile") {

			Projectile* b;
			void* player_data;
			void* bullet_data;

			if (fixAType == "Player") {
				player_data = contact->GetFixtureA()->GetBody()->GetUserData();
				bullet_data = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				bullet_data = contact->GetFixtureA()->GetBody()->GetUserData();
				player_data = contact->GetFixtureB()->GetBody()->GetUserData();
			}

			b = static_cast<Projectile*>(bullet_data);
			bool dir = !b->getBoolDirection();
			static_cast<Player*>(player_data)->TakeDamage(dir);
			b->Die();

			Subject::instance()->notify(Subject::BULLET_HIT, nullptr);
		}

		
		//Player and Cannon
		if (fixAType == "Cannon" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Cannon") {
			Player* p;
			void* player_data;
			void* cannon_data;

			if (fixAType == "Player") {
				player_data = contact->GetFixtureA()->GetBody()->GetUserData();
				cannon_data = contact->GetFixtureB()->GetBody()->GetUserData();
				p = static_cast<Player*>(player_data);
			}
			else {
				cannon_data = contact->GetFixtureA()->GetBody()->GetUserData();
				player_data = contact->GetFixtureB()->GetBody()->GetUserData();
				p = static_cast<Player*>(player_data);
			}

			if (p->isJumping()) {
				sf::FloatRect player_geo = p->getBounds();
				sf::FloatRect cannon_geo = static_cast<Cannon*>(cannon_data)->getBounds();

				if (player_geo.top + player_geo.height >= cannon_geo.top - player_jump_y_offset &&
					player_geo.top + player_geo.height <= cannon_geo.top)
					p->setJumping(false);
			}
		}

		//Player Sword and Cannon
		if (fixAType == "Cannon" && fixBType == "Player_Sword"
			|| fixAType == "Player_Sword" && fixBType == "Cannon") {

			if (fixAType == "Player_Sword") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Cannon*>(bodyUserData2)->setCollidingSword(true);
			}
			else if (fixBType == "Player_Sword") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Cannon*>(bodyUserData2)->setCollidingSword(true);
			}
		}

		//Player and Platform
		if (fixAType == "Platform" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Platform") {

			void* player_userdata;
			void* platform_userdata;
			if (fixAType == "Player") {
				player_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				player_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			Player* player = static_cast<Player*>(player_userdata);
			Platform* platform = static_cast<Platform*>(platform_userdata);

			if (player->isJumping()) {
				sf::FloatRect plat_geo = platform->geometry();
				sf::FloatRect player_geo = player->getBounds();

				if (player_geo.top + player_geo.height >= plat_geo.top - player_jump_y_offset &&
					player_geo.top + player_geo.height <= plat_geo.top)
					player->setJumping(false);
			}
		}

		//Player and Chest
		if (fixAType == "Chest" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Chest") {

			void* player_userdata;
			void* chest_userdata;
			if (fixAType == "Player") {
				player_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				chest_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				player_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				chest_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			Player* player = static_cast<Player*>(player_userdata);
			Chest* chest = static_cast<Chest*>(chest_userdata);

			if (player->isJumping()) {
				sf::FloatRect chest_geo = chest->geometry();
				sf::FloatRect player_geo = player->getBounds();
				player->setJumping(false);
			/*	if (player_geo.top + player_geo.height >= chest_geo.top - player_jump_y_offset &&
					player_geo.top + player_geo.height <= chest_geo.top)
					player->setJumping(false);*/
			}
		}

		//Player and XY-Platform
		if (fixAType == "XY-Platform" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "XY-Platform") {

			void* player_userdata;
			void* plat_userdata;
			if (fixAType == "Player") {
				player_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				plat_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				player_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				plat_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			Player* player = static_cast<Player*>(player_userdata);
			XYPlatform* plat = static_cast<XYPlatform*>(plat_userdata);

			if (player->isJumping()) {
				sf::FloatRect plat_geo = plat->geometry();
				sf::FloatRect player_geo = player->getBounds();

				if (player_geo.top + player_geo.height >= plat_geo.top - player_jump_y_offset &&
					player_geo.top + player_geo.height <= plat_geo.top)
					player->setJumping(false);
			}
		}

		//Player_Sword and Chest
		if (fixAType == "Chest" && fixBType == "Player_Sword"
			|| fixAType == "Player_Sword" && fixBType == "Chest") {

			void* sword_userdata;
			void* chest_userdata;
			if (fixAType == "Player_Sword") {
				sword_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				chest_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				sword_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				chest_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			static_cast<Chest*>(chest_userdata)->setCollidingSword(true);
		}

		//Player and OneWay Platform
		if (fixAType == "OneWay-Platform" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "OneWay-Platform") {

			void* player_userdata;
			void* platform_userdata;
			if (fixAType == "Player") {
				player_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				player_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			Player* player = static_cast<Player*>(player_userdata);
			OneWayPlatform* platform = static_cast<OneWayPlatform*>(platform_userdata);

			if (player->isJumping()) {
				sf::FloatRect plat_geo = platform->geometry();
				sf::FloatRect player_geo = player->getBounds();

				if (player_geo.top + player_geo.height >= plat_geo.top - player_jump_y_offset &&
					player_geo.top + player_geo.height <= plat_geo.top)
					player->setJumping(false);
			}
		}

		//Player and Fade-Platform
		if (fixAType == "Fade-Platform" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Fade-Platform") {

			void* player_userdata;
			void* platform_userdata;
			if (fixAType == "Player") {
				player_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				player_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			Player* player = static_cast<Player*>(player_userdata);
			FadePlatform* platform = static_cast<FadePlatform*>(platform_userdata);

			if (player->isJumping() && !platform->getBody()->GetFixtureList()->IsSensor()) {
				sf::FloatRect plat_geo = platform->geometry();
				sf::FloatRect player_geo = player->getBounds();

				if (player_geo.top + player_geo.height >= plat_geo.top - player_jump_y_offset &&
					player_geo.top + player_geo.height <= plat_geo.top)
					player->setJumping(false);
			}
		}

		//Platform and Block
		if (fixAType == "Fade-Platform" && fixBType == "Block"
			|| fixAType == "Block" && fixBType == "Fade-Platform") {

			void* block_userdata;
			void* platform_userdata;
			if (fixAType == "Block") {
				block_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				block_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}
			static_cast<CrumbleBlock*>(block_userdata)->setTouchingFade(true);
			//CrumbleBlock* block = static_cast<CrumbleBlock*>(block_userdata);
			//block->setTouchingFade(true);
		}

		//Player and Blocks
		if (fixAType == "Block" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Block") {

			Player* p;
			if (fixAType == "Player") {
				void* player_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* block_data = contact->GetFixtureB()->GetBody()->GetUserData();
				p = static_cast<Player*>(player_data);

				if (p->isJumping()) {
					sf::FloatRect player_geo = p->getBounds();
					sf::FloatRect block_geo = static_cast<CrumbleBlock*>(block_data)->getBounds();

					if (player_geo.top + player_geo.height >= block_geo.top - player_jump_y_offset &&
						player_geo.top + player_geo.height <= block_geo.top)
						p->setJumping(false);
				}
			}
			if (fixBType == "Player") {
				void* block_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* player_data = contact->GetFixtureB()->GetBody()->GetUserData();
				p = static_cast<Player*>(player_data);

				if (p->isJumping()) {
					sf::FloatRect player_geo = p->getBounds();
					sf::FloatRect block_geo = static_cast<CrumbleBlock*>(block_data)->getBounds();

					if (player_geo.top + player_geo.height >= block_geo.top - player_jump_y_offset &&
						player_geo.top + player_geo.height <= block_geo.top)
						p->setJumping(false);
				}
			}
		}

		//Terrain and Skeleton
		else if (fixAType == "Skeleton" && fixBType == "Terrain"
			|| fixAType == "Terrain" && fixBType == "Skeleton") {
			
			if (fixAType == "Skeleton") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				sf::FloatRect t = static_cast<Terrain*>(bodyUserData2)->geometry;
				sf::FloatRect s = static_cast<Skeleton*>(bodyUserData1)->getBounds();

				//Right Side
				if (s.left + s.width > t.left - entity_wall_offset &&
					s.left + s.width < t.left)
					static_cast<Skeleton*>(bodyUserData1)->ReachWall();
				//Left Side
				else if (s.left > t.left + t.width + entity_wall_offset &&
					s.left < t.left + t.width)
					static_cast<Skeleton*>(bodyUserData1)->ReachWall();
				//Else set touching ground to be the skeleton ground
				else {
					Terrain* t = static_cast<Terrain*>(bodyUserData2);
					static_cast<Skeleton*>(bodyUserData1)->isTouching(t);
				}
			}
			else if (fixBType == "Skeleton") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				sf::FloatRect t = static_cast<Terrain*>(bodyUserData2)->geometry;
				sf::FloatRect s = static_cast<Skeleton*>(bodyUserData1)->getBounds();

				sf::IntRect int_s = vHelper::FloatToInt(s);
				//Right Side
				if (int_s.left + int_s.width >= t.left - entity_wall_offset &&
					int_s.left + int_s.width <= t.left)
					static_cast<Skeleton*>(bodyUserData1)->ReachWall();
				//Left Side
				else if (int_s.left >= t.left + t.width + entity_wall_offset &&
					int_s.left <= t.left + t.width)
					static_cast<Skeleton*>(bodyUserData1)->ReachWall();
				//Else set touching ground to be the skeleton ground
				else {
					Terrain* t = static_cast<Terrain*>(bodyUserData2);
					static_cast<Skeleton*>(bodyUserData1)->isTouching(t);
				}
			}
		}

		//Sensor and Player
		else if (fixAType == "Sensor" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Sensor") {

			if (fixAType == "Player") {
				void* player_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* sensor_data = contact->GetFixtureB()->GetBody()->GetUserData();

				Sensor* s = static_cast<Sensor*>(sensor_data);
				if (!s->hasTripped()) {
					s->trip();
				}
			}
			else if (fixBType == "Player") {
				void* sensor_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* player_data = contact->GetFixtureB()->GetBody()->GetUserData();

				Sensor* s = static_cast<Sensor*>(sensor_data);
				if (!s->hasTripped()) {
					s->trip();
				}
			}
		}

		//Checkpoint and Player
		else if (fixAType == "Checkpoint" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Checkpoint") {

			if (fixAType == "Player") {
				void* player_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* sensor_data = contact->GetFixtureB()->GetBody()->GetUserData();

				Checkpoint* s = static_cast<Checkpoint*>(sensor_data);
				if (!s->hasTripped()) {
					s->trip();
				}
				Subject::instance()->notify(Subject::CP_TRIP, nullptr);
			}
			else if (fixBType == "Player") {
				void* sensor_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* player_data = contact->GetFixtureB()->GetBody()->GetUserData();

				Checkpoint* s = static_cast<Checkpoint*>(sensor_data);
				if (!s->hasTripped()) {
					s->trip();
				}
				Subject::instance()->notify(Subject::CP_TRIP, nullptr);
			}
		}

		//Block and Skeleton
		else if (fixAType == "Skeleton" && fixBType == "Block"
			|| fixAType == "Block" && fixBType == "Skeleton") {

			if (fixAType == "Skeleton") {
				void* skele_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* block_data = contact->GetFixtureB()->GetBody()->GetUserData();

				sf::FloatRect t = static_cast<CrumbleBlock*>(block_data)->getBounds();
				sf::FloatRect s = static_cast<Skeleton*>(skele_data)->getBounds();

				//Right Side
				if (s.left + s.width > t.left - entity_wall_offset &&
					s.left + s.width < t.left)
					static_cast<Skeleton*>(skele_data)->ReachWall();
				//Left Side
				else if (s.left > t.left + t.width + entity_wall_offset &&
					s.left < t.left + t.width)
					static_cast<Skeleton*>(skele_data)->ReachWall();
				//Else set touching ground to be the skeleton ground
				//else {
				//	CrumbleBlock* t = static_cast<CrumbleBlock*>(block_data);
				//	static_cast<Skeleton*>(skele_data)->isTouching(t);
				//}
			}
			else if (fixBType == "Skeleton") {
				void* block_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* skele_data = contact->GetFixtureB()->GetBody()->GetUserData();

				sf::FloatRect t = static_cast<CrumbleBlock*>(block_data)->getBounds();
				sf::FloatRect s = static_cast<Skeleton*>(skele_data)->getBounds();

				//Right Side
				if (s.left + s.width > t.left - entity_wall_offset &&
					s.left + s.width < t.left)
					static_cast<Skeleton*>(skele_data)->ReachWall();
				//Left Side
				else if (s.left > t.left + t.width + entity_wall_offset &&
					s.left < t.left + t.width)
					static_cast<Skeleton*>(skele_data)->ReachWall();
				//Else set touching ground to be the skeleton ground
				//else {
				//	CrumbleBlock* t = static_cast<CrumbleBlock*>(block_data);
				//	static_cast<Skeleton*>(skele_data)->isTouching(t);
				//}
			}
		}

		//Player and Gem
		else if (fixAType == "Gem" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "Gem") {

			if (fixAType == "Gem") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				Gem* g = static_cast<Gem*>(bodyUserData1); 
				Player* p = static_cast<Player*>(bodyUserData2);
				if (g->e_body_active) {
					p->addGold(g->pickup());
				}
			}
			else if (fixBType == "Gem") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				Gem* g = static_cast<Gem*>(bodyUserData1);
				Player* p = static_cast<Player*>(bodyUserData2);
				if (g->e_body_active) {
					p->addGold(g->pickup());
				}
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
				if (s->isAlive()) {
					if (p->getBounds().top + p->getBounds().height < s->getBounds().top) {
						//Kill enemy
						s->TakeDamage();
					}
					else {
						s->ReachPlayer();
						if(s->getCenter().x > p->getCenter().x)
							p->TakeDamage(0);		//Knockback Left
						else
							p->TakeDamage(1);		//Knockback Left
					}
				}
			}
			else if (fixBType == "Skeleton") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				
				Skeleton* s = static_cast<Skeleton*>(bodyUserData1); //->ReachPlayer();
				Player* p = static_cast<Player*>(bodyUserData2); //->TakeDamage();
				if (s->isAlive()) {
					if (p->getBounds().top + p->getBounds().height < s->getBounds().top) {
						//Kill enemy
						s->TakeDamage();
					}
					else {
						s->ReachPlayer();
						if (s->getCenter().x > p->getCenter().x)
							p->TakeDamage(0);		//Knockback Left
						else
							p->TakeDamage(1);		//Knockback Left
					}
				}
			}
		}

		//Player Sword and Skeleton
		else if (fixAType == "Skeleton" && fixBType == "Player_Sword"
			|| fixAType == "Player_Sword" && fixBType == "Skeleton") {

			if (fixAType == "Player_Sword") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Skeleton*>(bodyUserData2)->setCollidingSword(true); 
			}
			else if (fixBType == "Player_Sword") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Skeleton*>(bodyUserData2)->setCollidingSword(true);
			}
		}
	
		//Player Sword and Block
		else if (fixAType == "Block" && fixBType == "Player_Sword"
			|| fixAType == "Player_Sword" && fixBType == "Block") {

			if (fixAType == "Player_Sword") {
				void* sword_fix = contact->GetFixtureA()->GetBody()->GetUserData();
				void* block_fix = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<CrumbleBlock*>(block_fix)->setCollidingSword(true);
			}
			else if (fixBType == "Player_Sword") {
				void* block_fix = contact->GetFixtureA()->GetBody()->GetUserData();
				void* sword_fix = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<CrumbleBlock*>(block_fix)->setCollidingSword(true);
			}
		}
	}

	/**
	*	@brief This is the presolve for box2d this is the function called when 
	*	a collision has taken place and continues to collide with another bodyUserData
	*	aka. If colliding but not the first 
	*	@param b2Contact This is the colliding point of two boxbodies
	*	@param b2Manifold
	*/
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		//Block and Gem
		if (fixAType == "Gem" && fixBType == "Block"
			|| fixAType == "Block" && fixBType == "Gem") {

			if (fixAType == "Gem") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				Gem* g = static_cast<Gem*>(bodyUserData1);
				CrumbleBlock* b = static_cast<CrumbleBlock*>(bodyUserData2);
				if (g->e_body_active && !b->e_body_active) {
					contact->SetEnabled(false);
				}
			}
			else if (fixBType == "Gem") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				Gem* g = static_cast<Gem*>(bodyUserData1);
				CrumbleBlock* b = static_cast<CrumbleBlock*>(bodyUserData2);
				if (g->e_body_active && !b->e_body_active) {
					contact->SetEnabled(false);
				}
			}
		}
			
		//Player and OneWay Platform
		if (fixAType == "OneWay-Platform" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "OneWay-Platform") {

			void* player_userdata;
			void* platform_userdata;
			if (fixAType == "Player") {
				player_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				player_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			Player* player = static_cast<Player*>(player_userdata);
			OneWayPlatform* platform = static_cast<OneWayPlatform*>(platform_userdata);

			if (player->isJumping()) {
				int numPoints = contact->GetManifold()->pointCount;
				b2WorldManifold worldManifold;
				contact->GetWorldManifold(&worldManifold);

				//check if contact points are moving downward
				for (int i = 0; i < numPoints; i++) {
					b2Vec2 pointVel =
						player->getBody()->GetLinearVelocityFromWorldPoint(worldManifold.points[i]);
					if (pointVel.y > 0)
						return;//point is moving down, leave contact solid and exit
				}
				contact->SetEnabled(false);
			}
		}
	}

	/**
	*	@brief This is the Box2d callback called when two box bodies end contact. 
	*	@param b2Contact This is the colliding point of two boxbodies
	*/
	void EndContact(b2Contact* contact) {
		void* fixAType = contact->GetFixtureA()->GetBody()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetBody()->GetUserData();
		
		//Player Sword and Skeleton
		if (fixAType == "Skeleton" && fixBType == "Player_Sword"
			|| fixAType == "Player_Sword" && fixBType == "Skeleton") {

			if (fixAType == "Player_Sword") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Skeleton*>(bodyUserData1)->setCollidingSword(false);
			}
			else if (fixBType == "Player_Sword") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Skeleton*>(bodyUserData1)->setCollidingSword(false);
			}
		}

		//Player and OneWay Platform
		if (fixAType == "OneWay-Platform" && fixBType == "Player"
			|| fixAType == "Player" && fixBType == "OneWay-Platform") {

			void* player_userdata;
			void* platform_userdata;
			if (fixAType == "Player") {
				player_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				player_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}

			contact->SetEnabled(true);
		}
		//Platform and Block
		if (fixAType == "Fade-Platform" && fixBType == "Block"
			|| fixAType == "Block" && fixBType == "Fade-Platform") {

			void* block_userdata;
			void* platform_userdata;
			if (fixAType == "Block") {
				block_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else {
				block_userdata = contact->GetFixtureB()->GetBody()->GetUserData();
				platform_userdata = contact->GetFixtureA()->GetBody()->GetUserData();
			}
			static_cast<CrumbleBlock*>(block_userdata)->setTouchingFade(false);
		}

		//Player Sword and Block
		else if (fixAType == "Block" && fixBType == "Player_Sword"
			|| fixAType == "Player_Sword" && fixBType == "Block") {

			if (fixAType == "Player_Sword") {
				void* sword_fix = contact->GetFixtureA()->GetBody()->GetUserData();
				void* block_fix = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<CrumbleBlock*>(block_fix)->setCollidingSword(false);
			}
			else if (fixBType == "Player_Sword") {
				void* block_fix = contact->GetFixtureA()->GetBody()->GetUserData();
				void* sword_fix = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<CrumbleBlock*>(block_fix)->setCollidingSword(false);
			}
		}
	}
};
#endif