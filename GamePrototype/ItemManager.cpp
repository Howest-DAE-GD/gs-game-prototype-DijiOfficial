#include "pch.h"

#include "ItemManager.h"
#include "Item.h"
#include "SceneManager.h"
#include "ItemCounter.h"
#include "SVGParser.h"

void ItemManager::Init(Scene* scene, Player* player)
{
	m_PlayerPtr = player;
	
	SVGParser::GetVerticesFromSvgFile("BonusCoins.svg", m_VerticesVec);
	SVGParser::ParseSVGData(m_VerticesVec);

	for (const auto& vec : m_VerticesVec)
	{
		for (const auto& pos : vec)
		{
			m_ItemsMap.emplace(70, scene->CreateGameObjects<BonusCoin>(player, pos));
		}
	}

	m_ItemsMap.emplace(0, scene->CreateGameObjects<FinalKey>(player, 0));
	m_ItemsMap.emplace(1, scene->CreateGameObjects<Key>(player, 1));
	m_ItemsMap.emplace(2, scene->CreateGameObjects<Key>(player, 1));
	m_ItemsMap.emplace(3, scene->CreateGameObjects<Key>(player, 1));
	m_ItemsMap.emplace(4, scene->CreateGameObjects<Key>(player, 1));
	m_ItemsMap.emplace(5, scene->CreateGameObjects<Key>(player, 1));
	m_ItemsMap.emplace(6, scene->CreateGameObjects<Key>(player, 1));
	m_ItemsMap.emplace(7, scene->CreateGameObjects<Key>(player, 999));
	m_ItemsMap.emplace(69, scene->CreateGameObjects<Coin>(player));
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
					SceneManager::GetInstance().GetScene("Hud")->GetGameObject<ItemCounter>()->AddKey();
				}
				if (dynamic_cast<FinalKey*>(item.second))
				{
					SceneManager::GetInstance().GetScene("Hud")->GetGameObject<ItemCounter>()->AddFinalKey();
				}
				if (dynamic_cast<Coin*>(item.second))
				{
					SceneManager::GetInstance().GetScene("Hud")->GetGameObject<ItemCounter>()->AddCoin();
				}
			}
		}
	}
}

bool ItemManager::HasKey(const unsigned int doorId) const
{
	for (auto& item : m_ItemsMap)
	{
		if (item.second->GetID() == doorId and item.second->IsOwned())
		{
			return true;
		}
	}
	return false;
}

void ItemManager::UseKey(const unsigned int doorId)
{
	for (auto& item : m_ItemsMap)
	{
		if (item.second->GetID() == doorId)
		{
			item.second->SetUsed();
		}
	}
}
