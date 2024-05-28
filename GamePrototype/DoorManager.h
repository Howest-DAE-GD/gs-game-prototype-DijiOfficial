#pragma once
#include "GameObject.h"

class Player;

class DoorManager final : public GameObject
{
public:
	DoorManager(Scene* scene, Player* player);
	~DoorManager() override = default;

	void Update() override;
	void Render() const override;

	//bool GetIsBossActive() const { return m_IsBossActive; }

	//bool IsFinalBossDead() const;
private:
	//std::vector<std::unique_ptr<Boss>> m_Bosses;
	//std::vector<std::vector<Point2f>> m_BossTrigers;

	//Player* m_PlayerPtr;
	//BossHealthBar* m_BossHealthBarPtr;

	//bool m_IsBossActive = false;
	//int m_CurrentActiveBoss = -1;

	//void CheckForBossTriggers(int& id);
	//void ActivateBoss(int id);

	//void Init();
};

