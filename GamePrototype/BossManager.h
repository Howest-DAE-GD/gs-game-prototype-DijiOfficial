#pragma once
//#include "Singleton.h"
#include "Boss.h"
#include <memory>

class Player;
class Scene;
class BossHealthBar;

class BossManager final : public GameObject
{
public:
	BossManager(Scene* scene, Player* player, BossHealthBar* healthBar);
	~BossManager() override = default;

	BossManager(const BossManager& other) = delete;
	BossManager(BossManager&& other) = delete;
	BossManager& operator=(const BossManager& other) = delete;
	BossManager& operator=(BossManager&& other) = delete;

	void Update() override;
	void Render() const override;
	void Reset() override;
	bool GetIsBossActive() const { return m_IsBossActive; }

	bool IsFinalBossDead() const;
private:
	std::vector<std::unique_ptr<Boss>> m_Bosses;
	std::vector<std::vector<Point2f>> m_BossTrigers;

	Player* m_PlayerPtr;
	BossHealthBar* m_BossHealthBarPtr;

	bool m_IsBossActive = false;
	int m_CurrentActiveBoss = -1;

	void CheckForBossTriggers(int& id);
	void ActivateBoss(int id);

	void Init();
};

