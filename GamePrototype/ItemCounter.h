#pragma once
#include "GameObject.h"

class Texture;
class Font;
class ItemCounter final : public GameObject
{
public:
	ItemCounter(Scene* scene);
	~ItemCounter() = default;

	void Update() override ;
	void Render() const override;
	void Reset() override;
	void AddKey();
	void RemoveKey();

	void AddFinalKey();
	void RemoveFinalKey();

	void AddCoin(int amout = 0);
	void RemoveCoins(int amount);
	int GetCoinCount() const { return m_CoinCounter;  };

	void AddDeadBoss();
	void AddHealth();
	void AddDamage();
	void AddFireRate();

private:
	Font* font = nullptr;
	Texture* m_KeyTexture = nullptr;
	Texture* m_FinalKeyTexture = nullptr;
	Texture* m_CoinTexture = nullptr;
	Texture* m_DeadBossesTexture = nullptr;
	Texture* fireRate = nullptr;
	Texture* health = nullptr;
	Texture* Damage = nullptr;
	Texture* Map = nullptr;
	int m_CoinCounter = 0;
	int m_KeyCounter = 0;
	int m_DeadBosses = 0;
	float m_FireRate = 1.5;
	int m_Health = 400;
	int m_Damage = 25;
	const Point2f center{ 725.f, 475.f };
	const Point2f pos{ 740.f, 465.f };
	bool m_HasFinalKey = false;
	bool wasEnterKey = false;
};

