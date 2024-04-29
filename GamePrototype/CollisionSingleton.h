#pragma once
#include "Singleton.h"
#include <map>
#include "structs.h"

class GameObject;
//class Player;

class CollisionSingleton final : public Singleton<CollisionSingleton>
{
public:
	//void AddPlayer(Player* player);
	void AddCollider(GameObject* object, const Rectf& collider);
	void RemoveCollider(GameObject* object);

	void UpdateCollider(GameObject* object, const Rectf& collider);

	void IsColliding(GameObject* object);
	bool HitEnemyType(const Rectf& shape);

private:
	std::map<GameObject*, Rectf> m_Colliders;
	//Player* m_PlayerPtr;
};

