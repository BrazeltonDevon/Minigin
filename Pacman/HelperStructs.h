#pragma once
#include <vector>

struct LevelData
{
	int levelHeight;
	int levelWidth;
	std::vector<std::vector<int>> levelLayout;
};