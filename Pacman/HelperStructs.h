#pragma once
#include <vector>

struct LevelData
{
	int tileWidth;
	int tileHeight;
	int levelHeight;
	int levelWidth;
	std::vector<std::vector<int>> levelLayout;
};