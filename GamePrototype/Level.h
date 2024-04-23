#pragma once
#include "GameObject.h"
#include "Tiles.h"
#include "Texture.h"
#include "WFC.h"

class Level final : public GameObject
{
public:
	Level(Scene* scene);
	~Level() override;

	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;

	void Update() override {};
	void Render() const override;

private:
	std::vector<std::vector<Point2f>> m_VerticesVec;
	Rectf m_Viewport;
	//replace with vec of unique ptr? they would need to be shared
	std::vector<Tiles*> m_TilesPtrVec;
	const Texture* m_BmpTileTexturePtr = nullptr;
	int m_WorldWidth = 320;
	int m_WorldHeight = 180;
	constexpr static int TILE_SIZE = 32;

	void LoadMap();
	void PaintMap() const;
};

