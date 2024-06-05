#pragma once
#include "pch.h"
#include "GameObject.h"
#include "PlayerAttacks.h"
#include "Health.h"

class Texture;
class Level;
class DoorManager;
class Player final : public GameObject
{
public:
	Player(Scene* scene);
	~Player() override = default;

	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	void Update() override;
	void Render() const override;
	void Reset() override;

	//lmao shape as no business being private If i can just publicly change it
	Rectf GetShape() const { return m_Shape; }
	void SetShape(Rectf& shape) { m_Shape = shape; }
	Point2f GetPosition() const { return Point2f{ m_Shape.left + m_Shape.width * 0.5f, m_Shape.bottom + m_Shape.height * 0.5f }; }
	Point2f GetRelativeCenter() const;
	void SetAngle(float angle) { m_Angle = angle; }
	bool IsInvincible() const { return m_IsInvincible; }
	int GetHealth() const { return m_Health->GetTotalHealth(); }
	Health* GetHealthObject() const { return m_Health.get(); }

	bool IsColliding(const Rectf& actorShape) const;
	bool CollidingWithDoor(const Rectf& actorShape) const;
	int GetDamage() const { return m_BasicAttack->GetDamage(); }
	void Attack();
	void DealDamage(const int damage);
	void AddDoorManager(DoorManager* doorManager) const { m_DoorManagerPtr = doorManager; };
	void Pause() { pause = true; }
	void Unpause() { pause = false; }
	bool GetPause() const { return pause; }

	void AddHealth() { m_Health->AddHealth(); }
	void AddDamage() { m_BasicAttack->IncreaseDamage(); }
	void AddFireRate() { m_BasicAttack->ReduceCooldown(); }
private:
	std::unique_ptr<ShootAttack> m_BasicAttack;
	Rectf m_Shape;
	//Texture* m_pSpritesTexture;
	Texture* m_YouDiedText;
	Level* m_LevelPtr;
	mutable DoorManager* m_DoorManagerPtr = nullptr;
	std::unique_ptr<Health> m_Health;
	
	float m_textAppearTime = 0.0f;
	bool showDeathText = false;
	float m_Angle = 0.f;
	bool m_IsInvincible = false;
	float m_Iframes = 0.0f;

	bool pause = false;
	void WarpPlayer();

	bool m_IsPlayerDead = false;
};

