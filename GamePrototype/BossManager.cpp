#include "pch.h"

#include "BossManager.h"
#include "CollisionSingleton.h"
#include "Player.h"
#include "SvgParser.h"
#include "IObserver.h"

BossManager::BossManager(Scene* scene, Player* player, BossHealthBar* healthBar)
	: GameObject{ scene }
	, m_PlayerPtr{ player }
	, m_BossHealthBarPtr{ healthBar }
{
	Init();
}

void BossManager::Update()
{
	int triggerID = -1;
	CheckForBossTriggers(triggerID);
	
	//Create the boss unless it's the final boss then activate
	// so i can keep track of the number of bossees defeated etc
	if (triggerID != -1)
		ActivateBoss(triggerID);

	for (const auto& boss : m_Bosses)
	{
		boss->Update();
	}

	if (m_IsBossActive)
	{
		const auto& state = m_Bosses[m_CurrentActiveBoss]->GetState();

		if (state == BossState::DEAD)
		{
			m_IsBossActive = false;
			m_CurrentActiveBoss = -1;
			m_BossHealthBarPtr->SetInactive();
		}
	}
}

void BossManager::Render() const
{
	for (const auto& boss : m_Bosses)
	{
		boss->Render();
	}
}

bool BossManager::IsFinalBossDead() const
{
	return m_Bosses[0]->GetState() == BossState::DEAD;
}

void BossManager::CheckForBossTriggers(int& id)
{
	const auto& playerShape = m_PlayerPtr->GetShape();

	for (int idx{ 0 }; idx < m_BossTrigers.size(); ++idx)
	{
		const Point2f bottomLeft(playerShape.left, playerShape.bottom);
		const Point2f topLeft(playerShape.left, playerShape.bottom + playerShape.height);

		utils::HitInfo hitInfo;
		if (utils::Raycast(m_BossTrigers[idx], bottomLeft, topLeft, hitInfo))
		{
			id = idx;
			break;
		}

		const Point2f topRight(playerShape.left + playerShape.width, playerShape.bottom + playerShape.height);
		if (utils::Raycast(m_BossTrigers[idx], topLeft, topRight, hitInfo))
		{
			id = idx;
			break;
		}

		const Point2f bottomRight(playerShape.left + playerShape.width, playerShape.bottom);
		if (utils::Raycast(m_BossTrigers[idx], topRight, bottomRight, hitInfo))
		{
			id = idx;
			break;
		}

		(void)hitInfo;
	}
}

void BossManager::ActivateBoss(int id)
{
	for (auto& boss : m_Bosses)
	{
		if (boss->GetID() == id and boss->GetState() == BossState::DISABLED)
		{
			m_IsBossActive = true;
			m_BossHealthBarPtr->SetActive();
			m_CurrentActiveBoss = id;
			boss->Activate();
			
			boss->GetHealthObject()->AddObserver(MessageTypes::HEALTH_CHANGE, m_BossHealthBarPtr);
			break;
		}
	}
}

void BossManager::Init()
{
	const auto& scene = GetOwner();

	SVGParser::GetVerticesFromSvgFile("BossTriggers.svg", m_BossTrigers);
	SVGParser::ParseSVGData(m_BossTrigers);

	m_Bosses.push_back(std::make_unique<FinalBoss>(scene, m_PlayerPtr));
	m_Bosses.push_back(std::make_unique<FirstBoss>(scene, m_PlayerPtr));
}
