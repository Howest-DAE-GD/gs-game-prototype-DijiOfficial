#pragma once
#include <map>
#include <vector>
#include <string>

// All available tiles
enum class TileName
{
	TILE_GRASS = 0,
	TILE_WATER,
	TILE_FOREST,
	TILE_ROCK,
	TILE_COASTN,
	TILE_COASTE,
	TILE_COASTS,
	TILE_COASTW,
	TILE_COASTNE,
	TILE_COASTSE,
	TILE_COASTSW,
	TILE_COASTNW,
	TILE_COASTNE2,
	TILE_COASTSE2,
	TILE_COASTSW2,
	TILE_COASTNW2,
	TILE_ROCKN,
	TILE_ROCKE,
	TILE_ROCKS,
	TILE_ROCKW,
	TILE_ROCKNE,
	TILE_ROCKSE,
	TILE_ROCKSW,
	TILE_ROCKNW,
	TILE_FORESTS,
	TILE_FORESTW,
	TILE_FORESTN,
	TILE_FORESTE,
	TILE_FORESTSW,
	TILE_FORESTNW,
	TILE_FORESTNE,
	TILE_FORESTSE,
	TILE_FORESTNE2,
	TILE_FORESTSE2,
	TILE_FORESTSW2,
	TILE_FORESTNW2,
};

// Create A vector of all available tiles names
static std::vector<std::wstring> TileNamesVec
{
	L"TILE_GRASS",
	L"TILE_WATER",
	L"TILE_FOREST",
	L"TILE_ROCK",
	L"TILE_COASTN",
	L"TILE_COASTE",
	L"TILE_COASTS",
	L"TILE_COASTW",
	L"TILE_COASTNE",
	L"TILE_COASTSE",
	L"TILE_COASTSW",
	L"TILE_COASTNW",
	L"TILE_COASTNE2",
	L"TILE_COASTSE2",
	L"TILE_COASTSW2",
	L"TILE_COASTNW2",
	L"TILE_ROCKN",
	L"TILE_ROCKE",
	L"TILE_ROCKS",
	L"TILE_ROCKW",
	L"TILE_ROCKNE",
	L"TILE_ROCKSE",
	L"TILE_ROCKSW",
	L"TILE_ROCKNW",
	L"TILE_FORESTS",
	L"TILE_FORESTW",
	L"TILE_FORESTN",
	L"TILE_FORESTE",
	L"TILE_FORESTSW",
	L"TILE_FORESTNW",
	L"TILE_FORESTNE",
	L"TILE_FORESTSE",
	L"TILE_FORESTNE2",
	L"TILE_FORESTSE2",
	L"TILE_FORESTSW2",
	L"TILE_FORESTNW2"
};
// All possible tile edge types, Used for determining which tile can connect to which set in the rules (see below)
enum TileType
{
	GRASS = 0,
	WATER = 1,
	FOREST = 2,
	COAST_N = 3,
	COAST_E = 4,
	COAST_S = 5,
	COAST_W = 6,
	FOREST_N = 7,
	FOREST_E = 8,
	FOREST_S = 9,
	FOREST_W = 10,
	ROCK_N = 11,
	ROCK_E = 12,
	ROCK_S = 13,
	ROCK_W = 14,
	ROCK = 15
};

// All possible tile edge sets, Used for determining which tile can connect to which type (see above)
struct TileInfo
{
	std::vector<TileType> m_TileTypesVec;
	int m_TileWeight;
};

using TileNameToRulesMap = const std::map<TileName, TileInfo>;
inline TileNameToRulesMap TileRuleSet
{ 
	{ TileName::TILE_GRASS,		{{ GRASS, GRASS, GRASS, GRASS }			, 1	    }}, 
	{ TileName::TILE_WATER,		{{ WATER, WATER, WATER, WATER }			, 40		}}, 
	{ TileName::TILE_FOREST,	{{ FOREST, FOREST, FOREST, FOREST }		, 1500		}}, 
	{ TileName::TILE_ROCK,		{{ ROCK, ROCK, ROCK, ROCK }				, 1500		}},
	{ TileName::TILE_COASTN,	{{ GRASS, COAST_N, WATER, COAST_N }		, 50		}}, 
	{ TileName::TILE_COASTE,	{{ COAST_E, GRASS, COAST_E, WATER }		, 50		}}, 
	{ TileName::TILE_COASTS,	{{ WATER, COAST_S, GRASS, COAST_S }		, 50		}}, 
	{ TileName::TILE_COASTW,	{{ COAST_W, WATER, COAST_W, GRASS }		, 50		}}, 
	{ TileName::TILE_COASTNE,	{{ GRASS, GRASS, COAST_E, COAST_N }		, 50		}}, 
	{ TileName::TILE_COASTSE,	{{ COAST_E, GRASS, GRASS, COAST_S }		, 50		}}, 
	{ TileName::TILE_COASTSW,	{{ COAST_W, COAST_S, GRASS, GRASS }		, 50		}}, 
	{ TileName::TILE_COASTNW,	{{ GRASS, COAST_N, COAST_W, GRASS }		, 50		}}, 
	{ TileName::TILE_COASTNE2,	{{ COAST_E, COAST_N, WATER, WATER }		, 20		}}, 
	{ TileName::TILE_COASTSE2,	{{ WATER, COAST_S, COAST_E, WATER }		, 20		}}, 
	{ TileName::TILE_COASTSW2,	{{ WATER, WATER, COAST_W, COAST_S }		, 20		}}, 
	{ TileName::TILE_COASTNW2,	{{ COAST_W, WATER, WATER, COAST_N }		, 20		}}, 
	{ TileName::TILE_ROCKN,		{{ ROCK, ROCK_N, GRASS, ROCK_N }		, 400		}}, 
	{ TileName::TILE_ROCKE,		{{ ROCK_E, ROCK, ROCK_E, GRASS }		, 400		}}, 
	{ TileName::TILE_ROCKS,		{{ GRASS, ROCK_S, ROCK, ROCK_S }		, 400		}}, 
	{ TileName::TILE_ROCKW,		{{ ROCK_W, GRASS, ROCK_W, ROCK }		, 400		}}, 
	{ TileName::TILE_ROCKNE,	{{ ROCK_E, ROCK_N, GRASS, GRASS }		, 400		}}, 
	{ TileName::TILE_ROCKSE,	{{ GRASS, ROCK_S, ROCK_E, GRASS }		, 400		}}, 
	{ TileName::TILE_ROCKSW,	{{ GRASS, GRASS, ROCK_W, ROCK_S }		, 400		}}, 
	{ TileName::TILE_ROCKNW,	{{ ROCK_W, GRASS, GRASS, ROCK_N }		, 400		}}, 
	{ TileName::TILE_FORESTN,	{{ FOREST, FOREST_N, GRASS, FOREST_N }	, 200		}}, 
	{ TileName::TILE_FORESTE,	{{ FOREST_E, FOREST, FOREST_E, GRASS }	, 200		}}, 
	{ TileName::TILE_FORESTS,	{{ GRASS, FOREST_S, FOREST, FOREST_S }	, 200		}}, 
	{ TileName::TILE_FORESTW,	{{ FOREST_W, GRASS, FOREST_W, FOREST }	, 200		}}, 
	{ TileName::TILE_FORESTNE,	{{ FOREST_E, FOREST_N, GRASS, GRASS }	, 200		}}, 
	{ TileName::TILE_FORESTSE,	{{ GRASS, FOREST_S, FOREST_E, GRASS }	, 200		}}, 
	{ TileName::TILE_FORESTSW,	{{ GRASS, GRASS, FOREST_W, FOREST_S }	, 200		}}, 
	{ TileName::TILE_FORESTNW,	{{ FOREST_W, GRASS, GRASS, FOREST_N }	, 200		}}, 
	{ TileName::TILE_FORESTNE2,	{{ FOREST, FOREST, FOREST_E, FOREST_N }	, 200		}}, 
	{ TileName::TILE_FORESTSE2,	{{ FOREST_E, FOREST, FOREST, FOREST_S }	, 200		}}, 
	{ TileName::TILE_FORESTSW2,	{{ FOREST_W, FOREST_S, FOREST, FOREST }	, 200		}}, 
	{ TileName::TILE_FORESTNW2,	{{ FOREST, FOREST_N, FOREST_W, FOREST }	, 200		}}
};

// All available directions for each tile
enum class Direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};
