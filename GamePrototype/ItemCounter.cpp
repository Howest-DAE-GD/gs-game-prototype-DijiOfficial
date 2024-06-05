#include "pch.h"
#include "ItemCounter.h"
#include "ResourceManager.h"

ItemCounter::ItemCounter(Scene* scene)
	: GameObject{ scene }
{
	font = ResourceManager::GetInstance().LoadFont("Fonts/zig.ttf", 16);
	m_KeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_KeyCounter), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
	m_FinalKeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(0), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
	m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 0.f, 1.f });
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
			m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 0.f, 1.f });

		}
}

void ItemCounter::Render() const
{
	utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
	utils::FillArc(center, 6, 6, 0, 360);
	m_KeyTexture->Draw(pos);

	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::FillArc(Point2f{center.x, center.y - 20}, 6, 6, 0, 360);
	m_FinalKeyTexture->Draw(Point2f{ pos.x, pos.y - 20 });

	utils::SetColor(Color4f{ 1.f, 1.f, 0.f, 1.f });
	utils::FillArc(Point2f{center.x, center.y - 40}, 6, 6, 0, 360);
	m_CoinTexture->Draw(Point2f{ pos.x, pos.y - 40 });
}

void ItemCounter::Reset()
{
	m_KeyCounter = 0;
	m_KeyTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_KeyCounter), font, Color4f{ 1.f, 1.f, 1.f, 1.f });
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

void ItemCounter::AddCoin()
{
	++m_CoinCounter;
	m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 0.f, 1.f });
}

void ItemCounter::RemoveCoins(int amount)
{
	m_CoinCounter -= amount;
	m_CoinTexture = ResourceManager::GetInstance().LoadTexture(std::to_string(m_CoinCounter), font, Color4f{ 1.f, 1.f, 0.f, 1.f });
}
