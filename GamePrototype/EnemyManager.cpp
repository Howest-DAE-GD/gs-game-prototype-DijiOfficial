#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "SVGParser.h"

#include <thread>

EnemyManager::EnemyManager(Scene* scene, Player* player)
	: GameObject{ scene }
    , m_Player{ player }
{
    SVGParser::GetVerticesFromSvgFile("Enemies.svg", m_EnemiesPos);

    SVGParser::ParseSVGData(m_EnemiesPos);
    ParseEnemyData(m_EnemiesPos);
}

void EnemyManager::Update()
{
    for (const auto& enemy : m_Enemies)
    {
        if (enemy->GetState() != EnemyState::DEAD)
		    enemy->Update();
	}
    //if (m_Enemies.empty())
    //    return;

    //auto it = m_Enemies.begin();
    //while (it != m_Enemies.end())
    //{
    //    if (not (*it))
    //        continue;

    //    if ((*it)->GetState() == EnemyState::DEAD)
    //        it = m_Enemies.erase(it);
    //    else
    //    {
    //        (*it)->Update();
    //        ++it;
    //    }
    //}
}

void EnemyManager::Render() const 
{
	for (const auto& enemy : m_Enemies)
	{
		enemy->Render();
	}
}

void EnemyManager::Reset()
{
    for (const auto& enemy : m_Enemies)
    {
		enemy->Reset();
	}
    m_Enemies.clear();

    ParseEnemyData(m_EnemiesPos);
}

void EnemyManager::AddEnemy(Player* player, const Point2f& pos)
{
	m_Enemies.push_back(std::make_unique<Goblin>(GetOwner(), player, pos));
}

void EnemyManager::AddEnemy(Scene* scene, Player* player, const Point2f& pos)
{
	m_Enemies.push_back(std::make_unique<Goblin>(scene, player, pos));
}

void EnemyManager::ParseEnemyData(std::vector<std::vector<Point2f>> enemies)
{
    const auto& scene = GetOwner();

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        const EnemyType type = static_cast<EnemyType>(i);
        switch (type)
        {
        case EnemyType::GOBLIN:
            for (const auto& pos : enemies[i])
            {
			    m_Enemies.push_back(std::make_unique<Goblin>(scene, m_Player, pos));
		    }
		break;
        default:
            break;
        }
    }
}