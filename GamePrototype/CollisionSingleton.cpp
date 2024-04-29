#include "pch.h"

#include "CollisionSingleton.h"
#include "GameObject.h"
#include "Enemy.h"

//void CollisionSingleton::AddPlayer(Player* player)
//{
//	m_PlayerPtr = player;
//}

void CollisionSingleton::AddCollider(GameObject* object, const Rectf& collider)
{
	m_Colliders[object] = collider;
}

void CollisionSingleton::RemoveCollider(GameObject* object)
{
	auto it = m_Colliders.find(object);
	if (it != m_Colliders.end())
		m_Colliders.erase(it);
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
				//Bullets* bullet = dynamic_cast<Bullets*>(pair.first);
				//if (bullet)
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
			Enemy* enemy = dynamic_cast<Enemy*>(pair.first);
			if (enemy)
			{
				enemy->Hit();//can add damage or more info to this call later
				hit = true;
			}
		}
	}

	return hit;
}