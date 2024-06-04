#pragma once
#include "GameObject.h"
#include "CollisionSingleton.h"
#include "Health.h"

class Player;
enum class BossState
{
	DISABLED = -1,
	ALIVE = 0,
	HIT,
	DYING,
	DEAD,
};

class Boss : public GameObject
{
public:
	Boss(Scene* scene, Player* player, const unsigned int id, int health)
		: GameObject(scene)
		, m_PlayerPtr(player)
		, m_ID{ id }
	{
		m_Health = std::make_unique<Health>(health);
	};
	~Boss() = default;

	Boss(const Boss& other) = delete;
	Boss(Boss&& other) = delete;
	Boss& operator=(const Boss& other) = delete;
	Boss& operator=(Boss&& other) = delete;

	void Update() override = 0;
	void Render() const override = 0;
	void Reset() override = 0;
	void Hit(int damage);

	void Activate() { m_State = BossState::ALIVE; }
	unsigned int GetID() const { return m_ID; }
	BossState GetState() const { return m_State; }
	Health* GetHealthObject() const { return m_Health.get(); }

protected:
	Player* GetPlayer() const { return m_PlayerPtr; }
	//bool m_AttackPlayer = false;
	const int m_Speed = 250;
	const unsigned int m_ID;
	BossState m_State = BossState::DISABLED;
	CollisionSingleton& m_CollisionSingleton = CollisionSingleton::GetInstance();
	std::unique_ptr<Health> m_Health;
	Rectf m_Shape;

private:
	Player* m_PlayerPtr;
};

class FinalBoss final : public Boss
{

public:
	FinalBoss(Scene* scene, Player* player);
	~FinalBoss() = default;

	void Update() override;
	void Render() const override;
	void Reset() override;
private:
	//todo: boss health bar is wrong suzed
};

class FirstBoss : public Boss
{
public:
	FirstBoss(Scene* scene, Player* player, int id = 0, int health = 100);
	~FirstBoss() = default;

	void Update() override;
	void Render() const override;
	void Reset() override {};

private:
	//Rectf m_Shape;
};

class RealFirstBoss : public FirstBoss
{
public:
	RealFirstBoss(Scene* scene, Player* player);
	~RealFirstBoss() = default;

	//void Update() override;
	//void Render() const override;
	void Reset() override;

private:
	//Rectf m_Shape;
};

class SecondBoss : public FirstBoss
{
public:
	SecondBoss(Scene* scene, Player* player);
	~SecondBoss() = default;

	//void Update() override;
	//void Render() const override;
	void Reset() override;

private:
	//Rectf m_Shape;
};

class ThirdBoss final : public FirstBoss
{
public:
	ThirdBoss(Scene* scene, Player* player);
	~ThirdBoss() = default;

	//void Update() override;
	//void Render() const override;
	void Reset() override;

private:
	//Rectf m_Shape;
};

class FourthBoss final : public FirstBoss
{
public:
	FourthBoss(Scene* scene, Player* player);
	~FourthBoss() = default;

	//void Update() override;
	//void Render() const override;
	void Reset() override;

private:
	//Rectf m_Shape;
};

class FifthBoss final : public FirstBoss
{
public:
	FifthBoss(Scene* scene, Player* player);
	~FifthBoss() = default;

	//void Update() override;
	//void Render() const override;
	void Reset() override;

private:
	//Rectf m_Shape;
};

class SixthBoss final : public FirstBoss
{
public:
	SixthBoss(Scene* scene, Player* player);
	~SixthBoss() = default;

	//void Update() override;
	//void Render() const override;
	void Reset() override;

private:
	//Rectf m_Shape;
};