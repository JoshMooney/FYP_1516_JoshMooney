#ifndef _CONTACTLISTENER_HPP
#define _CONTACTLISTENER_HPP

#include "Box2D\Box2D.h"

#include "Player.hpp"
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
					s->ReachPlayer();
					p->TakeDamage();
				}
			}
			else if (fixBType == "Skeleton") {
				//if bottom of player touches top of enenmy
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				
				Skeleton* s = static_cast<Skeleton*>(bodyUserData1); //->ReachPlayer();
				Player* p = static_cast<Player*>(bodyUserData2); //->TakeDamage();

				if (p->getBounds().top + p->getBounds().height < s->getBounds().top)	{
					//Kill enemy
					s->TakeDamage();
				}
				else {
					s->ReachPlayer();
					p->TakeDamage();
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
	}
};
#endif