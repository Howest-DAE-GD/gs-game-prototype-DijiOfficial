#include "pch.h"
#include "DoorManager.h"
#include "Player.h"
#include "SVGParser.h"
#include "ResourceManager.h"
#include "ItemManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Player.h"

DoorManager::DoorManager(Scene* scene, Player* player)
	: GameObject{ scene }
	, m_PlayerPtr{ player }
{
	Init();
}

#include <iostream>
void DoorManager::Update()
{
	for (const auto& door : m_DoorsPtr)
	{
		if (not ItemManager::GetInstance().HasKey(door->GetID()))
			continue;

		const auto& doorPos = door->GetShape();
		const auto& playerPos = m_PlayerPtr->GetShape();

		if (not door->IsOpen() and utils::GetDistance(doorPos.left + doorPos.width * 0.5f, doorPos.bottom + doorPos.height * 0.5f, playerPos.left + playerPos.width * 0.5f, playerPos.bottom + playerPos.height * 0.5f) < 160.f)
		{
			auto pKeyboard = SDL_GetKeyboardState(nullptr);
			if (pKeyboard[SDL_SCANCODE_F])
			{
				door->OPENGNEEGNOOOOOR();
				ItemManager::GetInstance().UseKey(door->GetID());
			}
		}
	}
}

void DoorManager::Render() const
{
	for (const auto& door : m_DoorsPtr)
	{
		door->Render();

		const auto& doorPos = door->GetShape();
		const auto& playerPos = m_PlayerPtr->GetShape();

		if (not door->IsOpen() and utils::GetDistance(doorPos.left + doorPos.width * 0.5f, doorPos.bottom + doorPos.height * 0.5f, playerPos.left + playerPos.width * 0.5f, playerPos.bottom + playerPos.height * 0.5f) < 160.f)
		{
			const Rectf dst = Rectf{ playerPos.left - m_OpenDoorText->GetWidth() * 0.5f + playerPos.width * 0.5f , playerPos.bottom + 100, m_OpenDoorText->GetWidth(), m_OpenDoorText->GetHeight()};
			m_OpenDoorText->Draw(dst);			
		}
	}
}

void DoorManager::Reset()
{
	for (const auto& door : m_DoorsPtr)
		if (door->GetID() != 999)
			door->Reset();
}

bool DoorManager::IsPlayerColliding(const Rectf& actorShape) const
{
	int doorID{ -1 };
	for (const auto& collisionBox : m_Doors)
	{
		++doorID;
		if (m_DoorsPtr[doorID]->IsOpen())
			continue;

		const Point2f bottomLeft(actorShape.left, actorShape.bottom);
		const Point2f topLeft(actorShape.left, actorShape.bottom + actorShape.height);

		utils::HitInfo hitInfo;
		if (utils::Raycast(collisionBox, bottomLeft, topLeft, hitInfo))
			return true;

		const Point2f topRight(actorShape.left + actorShape.width, actorShape.bottom + actorShape.height);
		if (utils::Raycast(collisionBox, topLeft, topRight, hitInfo))
			return true;


		const Point2f bottomRight(actorShape.left + actorShape.width, actorShape.bottom);
		if (utils::Raycast(collisionBox, topRight, bottomRight, hitInfo))
			return true;

		(void)hitInfo;
	}
	return false;
}

void DoorManager::Init()
{
	const auto& font = ResourceManager::GetInstance().LoadFont("Fonts/zig.ttf", 28);
	m_OpenDoorText = ResourceManager::GetInstance().LoadTexture("press F to open the door", font, Color4f{ 1.f, 1.f, 0.f, 1.f });

	const auto& scene = GetOwner();

	SVGParser::GetVerticesFromSvgFile("dors.svg", m_Doors);
	SVGParser::ParseSVGData(m_Doors);

	int id{ 0 };
	const std::vector<unsigned int> ids{ 999, 0, 1,1,1,1,1,1,1,1,1 };
	for (const auto& pos : m_Doors)
	{
		m_DoorsPtr.push_back(std::make_unique<Doors>(pos, ids[id]));
		++id;
	}

	SceneManager::GetInstance().GetScene("Level")->GetGameObject<Player>()->AddDoorManager(this);
}
