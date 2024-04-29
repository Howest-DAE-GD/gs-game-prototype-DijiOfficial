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
	EnemyManager(Scene* scene);
	~EnemyManager() override = default;

	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;

	void Update() override;
	void Render() const override;

	void AddEnemy(Player* player, const Point2f& pos);
	void AddEnemy(Scene* scene, Player* player, const Point2f& pos);

private:
	std::vector<std::unique_ptr<Enemy>> m_Enemies;
};

