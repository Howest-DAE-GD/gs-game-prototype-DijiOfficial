#pragma once
#include "Singleton.h"
#include "structs.h"
#include <map>
#include <vector>

class GameObject;
class Player;

class CollisionSingleton final : public Singleton<CollisionSingleton>
{
public:
	void AddPlayer(Player* player);
	void AddCollider(GameObject* object, const Rectf& collider);
	void RemoveCollider(GameObject* object);

	void UpdateCollider(GameObject* object, const Rectf& collider);

	void IsColliding(GameObject* object);
	bool HitEnemyType(const Rectf& shape);
	bool HitPlayerType(const Rectf& shape, const int damage);

	unsigned int PlayerHitTrigger(std::vector<std::vector<Point2f>>& collision);

private:
	std::map<GameObject*, Rectf> m_Colliders;
	Player* m_PlayerPtr;
};

