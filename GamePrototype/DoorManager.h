#pragma once
#include "GameObject.h"
#include "Doors.h"

class Player;
class Texture;

class DoorManager final : public GameObject
{
public:
	DoorManager(Scene* scene, Player* player);
	~DoorManager() override = default;

	void Update() override;
	void Render() const override;
	void Reset() override;
	bool IsPlayerColliding(const Rectf& actorShape) const;
	
private:
	Texture* m_OpenDoorText;
	std::vector<std::unique_ptr<Doors>> m_DoorsPtr;
	std::vector<std::vector<Point2f>> m_Doors;

	Player* m_PlayerPtr;
	//BossHealthBar* m_BossHealthBarPtr;

	//bool m_IsBossActive = false;
	//int m_CurrentActiveBoss = -1;

	//void CheckForBossTriggers(int& id);
	//void ActivateBoss(int id);

	void Init();
};

