#include "HighScoreLoader.h"

#include <algorithm>
#include <fstream>
#include <ostream>
#include <iostream>

//#pragma warning(disable : 4996)
#include "../3rdParty/rapidjson/writer.h"
#include "../3rdParty/rapidjson/stringbuffer.h"
//#pragma warning(default : 4996)

using namespace rapidjson;

int HighScoreLoader::LoadHighScores(const std::string& fileName)
{
    m_FileName = "../Data/" + fileName;
    std::ifstream inputFile(m_FileName);

    // Check if file was opened successfully
    if (!inputFile.is_open())
    {
        GenerateDefaultJson(m_FileName);
        return 0;
    }

    // Read the entire file into a string
    std::string fileContents((std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>());

    // Close the input file
    inputFile.close();

    m_Document.Parse(fileContents.c_str());

    if (m_Document.HasParseError() || !m_Document.IsArray())
    {
        GenerateDefaultJson(m_FileName);
        return 0;
    }


    int biggestHighScore = 0;

    for (SizeType i = 0; i < m_Document.Size(); ++i)
    {
        const Value& scoreObj = m_Document[i];
        if (scoreObj.IsObject() && scoreObj.HasMember("name") && scoreObj.HasMember("high_score"))
        {
            const Value& nameValue = scoreObj["name"];
            const Value& highScoreValue = scoreObj["high_score"];

            if (nameValue.IsString() && highScoreValue.IsInt())
            {
                std::string name = nameValue.GetString();
                const int highScore = highScoreValue.GetInt();
                m_HighScores[name] = highScore;
                if (highScore > biggestHighScore)
                {
                    biggestHighScore = highScore;
                }
            }
        }
    }

    return biggestHighScore;
}

void HighScoreLoader::AddHighScore(const std::string& playerName, int score)
{
    m_HighScores[playerName] = std::max(m_HighScores[playerName], score);

    using namespace rapidjson;


    Document::AllocatorType& allocator = m_Document.GetAllocator();

    //Value newPlayer(kObjectType);

    // Only keep the top 5 in the file.
    m_Document.Clear();

    for (const auto& [newName, newScore] : GetTopFive())
    {
        Value newPlayer(kObjectType);
        newPlayer.AddMember("name", Value(newName.c_str(), allocator).Move(), allocator);
        newPlayer.AddMember("high_score", newScore, allocator);
        m_Document.PushBack(newPlayer, allocator);
    }


    StringBuffer bufferOut;
    Writer<StringBuffer> writer(bufferOut);
    m_Document.Accept(writer);

    std::ofstream outFile(m_FileName);
    if (!outFile.is_open())
        return;

    outFile.write(bufferOut.GetString(), bufferOut.GetSize());
    outFile.close();
}

std::vector<std::pair<std::string, int>> HighScoreLoader::GetTopFive()
{
    std::vector<std::pair<std::string, int>> sortedVector(m_HighScores.begin(), m_HighScores.end());

    std::ranges::sort(sortedVector, [](const auto& a, const auto& b)
        {
            return a.second > b.second;
        });

    std::vector<std::pair<std::string, int>> topFive;
    int count = 0;

    for (const auto& entry : sortedVector)
    {
        topFive.emplace_back(entry);
        ++count;

        if (count == 5)
        {
            break;
        }
    }

    while (count < 5)
    {
        ++count;
        topFive.emplace_back(std::pair{ "-----", 0 });
    }


    return topFive;
}

void HighScoreLoader::GenerateDefaultJson(const std::string& filename)
{
    using namespace rapidjson;

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to create file for highscores\n";
        return;
    }

    m_Document.SetArray();

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    m_Document.Accept(writer);

    file.write(buffer.GetString(), buffer.GetSize());
    file.close();
}

// CODE GENERATED BY CHATGPT

//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <algorithm>
//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
//
//using namespace rapidjson;
//
//struct HighScore {
//    std::string playerName;
//    int score;
//};
//
//std::vector<HighScore> highScores;
//
//// Function to save high scores to a JSON file
//void saveHighScores() {
//    Document scoresJson;
//    scoresJson.SetArray();
//
//    for (const auto& score : highScores) {
//        Value scoreObj(kObjectType);
//        Value playerName(score.playerName.c_str(), scoresJson.GetAllocator());
//        scoreObj.AddMember("name", playerName, scoresJson.GetAllocator());
//        scoreObj.AddMember("score", score.score, scoresJson.GetAllocator());
//        scoresJson.PushBack(scoreObj, scoresJson.GetAllocator());
//    }
//
//    StringBuffer buffer;
//    Writer<StringBuffer> writer(buffer);
//    scoresJson.Accept(writer);
//
//    std::ofstream outputFile("high_scores.json");
//    outputFile << buffer.GetString();
//    outputFile.close();
//}

// Function to load high scores from a JSON file
// 
//void loadHighScores() {
//    highScores.clear();
//
//    std::ifstream inputFile("high_scores.json");
//    if (!inputFile.is_open()) {
//        return;
//    }
//
//    std::stringstream buffer;
//    buffer << inputFile.rdbuf();
//    std::string fileContents = buffer.str();
//
//    Document scoresJson;
//    scoresJson.Parse(fileContents.c_str());
//
//    for (auto& scoreJson : scoresJson.GetArray()) {
//        highScores.push_back({
//            scoreJson["name"].GetString(),
//            scoreJson["score"].GetInt()
//            });
//    }
//
//    inputFile.close();
//}
//
//// Function to update and maintain top 5 high scores
//void updateHighScores(const std::string& playerName, int score) {
//    highScores.push_back({ playerName, score });
//    std::sort(highScores.begin(), highScores.end(), [](const HighScore& a, const HighScore& b) {
//        return a.score > b.score;
//        });
//
//    if (highScores.size() > 5) {
//        highScores.pop_back(); // Keep only the top 5 scores
//    }
//
//    saveHighScores();
//}
//
//// Function to display high scores
//void displayHighScores() {
//    std::cout << "High Scores:\n";
//    for (const auto& score : highScores) {
//        std::cout << score.playerName << ": " << score.score << "\n";
//    }
//}
//
//int main() {
//    loadHighScores();
//    // ... your game logic ...
//
//    return 0;
//}