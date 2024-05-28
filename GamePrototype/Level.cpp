#include "pch.h"
#include "SvgParser.h"
#include "Level.h"
#include "EnumClasses.h"
#include "Scene.h"
#include "ResourceManager.h"

#include <thread>

#include <iostream>
Level::Level(Scene* scene)
	: GameObject{ scene }
{
	m_BmpTileTexturePtr = ResourceManager::GetInstance().LoadTexture("Images/Tiles.bmp");
	SVGParser::GetVerticesFromSvgFile("test.svg", m_VerticesVec);
	SVGParser::ParseSVGData(m_VerticesVec);

	//LoadMap();
}

Level::~Level()
{
	for (auto& pTile : m_TilesPtrVec)
	{
		delete pTile;
		pTile = nullptr;
	}
	m_TilesPtrVec.clear();
}

void Level::Render() const
{
	//PaintMap();

	utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.0f });
	for (const auto& vertices : m_VerticesVec)
	{
		utils::DrawPolygon(vertices);
	}
}

bool Level::IsPlayerColliding(const Rectf& playerShape) const
{
	for (const auto& collisionBox : m_VerticesVec)
	{
		const Point2f bottomLeft(playerShape.left, playerShape.bottom);
		const Point2f topLeft(playerShape.left, playerShape.bottom + playerShape.height);

		utils::HitInfo hitInfo;
		if (utils::Raycast(collisionBox, bottomLeft, topLeft, hitInfo))
			return true;

		const Point2f topRight(playerShape.left + playerShape.width, playerShape.bottom + playerShape.height);
		if (utils::Raycast(collisionBox, topLeft, topRight, hitInfo))
			return true;


		const Point2f bottomRight(playerShape.left + playerShape.width, playerShape.bottom);
		if (utils::Raycast(collisionBox, topRight, bottomRight, hitInfo))
			return true;

		(void)hitInfo;
	}
	return false; 
}

void Level::LoadMap()
{
	m_TilesPtrVec.reserve(m_WorldWidth * m_WorldHeight);
	for (int i = 0; i < m_WorldWidth * m_WorldHeight; ++i)
		m_TilesPtrVec.emplace_back(new Tiles());

	for (int it = 0; it < m_TilesPtrVec.size(); ++it)
	{
		const int posY = static_cast<int>(it / m_WorldWidth);
		const int posX = it % m_WorldWidth;

		if (posY > 0)
			m_TilesPtrVec[it]->AddNeighbor(Direction::NORTH, m_TilesPtrVec[it - m_WorldWidth]);
		if (posX < m_WorldWidth - 1)
			m_TilesPtrVec[it]->AddNeighbor(Direction::EAST, m_TilesPtrVec[it + 1]);
		if (posY < m_WorldHeight - 1)
			m_TilesPtrVec[it]->AddNeighbor(Direction::SOUTH, m_TilesPtrVec[it + m_WorldWidth]);
		if (posX > 0)
			m_TilesPtrVec[it]->AddNeighbor(Direction::WEST, m_TilesPtrVec[it - 1]);
	}

	std::unique_ptr<WFC> WFCUPtr = std::make_unique<WFC>(m_TilesPtrVec);
	for (int y = 0; y < m_WorldHeight; ++y)
	{
		for (int x = 0; x < m_WorldWidth; ++x)
		{
			// Calculate the center of the current tile
			Point2f tileCenter{ (x + 0.5f) * TILE_SIZE, (y + 0.5f) * TILE_SIZE };

			float EdgeOfWorldX = m_WorldWidth * TILE_SIZE + 1;
			// Calculate the end point of the ray (edge of the world)
			Point2f rayEndRight{ EdgeOfWorldX, tileCenter.y };
			Point2f rayEndLeft{ -1.f, tileCenter.y };
			Point2f rayEndUp{ tileCenter.x, m_WorldHeight * TILE_SIZE + 1.f };
			Point2f rayEndDown{ tileCenter.x, -1.f };

			// Perform Raycast
			bool isColliding = false;
			for (const auto& vertices : m_VerticesVec)
			{
				//utils::Raycast(vertices, tileCenter, rayEndRight);
				if (utils::Raycast(vertices, tileCenter, rayEndUp))
				{
					isColliding = true;
					break;
				}
			}

			if (not isColliding)
				WFCUPtr->ForceCollapse((m_WorldHeight - y - 1) * m_WorldWidth + x);
		}
	}

	WFCUPtr->GenerateTiles();
}

void Level::PaintMap() const
{
	Rectf viewport = GetOwner()->GetGameObject<Camera>()->GetCameraPos(GetOwner()->GetGameObject<Player>()->GetShape());

	// Culling to avoid rendering 57k tiles
	int startX = static_cast<int>(viewport.left / TILE_SIZE);
	int startY = static_cast<int>((m_WorldHeight * TILE_SIZE - (viewport.bottom + viewport.height)) / TILE_SIZE);
	int endX = static_cast<int>((viewport.left + viewport.width) / TILE_SIZE) + 1;
	int endY = static_cast<int>((m_WorldHeight * TILE_SIZE - viewport.bottom) / TILE_SIZE) + 1;

	startX = std::max(startX, 0);
	startY = std::max(startY, 0);
	endX = std::min(endX, m_WorldWidth);
	endY = std::min(endY, m_WorldHeight);

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			const int index = y * m_WorldWidth + x;
			const int posX = x * TILE_SIZE;
			const int posY = (m_WorldHeight - 1 - y) * TILE_SIZE;

			const LONG srcX = static_cast<LONG>(m_TilesPtrVec[index]->GetTileName());
			const Rectf srcRect{ srcX * TILE_SIZE * 0.5f, 0.f, TILE_SIZE * 0.5f, TILE_SIZE * 0.5f };
			const Rectf dstRect{ static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE) };

			const int entropy = m_TilesPtrVec[index]->GetEntropy();
			if (entropy > 0)
			{
				utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
				utils::FillRect(dstRect);
			}
			else
			{
				m_BmpTileTexturePtr->Draw(dstRect, srcRect);
			}
		}
	}
}
