#pragma once
#include <map>
#include <string>
#include <vector>

#pragma warning(disable : 4996)
#include "../3rdParty/rapidjson/document.h"
#pragma warning(default : 4996)

class HighScoreLoader final
{
public:
	static int LoadHighScores(const std::string& fileName);
	static void AddHighScore(const std::string& playerName, int score);
	static std::vector<std::pair<std::string, int>> GetTopFive();

private:
	static void GenerateDefaultJson(const std::string& filename);

	inline static std::map<std::string, int> m_HighScores{};
	inline static rapidjson::Document m_Document{};
	inline static std::string m_FileName{};
};