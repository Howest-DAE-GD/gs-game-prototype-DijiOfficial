#include "pch.h"

#include "WFC.h"																				
#include "Tiles.h"
#include <memory>
#include "EnumClasses.h"
#include <stack>
#include <string>


WFC::WFC(std::vector<Tiles*>& tiles)
	: m_TilesPtrVec{ tiles }
{
}

void WFC::GenerateTiles()
{
	bool quit = false;
	while (!quit)
		quit = CollapseFunctionAlgorithm();
}

std::vector<Tiles*> WFC::GetLowestEntropyTiles()
{
	//Set lowest entropy to the highest possible value and create an empty list of tiles
	int tilesLowestEntropy = TileRuleSet.size();
	std::vector<Tiles*> tileList;

	//Loop through all tiles
	for (const auto& Tile : m_TilesPtrVec)
	{
		const int tileEntropy = Tile->GetEntropy();

		//If the tile has no entropy, skip it because it is already collapsed
		if (tileEntropy <= 0)
			continue;

		//Reset the list of tiles if a tile with a lower entropy is found
		if (tileEntropy < tilesLowestEntropy)
		{
			tileList.clear();
			tilesLowestEntropy = tileEntropy;
		}

		//Add the tile to the list of tiles with the lowest entropy
		if (tileEntropy == tilesLowestEntropy)
			tileList.push_back(Tile);
	}

	return tileList;
}

int WFC::GetLowestEntropy() const
{
	int lowestEntropy = TileRuleSet.size();
	for (const auto& tile : m_TilesPtrVec)
	{
		const int tileEntropy = tile->GetEntropy();
		if (tileEntropy > 0 and tileEntropy < lowestEntropy)
			lowestEntropy = tileEntropy;
	}

	return lowestEntropy;
}

void WFC::ForceCollapse(int idx)
{
	Tiles* tileToCollapse = m_TilesPtrVec[idx];

	tileToCollapse->ForceCollapse(TileName::TILE_GRASS);

	std::stack<Tiles*> stack;
	stack.push(tileToCollapse);

	// Propagate the constraints to the neighbors (remove all of the neighbor's unavailable tiles based on the previous neighbor)
	while (not stack.empty())
	{
		Tiles* currentTile = stack.top();
		stack.pop();

		// Get the available tiles and directions of the current tile
		std::vector<TileName> AvailableTilesForNeighborVec{ currentTile->GetAvailableTiles() };
		std::vector<Direction> directionsVec{ currentTile->GetDirections() };

		// Loop through all the nieghbors of the current tile
		for (const auto& direction : directionsVec)
		{
			Tiles* neighbor = currentTile->GetNeighbor(direction);
			if (neighbor->GetEntropy() == 0)
				continue;

			// If the neighbor was constrained*, push it to the stack. (If the neighbor had some tiles removed from his available tiles choices)
			// then add that neighbor to the stack so his neighbors can be checked
			// *see Constrain() implementation for more details
			if (neighbor->Constrain(AvailableTilesForNeighborVec, direction))
				stack.push(neighbor);
		}
	}
}

bool WFC::CollapseFunctionAlgorithm(int x, int y, bool isClicked)
{
	const auto lowestEntropyTilesList = GetLowestEntropyTiles();
	if (lowestEntropyTilesList.empty())
		return true;

	Tiles* tileToCollapse = lowestEntropyTilesList[rand() % static_cast<int>(lowestEntropyTilesList.size())];

	tileToCollapse->Collapse();

	std::stack<Tiles*> stack;
	stack.push(tileToCollapse);

	// Propagate the constraints to the neighbors (remove all of the neighbor's unavailable tiles based on the previous neighbor)
	while (not stack.empty())
	{
		Tiles* currentTile = stack.top();
		stack.pop();

		// Get the available tiles and directions of the current tile
		std::vector<TileName> AvailableTilesForNeighborVec{ currentTile->GetAvailableTiles() };
		std::vector<Direction> directionsVec{ currentTile->GetDirections() };

		// Loop through all the nieghbors of the current tile
		for (const auto& direction : directionsVec)
		{
			Tiles* neighbor = currentTile->GetNeighbor(direction);
			if (neighbor->GetEntropy() == 0)
				continue;

			// If the neighbor was constrained*, push it to the stack. (If the neighbor had some tiles removed from his available tiles choices)
			// then add that neighbor to the stack so his neighbors can be checked
			// *see Constrain() implementation for more details
			if (neighbor->Constrain(AvailableTilesForNeighborVec, direction))
				stack.push(neighbor);
		}
	}

	return false;
}
