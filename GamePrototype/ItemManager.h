#pragma once
#include "Singleton.h"
#include "Item.h"
#include <map>

class ItemManager final : public Singleton<ItemManager>
{
public:
	//ItemManager(Scene* scene, Player* player);
	~ItemManager() override = default;

	void Init(Scene* scene, Player* player);
	void DropItem(const int id, const Point2f& pos);

	void IsCollidingWithPlayer();

private:
	std::map<int, Item*> m_ItemsMap;

	Player* m_PlayerPtr;
};

