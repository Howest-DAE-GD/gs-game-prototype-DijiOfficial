#pragma once
#include "Enemy.h"
//how do i include the GameObject but avoid multiple inclusion
//#include "GameObject.h"
#include <memory>

class Player;
class Scene;

class EnemyManager final : public GameObject
{
public:
	EnemyManager(Scene* scene, Player* player);
	~EnemyManager() override;

	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;

	void Update() override;
	void Render() const override;
	void Reset() override;
	void AddEnemy(Player* player, const Point2f& pos);
	void AddEnemy(Scene* scene, Player* player, const Point2f& pos);
	void ParseEnemyData(std::vector<std::vector<Point2f>> enemies);
private:
	std::vector<std::unique_ptr<Enemy>> m_Enemies;
	std::vector<std::vector<Point2f>> m_EnemiesPos;
	Player* m_Player;
};

