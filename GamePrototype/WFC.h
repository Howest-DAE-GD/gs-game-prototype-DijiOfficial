#pragma once
#include <vector>

class Tiles;
class WFC final
{
public:
	WFC(std::vector<Tiles*>& tiles);
	~WFC() = default;

	WFC(const WFC& other) = delete;
	WFC(WFC&& other) noexcept = delete;
	WFC& operator=(const WFC& other) = delete;
	WFC& operator=(WFC&& other) noexcept = delete;

	void GenerateTiles();

	bool CollapseFunctionAlgorithm(int x = -1, int y = -1, bool isClicked = false);
	void ForceCollapse(int idx);
	std::vector<Tiles*> GetLowestEntropyTiles();
	int GetLowestEntropy() const;

	std::vector<Tiles*> GetTiles() const { return m_TilesPtrVec; };
private:
	std::vector<Tiles*> m_TilesPtrVec{};
};