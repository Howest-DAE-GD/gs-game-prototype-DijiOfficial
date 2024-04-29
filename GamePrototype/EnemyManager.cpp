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
    auto it = m_Enemies.begin();
    while (it != m_Enemies.end())
    {
        if ((*it)->GetState() == EnemyState::DEAD)
            it = m_Enemies.erase(it);
        else
        {
            (*it)->Update();
            ++it;
        }
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
