#ifndef _CONTACTLISTENER_HPP
#define _CONTACTLISTENER_HPP

#include "Box2D\Box2D.h"

#include "Player.hpp"
#include "CrumbleBlock.hpp"
#include "Sensor.hpp"
#include "Checkpoint.hpp"
#include "Terrain.hpp"
#include "Enemy.hpp"
#include "Skeleton.hpp"

class ContactListener : public b2ContactListener {
private:
	const float player_jump_y_offset = 15;
	const float entity_wall_offset = 10;
public:
	ContactListener() : b2ContactListener() {	}
	/*void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
	
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

		//Ground and Skeleton
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
			}
			else if (fixBType == "Player") {
				void* sensor_data = contact->GetFixtureA()->GetBody()->GetUserData();
				void* player_data = contact->GetFixtureB()->GetBody()->GetUserData();

				Checkpoint* s = static_cast<Checkpoint*>(sensor_data);
				if (!s->hasTripped()) {
					s->trip();
				}
			}
		}

		//Ground and Skeleton
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

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		
	}

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