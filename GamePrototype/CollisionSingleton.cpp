#include "pch.h"

#include "CollisionSingleton.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include "Boss.h"

void CollisionSingleton::AddPlayer(Player* player)
{
	m_PlayerPtr = player;
}

void CollisionSingleton::AddCollider(GameObject* object, const Rectf& collider)
{
	m_Colliders[object] = collider;
}

void CollisionSingleton::RemoveCollider(GameObject* object)
{
	if (object == nullptr or m_Colliders.empty()) return;

	auto it = m_Colliders.find(object);
	if (it != m_Colliders.end())
	{
		m_Colliders.erase(it);
	}
}

void CollisionSingleton::UpdateCollider(GameObject* object, const Rectf& collider)
{
	m_Colliders[object] = collider;
}

void CollisionSingleton::IsColliding(GameObject* object)
{
	auto collidersCopy = m_Colliders; //copy because collider may be removed
	for (auto& pair : collidersCopy)
	{
		if (pair.first != object)
		{
			if (utils::IsOverlapping(m_Colliders[object], pair.second))
			{
				//Enemy* enemy = dynamic_cast<Enemy*>(pair.first);
				//if (enemy)
				//{
				//	//delete object
				//	//object
				//}
				//else
				//{
				//	//object->NotifyCollisionSingleton(MessageTypes::ENEMY_COLLISION);
				//}
			}
		}
		//else
		//{
		//	const auto t = m_PlayerPtr->GetTransform();
		//}
	}
}

bool CollisionSingleton::HitEnemyType(const Rectf& shape)
{
	bool hit = false;
	auto collidersCopy = m_Colliders; //copy because collider may be removed
	for (auto& pair : collidersCopy)
	{
		if (utils::IsOverlapping(shape, pair.second))
		{
			const auto& damage = m_PlayerPtr->GetDamage();

			Enemy* enemy = dynamic_cast<Enemy*>(pair.first);
			if (enemy)
			{
				enemy->Hit(damage);//can add damage or more info to this call later
				hit = true;
			}

			Boss* boss = dynamic_cast<Boss*>(pair.first);
			if (boss)
			{
				boss->Hit(damage); //currently hard coded get it from the player
				hit = true;
			}
		}
	}

	return hit;
}

bool CollisionSingleton::HitPlayerType(const Rectf& shape, const int damage)
{
	if (m_PlayerPtr->IsInvincible())
		return false;

	bool hit = false;

	if (utils::IsOverlapping(shape, m_PlayerPtr->GetShape()))
	{
		m_PlayerPtr->DealDamage(damage);
		hit = true;
	}

	return hit;
}

unsigned int CollisionSingleton::PlayerHitTrigger(std::vector<std::vector<Point2f>>& collision)
{
	const auto& playerShape = m_PlayerPtr->GetShape();
	unsigned int idx = 0;

	for (const auto& collisionBox : collision)
	{
		const Point2f bottomLeft(playerShape.left, playerShape.bottom);
		const Point2f topLeft(playerShape.left, playerShape.bottom + playerShape.height);

		utils::HitInfo hitInfo;
		if (utils::Raycast(collisionBox, bottomLeft, topLeft, hitInfo))
			return idx;

		const Point2f topRight(playerShape.left + playerShape.width, playerShape.bottom + playerShape.height);
		if (utils::Raycast(collisionBox, topLeft, topRight, hitInfo))
			return idx;


		const Point2f bottomRight(playerShape.left + playerShape.width, playerShape.bottom);
		if (utils::Raycast(collisionBox, topRight, bottomRight, hitInfo))
			return idx;

		(void)hitInfo;
		++idx;
	}
	return -1;
	
}
