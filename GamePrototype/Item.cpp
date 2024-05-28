#include "pch.h"

#include "Item.h"
#include "Player.h"

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
	else if (m_IsOwned)
	{
		utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
		utils::FillArc(m_Center, 6, 6, 0, 360);
	}
}

void Item::PickUp()
{
	m_IsOwned = true; 
	m_IsDropped = false;
}
