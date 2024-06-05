#pragma once
#include "GameObject.h"

class Texture;
class Font;
class Player;

class Shop final : public GameObject
{
public:
	Shop(Scene* scene, Player* player);
	~Shop() = default;
	
	//void Initialize(Player* player);
	virtual void Update();
	virtual void Render() const;
	virtual void Reset() { m_IsActive = true; m_InShop = false; currentSelection = 0; };

	void Deactivate() { m_IsActive = false; };
private:
	bool m_IsActive = true;
	bool m_InShop = false;
	Texture* texture = nullptr;
	Texture* m_OpenShopText = nullptr;
	Texture* moreHealth = nullptr;
	Texture* moreDamage = nullptr;
	Texture* moreAttackRate = nullptr;
	Texture* cost = nullptr;
	int currentSelection = 0;
	Player* m_player = nullptr; 
	bool wasDownKey = false;
	bool wasUpKey = false;
	bool wasEnterKey = false;
};


