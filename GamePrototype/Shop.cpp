#include "pch.h"

#include "Shop.h"
#include "ResourceManager.h"
#include "utils.h"
#include "Player.h"
#include "ItemCounter.h"
#include "SceneManager.h"
#include "DoorManager.h"

Shop::Shop(Scene* scene, Player* player)
	: GameObject(scene)
{
	const auto& font = ResourceManager::GetInstance().LoadFont("Fonts/zig.ttf", 24);
	texture = ResourceManager::GetInstance().LoadTexture("SHOP", font, Color4f{1.f, 1.f, 1.f, 1.f});
	m_player = player;
	m_OpenShopText = ResourceManager::GetInstance().LoadTexture("press F to open the shop", font, Color4f{ 1.f, 1.f, 0.f, 1.f });
	moreHealth = ResourceManager::GetInstance().LoadTexture("More Health", font, Color4f{ 1.f, 1.f, 1.f, 1.f });;
	moreDamage = ResourceManager::GetInstance().LoadTexture("More Damage", font, Color4f{ 1.f, 1.f, 1.f, 1.f });;
	moreAttackRate = ResourceManager::GetInstance().LoadTexture("More Fire Rate", font, Color4f{ 1.f, 1.f, 1.f, 1.f });;
	cost = ResourceManager::GetInstance().LoadTexture("All Upgrades cost 5 coins", font, Color4f{ 0.f, 1.f, 1.f, 1.f });;
}

#include <iostream>
void Shop::Update()
{
	if (not m_IsActive)
		return;

	auto pKeyboard = SDL_GetKeyboardState(nullptr);
	const auto& shop = Rectf{ 4500,1250, texture->GetWidth(), texture->GetHeight() };
	const auto& playerPos = m_player->GetShape();

	if (utils::GetDistance(shop.left + shop.width * 0.5f, shop.bottom + shop.height * 0.5f, playerPos.left + playerPos.width * 0.5f, playerPos.bottom + playerPos.height * 0.5f) < 160.f)
	{
		if (pKeyboard[SDL_SCANCODE_F])
		{
			m_InShop = true;
			m_player->Pause();
		}
		else if (pKeyboard[SDL_SCANCODE_ESCAPE])
		{
			m_InShop = false;
			m_player->Unpause();
		}
	}
	if (m_InShop)
	{
		if (!pKeyboard[SDL_SCANCODE_LEFT] && !pKeyboard[SDL_SCANCODE_A])
			wasDownKey = false;

		if (!pKeyboard[SDL_SCANCODE_RIGHT] && !pKeyboard[SDL_SCANCODE_D])
			wasUpKey = false;

		if (!pKeyboard[SDL_SCANCODE_RETURN])
			wasEnterKey = false;

		if ((pKeyboard[SDL_SCANCODE_LEFT] or pKeyboard[SDL_SCANCODE_A]) && !wasDownKey)
		{
			--currentSelection;
			if (currentSelection < 0)
				currentSelection = 2;
			wasDownKey = true;
		}
		if ((pKeyboard[SDL_SCANCODE_RIGHT] or pKeyboard[SDL_SCANCODE_D]) && !wasUpKey)
		{
			++currentSelection;
			currentSelection %= 3;
			wasUpKey = true;
		}

		if (pKeyboard[SDL_SCANCODE_RETURN] && !wasEnterKey)
		{
			wasEnterKey = true;
			if (SceneManager::GetInstance().GetScene("Hud")->GetGameObject<ItemCounter>()->GetCoinCount() >= 5)
			{
				switch (currentSelection)
				{
				case 0:
					std::cout << "added Health" << std::endl;
					m_player->AddHealth();
					break;
				case 1:
					std::cout << "added Damage" << std::endl;
					m_player->AddDamage();
					break;
				case 2:
					std::cout << "added FireRate" << std::endl;
					m_player->AddFireRate();
					break;
				}

				SceneManager::GetInstance().GetScene("Hud")->GetGameObject<ItemCounter>()->RemoveCoins(5);
			}
		}
	}

	//if colliding with entrance door deactive
	const auto& doors = SceneManager::GetInstance().GetScene("Level")->GetGameObject<DoorManager>()->GetDoors();
	for (const auto& collisionBox : doors)
	{
		const Point2f bottomLeft(playerPos.left, playerPos.bottom);
		const Point2f topLeft(playerPos.left, playerPos.bottom + playerPos.height);

		utils::HitInfo hitInfo;
		if (utils::Raycast(collisionBox, bottomLeft, topLeft, hitInfo))
		{
			m_IsActive = false;
			return;
		}

		const Point2f topRight(playerPos.left + playerPos.width, playerPos.bottom + playerPos.height);
		if (utils::Raycast(collisionBox, topLeft, topRight, hitInfo))
		{
			m_IsActive = false;
			return;
		}


		const Point2f bottomRight(playerPos.left + playerPos.width, playerPos.bottom);
		if (utils::Raycast(collisionBox, topRight, bottomRight, hitInfo))
		{
			m_IsActive = false;
			return;
		}
	}	
}

void Shop::Render() const
{
	if (not m_IsActive)
		return;

	texture->Draw(Point2f{4500, 1250});
	const auto& playerPos = m_player->GetShape();

	if (m_InShop)
	{
		//846.f, 500.f
		utils::SetColor(Color4f{ 0.5f, 0.5f, 0.5f, 1.f });
		utils::FillRect(playerPos.left - 300, playerPos.bottom - 150, 620, 390);
		utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.f });

		utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.f });
		if (currentSelection == 0)
			utils::SetColor(Color4f{ 0.5f, 1.0f, 0.5f, 1.f });
		utils::FillRect(playerPos.left - 290, playerPos.bottom - 130, 180, 320);

		utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.f });
		if (currentSelection == 1)
			utils::SetColor(Color4f{ 0.5f, 1.0f, 0.5f, 1.f });
		utils::FillRect(playerPos.left - 90, playerPos.bottom - 130, 180, 320);

		utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.f });
		if (currentSelection == 2)
			utils::SetColor(Color4f{ 0.5f, 1.0f, 0.5f, 1.f });
		utils::FillRect(playerPos.left + 120, playerPos.bottom - 130, 180, 320);

		moreHealth->Draw(Point2f{ playerPos.left - 275, playerPos.bottom });
		moreDamage->Draw(Point2f{ playerPos.left - 75, playerPos.bottom - 50 });
		moreAttackRate->Draw(Point2f{ playerPos.left + 100, playerPos.bottom + 50 });
		cost->Draw(Point2f{ playerPos.left - cost->GetWidth() * 0.5f, playerPos.bottom + 200});
	}
	else
	{
		const auto& shop = Rectf{ 4500,1250, texture->GetWidth(), texture->GetHeight()};

		if (utils::GetDistance(shop.left + shop.width * 0.5f, shop.bottom + shop.height * 0.5f, playerPos.left + playerPos.width * 0.5f, playerPos.bottom + playerPos.height * 0.5f) < 160.f)
		{
			const Rectf dst = Rectf{ playerPos.left - m_OpenShopText->GetWidth() * 0.5f + playerPos.width * 0.5f , playerPos.bottom - 100, m_OpenShopText->GetWidth(), m_OpenShopText->GetHeight() };
			m_OpenShopText->Draw(dst);
		}
	}
}
