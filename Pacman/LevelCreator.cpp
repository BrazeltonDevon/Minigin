#include "LevelCreator.h"

#include <rapidjson.h>
#include <document.h>
#include <stream.h>
#include <filereadstream.h>

#include <iostream>
#include "HelperStructs.h"
#include "Scene.h"
#include "ColliderComponent.h"
#include "Transform.h"
#include "RenderComponent.h"

using namespace std;
using namespace rapidjson;

// Resources for rapidjson
//https://rapidjson.org/md_doc_tutorial.html#QueryArray

bool dae::LevelCreator::CreateLevel(const std::wstring& filePath, Scene* scene)
{
	std::wstring fileName = filePath;
	rapidjson::Document jsonFile;
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, fileName.c_str(), L"rb");

	if (pFile != nullptr)
	{
		fseek(pFile, 0, SEEK_END);
		const size_t size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		char* readBuffer = new char[size];
		rapidjson::FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
		jsonFile.ParseStream(inputStream);
		delete[] readBuffer;
		fclose(pFile);
	}

	const rapidjson::Value& tileSizeVal = jsonFile["tileSize"];
	const rapidjson::Value& nrRowsVal = jsonFile["nrRows"];
	const rapidjson::Value& nrColsVal = jsonFile["nrCols"];
	const rapidjson::Value& levelLayoutVal = jsonFile["levelLayout"];

	int tileSize = tileSizeVal.GetInt();
	int nrRows = nrRowsVal.GetInt();
	int nrCols = nrColsVal.GetInt();

	std::vector<int>levelLayOut;

	for (SizeType i = 0; i < levelLayoutVal.Size(); ++i)
	{
		// get values in the array
		levelLayOut.push_back(levelLayoutVal[i].GetInt());
	}

	// starting position of the grid for the level
	glm::vec3 startPos{0.f, 0.f, 0.f};
	auto levelSize = levelLayOut.size();

	int mapSize = nrRows * nrCols;

	for (int i = 0; i < nrRows; ++i)
	{
		float posY = startPos.y + (i * tileSize); //* tileSize;
		//std::cout << "col = " << i << "\n";

		for (int j = 0; j < nrCols; ++j)
		{
			float posX = startPos.x + (j * tileSize); //* tileSize;
			

			//std::cout << "row = " << j << "\n";

			switch (levelLayOut[i * nrCols + j])
			{
			case 1:
				LevelCreator::GetInstance().CreateWall(scene, posX, posY);
				break;
			default:
				break;
			}
		}

	}


	return true;
}

void dae::LevelCreator::CreateWall(Scene* scene, float xPos, float yPos)
{
	auto wall = std::make_shared<GameObject>();
	auto wallTransform = wall->AddComponent<Transform>();
	wallTransform->SetLocalPosition(xPos, yPos, 0.f);
	auto wallRenderer = wall->AddComponent<RenderComponent>();
	wallRenderer->SetTexture("wall.png");
	auto wallCollider = wall->AddComponent<ColliderComponent>("WALL");
	wallCollider->SetDimensions(xPos, yPos, 16.f, 16.f);

	scene->Add(wall);
}
