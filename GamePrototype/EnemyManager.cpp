#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Scene.h"

EnemyManager::EnemyManager(Scene* scene)
	: GameObject{ scene }
{

}

void EnemyManager::Update()
{
	for (auto& enemy : m_Enemies)
	{
		enemy->Update();
	}
}

void EnemyManager::Render() const 
{
	for (const auto& enemy : m_Enemies)
	{
		enemy->Render();
	}
}

void EnemyManager::AddEnemy(Player* player, const Point2f& pos)
{
	m_Enemies.push_back(std::make_unique<Goblin>(GetOwner(), player, pos));
}

void EnemyManager::AddEnemy(Scene* scene, Player* player, const Point2f& pos)
{
	m_Enemies.push_back(std::make_unique<Goblin>(scene, player, pos));
}
