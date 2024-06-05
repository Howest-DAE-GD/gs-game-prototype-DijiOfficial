#include "pch.h"

#include "Item.h"
#include "Player.h"
#include "SceneManager.h"
#include "ItemCounter.h"

void Key::Update()
{
}

void Key::Render() const
{
	if (m_IsDropped)
	{
		utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
		utils::FillArc(m_Center, 15, 15, 0 , 360);
	}
}

void Key::Reset()
{
	m_IsDropped = false;
	m_IsOwned = false;
}

void FinalKey::Update()
{
}

void FinalKey::Render() const
{
	if (m_IsDropped)
	{
		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
		utils::FillArc(m_Center, 15, 15, 0, 360);
	}
}

void FinalKey::Reset()
{
	m_IsDropped = false;
	m_IsOwned = false;
}

void Item::PickUp()
{
	m_IsOwned = true; 
	m_IsDropped = false;
}

void Item::SetUsed()
{
	if (m_IsOwned)
		SceneManager::GetInstance().GetScene("Hud")->GetGameObject<ItemCounter>()->RemoveKey();
	
	m_IsOwned = false;
}

void Coin::Update()
{
}

void Coin::Render() const
{
	if (m_IsDropped)
	{
		utils::SetColor(Color4f{ 1.f, 1.f, 0.f, 1.f });
		utils::FillArc(m_Center, 15, 15, 0, 360);
	}
}

void Coin::Reset()
{
	m_IsDropped = false;
	m_IsOwned = false;
}
