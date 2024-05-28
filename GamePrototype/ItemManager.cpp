#include "pch.h"

#include "ItemManager.h"
#include "Item.h"
#include "SceneManager.h"

void ItemManager::Init(Scene* scene, Player* player)
{
	m_PlayerPtr = player;
	
	m_ItemsMap.emplace(0, scene->CreateGameObjects<Key>(player, 0));
	m_ItemsMap.emplace(1, scene->CreateGameObjects<Key>(player, 1));
	m_ItemsMap.emplace(2, scene->CreateGameObjects<Key>(player, 2));
	m_ItemsMap.emplace(3, scene->CreateGameObjects<Key>(player, 3));
	m_ItemsMap.emplace(4, scene->CreateGameObjects<Key>(player, 4));
	m_ItemsMap.emplace(5, scene->CreateGameObjects<Key>(player, 5));
	m_ItemsMap.emplace(6, scene->CreateGameObjects<Key>(player, 6));
};

void ItemManager::DropItem(const int id, const Point2f& pos)
{
	m_ItemsMap[id]->Drop(pos);
}

void ItemManager::IsCollidingWithPlayer()
{
	for (auto& item : m_ItemsMap)
	{
		if (item.second->IsDropped())
		{
			if (utils::IsOverlapping(item.second->GetShape(), m_PlayerPtr->GetShape()))
			{
				item.second->PickUp();
				//switch scenes
				if (dynamic_cast<Key*>(item.second))
				{
					item.second->SetPos(Point2f{ 775.f - (int)item.second->GetID() * 16, 475.f });

					SceneManager::GetInstance().TranferScene("Level", "Hud", item.second);
					//SceneManager::GetInstance().GetScene("Level")->Remove(item.second);
					//SceneManager::GetInstance().GetScene("Hud")->AddExistingObject(item.second);
				}
			}
		}
	}
}
