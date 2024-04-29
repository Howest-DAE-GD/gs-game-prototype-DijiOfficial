#include "pch.h"

#include "PlayerAttacks.h"
#include "Level.h"

void ShootAttack::Update()
{
	for (size_t i{}; i < m_Bullets.size(); ++i)
	{
		m_Bullets[i]->Update();
	}

	for (auto it = m_Bullets.begin(); it != m_Bullets.end();)
	{
		if (m_LevelPtr->IsPlayerColliding((*it)->GetShape()))
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
	//need object pooling here
	m_Bullets.push_back(std::make_unique<Bullets>(pos, angle));
}
