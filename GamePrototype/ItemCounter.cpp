#include "pch.h"
#include "ItemCounter.h"
#include "ResourceManager.h"
#include <format>
#include "SceneManager.h"
#include "Player.h"

ItemCounter::ItemCounter(Scene* scene)
	: GameObject{ scene }
{
	font = ResourceManager::GetInstance().LoadFont("Fonts/zig.ttf", 16);
	m_KeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_KeyCounter), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
	m_FinalKeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(0), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
	m_DeadBossesTexture = ResourceManager::GetInstance().LoadTexture(std::format("{}/6 Killed", m_DeadBosses), font, Color4f{1.f, 1.f, 1.f, 1.f});
	m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 0.f, 1.f });

	fireRate = ResourceManager::GetInstance().LoadTexture(std::format("{} seconds", m_FireRate), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
	health = ResourceManager::GetInstance().LoadTexture(std::format("{}", m_Health), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
	Damage = ResourceManager::GetInstance().LoadTexture(std::format("Damage: {}", m_Damage), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
	Map = ResourceManager::GetInstance().LoadTexture("Map.png");
}

void ItemCounter::Update()
{
	auto pKeyboard = SDL_GetKeyboardState(nullptr);

	
		if (!pKeyboard[SDL_SCANCODE_P])
			wasEnterKey = false;

		

		if (pKeyboard[SDL_SCANCODE_P] && !wasEnterKey)
		{
			wasEnterKey = true;
			m_CoinCounter += 5;
			m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 1.f, 1.f });

		}
}

void ItemCounter::Render() const
{
	utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
	m_DeadBossesTexture->Draw(Point2f{ pos.x - 30.f, pos.y - 60 });
	fireRate->Draw(Point2f{ 330, 20 });
	health->Draw(Point2f{ 30, 30 });
	Damage->Draw(Point2f{ 330, 40 });
	
	utils::FillArc(center, 6, 6, 0, 360);
	m_KeyTexture->Draw(pos);

	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::FillArc(Point2f{center.x, center.y - 20}, 6, 6, 0, 360);
	m_FinalKeyTexture->Draw(Point2f{ pos.x, pos.y - 20 });

	utils::SetColor(Color4f{ 1.f, 1.f, 0.f, 1.f });
	utils::FillArc(Point2f{center.x, center.y - 40}, 6, 6, 0, 360);
	m_CoinTexture->Draw(Point2f{ pos.x, pos.y - 40 });

	//minimap
	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	const Rectf map = Rectf{ 601, 5, 240, 145 };
	Map->Draw(map);

	const auto& playerPosition = SceneManager::GetInstance().GetScene("Level")->GetGameObject<Player>()->GetPosition();
	constexpr float worldWidth = 10240.f;
	constexpr float worldHeight = 5760.0f;
	const float scaleX = map.width / worldWidth;
	const float scaleY = map.height / worldHeight;
	const float playerMapX = map.left + (playerPosition.x * scaleX);
	const float playerMapY = map.bottom + (playerPosition.y * scaleY);
	const float playerMarkerSize = 5.0f;

	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::FillRect(Rectf{ playerMapX - playerMarkerSize * 0.5f, playerMapY - playerMarkerSize * 0.5f, playerMarkerSize, playerMarkerSize });
}

void ItemCounter::Reset()
{
	m_KeyCounter = 0;
	m_KeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_KeyCounter), font, Color4f{ 1.f, 1.f, 1.f, 1.f });

	m_DeadBosses = 0;
	m_DeadBossesTexture = ResourceManager::GetInstance().LoadTexture(std::format("{}/6 Killed", m_DeadBosses), font, Color4f{ 1.f, 1.f, 0.f, 1.f });
}

void ItemCounter::AddKey()
{
	++m_KeyCounter;
	m_KeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_KeyCounter), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
}

void ItemCounter::RemoveKey()
{
	--m_KeyCounter;
	m_KeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_KeyCounter), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
}

void ItemCounter::AddFinalKey()
{
	m_HasFinalKey = true;
	m_FinalKeyTexture = ResourceManager::GetInstance().LoadTexture("1", font, Color4f{ 1.f, 0.f, 0.f, 1.f });
}

void ItemCounter::RemoveFinalKey()
{
	m_HasFinalKey = false;
	m_FinalKeyTexture = ResourceManager::GetInstance().LoadTexture("0", font, Color4f{1.f, 0.f, 0.f, 1.f});
}

void ItemCounter::AddCoin(int amount)
{
	if (amount == 0)
		++m_CoinCounter;
	else
		m_CoinCounter += amount;
	m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 0.f, 1.f });
}

void ItemCounter::RemoveCoins(int amount)
{
	m_CoinCounter -= amount;
	m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 0.f, 1.f });
}

void ItemCounter::AddDeadBoss()
{
	++m_DeadBosses;
	m_DeadBossesTexture = ResourceManager::GetInstance().LoadTexture(std::format("{}/6 Killed", m_DeadBosses), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
}

void ItemCounter::AddHealth()
{
	m_Health += 20;
	health = ResourceManager::GetInstance().LoadTexture(std::format("{}", m_Health), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
}

void ItemCounter::AddDamage()
{
	m_Damage += 10;
	Damage = ResourceManager::GetInstance().LoadTexture(std::format("Damage: {}", m_Damage), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
}

void ItemCounter::AddFireRate()
{
	m_FireRate -= 0.2f;
	fireRate = ResourceManager::GetInstance().LoadTexture(std::format("{} seconds", m_FireRate), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
}


