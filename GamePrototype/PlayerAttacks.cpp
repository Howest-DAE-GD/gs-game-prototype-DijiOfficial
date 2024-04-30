#include "pch.h"

#include "PlayerAttacks.h"
#include "Level.h"
#include "CollisionSingleton.h"

void ShootAttack::Update()
{
	auto& collision = CollisionSingleton::GetInstance();
	for (size_t i{}; i < m_Bullets.size(); ++i)
	{
		m_Bullets[i]->Update();
	}

	for (auto it = m_Bullets.begin(); it != m_Bullets.end();)
	{
		const auto& shape = (*it)->GetShape();
		if (m_LevelPtr->IsPlayerColliding(shape) or collision.HitEnemyType(shape))
			it = m_Bullets.erase(it);
		else
			++it;
	}
}

void ShootAttack::Render() const
{
	for (size_t i{}; i < m_Bullets.size(); ++i)
	{
		m_Bullets[i]->Render();
	}
}

void ShootAttack::Attack(const Point2f& pos, float angle)
{
	//need object pooling here but i wont dont play too long it will be fine
	m_Bullets.push_back(std::make_unique<Bullets>(pos, angle));
}
